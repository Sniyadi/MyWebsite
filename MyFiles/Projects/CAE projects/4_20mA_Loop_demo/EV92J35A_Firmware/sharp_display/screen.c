/**
 * SHARP Memory Display - Character Cell Driver Implementation
 *
 * @file screen.c
 *
 * @brief Renders a 13x9 character grid onto the 144x168 pixel SHARP display.
 *
 * Architecture:
 *   - char_buffer[9][13] holds ASCII characters, char_style[9][13] holds
 *     per-character font style (normal/bold/oblique/bold-oblique).
 *   - dirty_flags tracks which rows have changed since last refresh.
 *   - render_text_row() converts one text row (18 scan lines) to pixels.
 *   - Display convention: bit 1 = white, bit 0 = black.
 *
 * Rendering algorithm (optimized for PIC18 at low clock speeds):
 *   The font bitmaps use a row-major, LSB-first, byte-aligned format
 *   (converted from the original Adafruit GFX MSB-first packed format by
 *   tools/convert_font.py). This allows each glyph row to be processed as
 *   a 1-2 byte merge operation rather than extracting individual pixels
 *   via expensive variable-position bit shifts.
 *
 *   For each character on a scan line, the renderer:
 *     1. Reads 1-2 bytes of pre-aligned glyph data from flash (TBLRD)
 *     2. Applies a clip mask to prevent bleed past the 11px cell boundary
 *     3. Shifts the glyph word left by (x_start & 7) to align with
 *        line_buffer's byte grid
 *     4. Merges into line_buffer with AND (normal) or OR (inverted)
 *
 *   A per-row glyph cache (91 bytes RAM) stores GFXglyph metadata read from
 *   flash once and reused across all 18 scan lines, avoiding repeated TBLRD
 *   sequences for the struct fields.
 *
 *   The 18-byte line_buffer is sent to the display via SPI1_BufferWrite()
 *   as a single block transfer, avoiding per-byte SPI reinitialisation.
 */

#include "screen.h"
#include "font_mono9.h"
#include "font_mono9_bold.h"
#include "font_mono9_oblique.h"
#include "font_mono9_boldoblique.h"
#include "sharp_mem.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define DISPLAY_WIDTH       144
#define DISPLAY_HEIGHT      168
#define BYTES_PER_LINE      (DISPLAY_WIDTH / 8)  /* 18 bytes per scan line */

/* Baseline position within each 18px-tall cell. Ascenders start at
 * scan_line = BASELINE + yOffset (typically 13 + (-10) = 3), and
 * descenders end at BASELINE + yOffset + height - 1 (max 16). */
#define BASELINE_IN_CELL    13

#define FONT_FIRST_CHAR     0x20  /* Space - first printable ASCII */
#define FONT_LAST_CHAR      0x7E  /* Tilde - last printable ASCII */

/* Lookup tables indexed by FONT_STYLE_* constants (0-3).
 * Allows O(1) font selection per character during rendering. */
static const uint8_t * const font_bitmaps[] = {
    font_mono9_bitmap,
    font_mono9_bold_bitmap,
    font_mono9_oblique_bitmap,
    font_mono9_boldoblique_bitmap
};

static const GFXglyph * const font_glyph_tables[] = {
    font_mono9_glyphs,
    font_mono9_bold_glyphs,
    font_mono9_oblique_glyphs,
    font_mono9_boldoblique_glyphs
};

/* Character grid: stores the ASCII value at each cell position */
static char char_buffer[SCREEN_ROWS][SCREEN_COLS];

/* Per-character font style (FONT_STYLE_NORMAL/BOLD/OBLIQUE/BOLD_OBLIQUE) */
static uint8_t char_style[SCREEN_ROWS][SCREEN_COLS];

/* Per-row attributes (bit 0 = inverted) */
static uint8_t row_attr[SCREEN_ROWS];

/* Bitmask of rows that need re-rendering. Bit N = row N is dirty.
 * 9 rows fit in a uint16_t (bits 0-8 used, 0x01FF = all dirty). */
static uint16_t dirty_flags;

/* Scratch buffer for building one scan line of pixel data before SPI send */
static uint8_t line_buffer[BYTES_PER_LINE];

/* Scratch buffer for vsnprintf output */
static char printf_buffer[SCREEN_COLS + 1];

/* The "current" font style applied to subsequent printf/set_char calls */
static uint8_t current_style;

static void render_text_row(uint8_t text_row);

void screen_init(void) {
    sharp_init();
    /* Hardware-clear the display to all-white (handles the bottom 6 unused
     * scan lines that are below the 9-row text area: 9*18=162, display=168) */
    sharp_clear_display();

    memset(char_buffer, ' ', sizeof(char_buffer));
    memset(char_style, 0, sizeof(char_style));
    memset(row_attr, 0, sizeof(row_attr));
    current_style = FONT_STYLE_NORMAL;
    dirty_flags = 0x01FF;  /* Mark all 9 rows dirty */

    /* Render and send the blank grid to the display */
    screen_refresh_all();
}

void screen_clear(void) {
    memset(char_buffer, ' ', sizeof(char_buffer));
    memset(char_style, 0, sizeof(char_style));
    memset(row_attr, 0, sizeof(row_attr));
    dirty_flags = 0x01FF;
}

void screen_clear_row(uint8_t row) {
    if (row >= SCREEN_ROWS) return;

    memset(char_buffer[row], ' ', SCREEN_COLS);
    memset(char_style[row], 0, SCREEN_COLS);
    row_attr[row] = 0;
    dirty_flags |= (1 << row);
}

void screen_set_char(uint8_t row, uint8_t col, char c) {
    if (row >= SCREEN_ROWS || col >= SCREEN_COLS) return;

    char_buffer[row][col] = c;
    char_style[row][col] = current_style;
    dirty_flags |= (1 << row);
}

void screen_set_font_style(uint8_t style) {
    current_style = style & 0x03;  /* Mask to valid range 0-3 */
}

void screen_printf(uint8_t row, uint8_t col, const char *fmt, ...) {
    if (row >= SCREEN_ROWS || col >= SCREEN_COLS) return;

    /* Format the string into the scratch buffer */
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(printf_buffer, sizeof(printf_buffer), fmt, args);
    va_end(args);

    if (len < 0) len = 0;
    if (len > SCREEN_COLS) len = SCREEN_COLS;

    /* Copy formatted characters into the grid, applying current font style */
    uint8_t available = SCREEN_COLS - col;
    uint8_t copy_len = (uint8_t)((len < available) ? len : available);

    for (uint8_t i = 0; i < copy_len; i++) {
        char_buffer[row][col + i] = printf_buffer[i];
        char_style[row][col + i] = current_style;
    }

    /* Clear remaining columns to end of row (prevents stale characters
     * when a shorter string replaces a longer one) */
    for (uint8_t i = col + copy_len; i < SCREEN_COLS; i++) {
        char_buffer[row][i] = ' ';
        char_style[row][i] = FONT_STYLE_NORMAL;
    }

    dirty_flags |= (1 << row);
}

void screen_set_inverted(uint8_t row, bool inverted) {
    if (row >= SCREEN_ROWS) return;

    uint8_t old_attr = row_attr[row];

    if (inverted) {
        row_attr[row] |= ROW_ATTR_INVERTED;
    } else {
        row_attr[row] &= ~ROW_ATTR_INVERTED;
    }

    /* Only mark dirty if the attribute actually changed */
    if (row_attr[row] != old_attr) {
        dirty_flags |= (1 << row);
    }
}

void screen_set_normal(uint8_t row) {
    screen_set_inverted(row, false);
}

void screen_refresh(void) {
    if (dirty_flags == 0) return;

    /* A "frame" is a single SPI transaction: CS goes high, write command is
     * sent, then any number of lines can be written, then CS goes low. */
    sharp_begin_frame();

    for (uint8_t text_row = 0; text_row < SCREEN_ROWS; text_row++) {
        if (dirty_flags & (1 << text_row)) {
            render_text_row(text_row);
        }
    }

    sharp_end_frame();
    dirty_flags = 0;
}

void screen_refresh_all(void) {
    dirty_flags = 0x01FF;
    screen_refresh();
}

/* Per-column glyph cache, populated once per text row and reused across all
 * 18 scan lines. Fields are copied individually from flash (not via struct
 * assignment) because XC8 free mode generates incorrect code for bulk struct
 * copies from program memory at higher array offsets. */
static GFXglyph glyph_cache[SCREEN_COLS];
static const uint8_t *glyph_font_ptr[SCREEN_COLS];
static uint8_t glyph_bytes_per_row[SCREEN_COLS];
static uint8_t glyph_x_start[SCREEN_COLS];
static uint8_t glyph_visible_w[SCREEN_COLS];
static void render_text_row(uint8_t text_row) {
    bool inverted = (row_attr[text_row] & ROW_ATTR_INVERTED) != 0;
    uint8_t fill_byte = inverted ? 0x00 : 0xFF;

    /* Phase 1: Populate glyph cache from flash (once per row).
     * Precomputes bytes_per_row, x_start, and visible_width so that the
     * inner scan-line loop only needs cheap RAM reads and arithmetic. */
    for (uint8_t col = 0; col < SCREEN_COLS; col++) {
        char c = char_buffer[text_row][col];
        if (c < FONT_FIRST_CHAR || c > FONT_LAST_CHAR) {
            c = '?';
        }

        uint8_t style = char_style[text_row][col] & 0x03;
        glyph_font_ptr[col] = font_bitmaps[style];

        const GFXglyph *glyphs = font_glyph_tables[style];
        uint8_t glyph_idx = (uint8_t)(c - FONT_FIRST_CHAR);
        const GFXglyph *src = &glyphs[glyph_idx];
        glyph_cache[col].bitmapOffset = src->bitmapOffset;
        glyph_cache[col].width = src->width;
        glyph_cache[col].height = src->height;
        glyph_cache[col].xAdvance = src->xAdvance;
        glyph_cache[col].xOffset = src->xOffset;
        glyph_cache[col].yOffset = src->yOffset;

        uint8_t w = glyph_cache[col].width;
        glyph_bytes_per_row[col] = (w + 7) >> 3;
        glyph_x_start[col] = (uint8_t)(col * CELL_WIDTH + glyph_cache[col].xOffset);

        /* Clip width to cell boundary */
        uint8_t cell_right = (uint8_t)((col + 1) * CELL_WIDTH);
        uint8_t x = glyph_x_start[col];
        uint8_t max_visible = (x < cell_right) ? (cell_right - x) : 0;
        glyph_visible_w[col] = (w < max_visible) ? w : max_visible;
    }

    /* Phase 2: Render each scan line by merging glyph bytes into line_buffer.
     * For each active character, we read 1-2 bytes from the row-major font
     * bitmap, clip to the cell boundary, shift into the correct bit position
     * within line_buffer, and merge using bitwise AND (normal) or OR (inverted). */
    for (uint8_t scan_line = 0; scan_line < CELL_HEIGHT; scan_line++) {
        uint8_t display_line = text_row * CELL_HEIGHT + scan_line;

        memset(line_buffer, fill_byte, BYTES_PER_LINE);

        for (uint8_t col = 0; col < SCREEN_COLS; col++) {
            uint8_t glyph_w = glyph_cache[col].width;
            uint8_t glyph_h = glyph_cache[col].height;

            if (glyph_w == 0 || glyph_h == 0) {
                continue;
            }

            int8_t glyph_row = (int8_t)scan_line -
                               (BASELINE_IN_CELL + glyph_cache[col].yOffset);

            if (glyph_row < 0 || glyph_row >= (int8_t)glyph_h) {
                continue;
            }

            /* Read 1-2 font bytes for this glyph row from flash */
            uint8_t bpr = glyph_bytes_per_row[col];
            uint16_t row_addr = glyph_cache[col].bitmapOffset +
                                (uint8_t)glyph_row * bpr;
            const uint8_t *bitmap = glyph_font_ptr[col];

            uint8_t font_b0 = bitmap[row_addr];
            uint8_t font_b1 = (bpr > 1) ? bitmap[row_addr + 1] : 0;

            /* Apply cell-boundary clip mask (LSB-first: lower bits = leftmost) */
            uint8_t vis_w = glyph_visible_w[col];
            if (vis_w < 8) {
                font_b0 &= (uint8_t)((1u << vis_w) - 1);
                font_b1 = 0;
            } else if (vis_w < glyph_w) {
                font_b1 &= (uint8_t)((1u << (vis_w - 8)) - 1);
            }

            /* Shift glyph bits to align with line_buffer position */
            uint8_t x = glyph_x_start[col];
            uint8_t byte_idx = x >> 3;
            uint8_t bit_shift = x & 7;

            /* Combine font bytes and shift into position.
             * Max width=11 + max shift=7 = 18 bits, needs up to 3 output bytes. */
            uint8_t out0 = font_b0 << bit_shift;
            uint8_t out1 = (uint8_t)((((uint16_t)font_b1 << 8) | font_b0) >> (8 - bit_shift));
            uint8_t out2 = (bit_shift > 0 && bpr > 1) ?
                           (font_b1 >> (8 - bit_shift)) : 0;

            /* Merge into line_buffer.
             * Font bit=1 means ink. Display: 0=black(ink), 1=white(bg).
             * Normal mode: CLEAR bits where font has ink (AND with ~ink)
             * Inverted mode: SET bits where font has ink (OR with ink) */
            if (!inverted) {
                line_buffer[byte_idx] &= ~out0;
                if (byte_idx + 1 < BYTES_PER_LINE)
                    line_buffer[byte_idx + 1] &= ~out1;
                if (out2 && byte_idx + 2 < BYTES_PER_LINE)
                    line_buffer[byte_idx + 2] &= ~out2;
            } else {
                line_buffer[byte_idx] |= out0;
                if (byte_idx + 1 < BYTES_PER_LINE)
                    line_buffer[byte_idx + 1] |= out1;
                if (out2 && byte_idx + 2 < BYTES_PER_LINE)
                    line_buffer[byte_idx + 2] |= out2;
            }
        }
        sharp_write_line(display_line + 1, line_buffer, BYTES_PER_LINE);
    }
}
