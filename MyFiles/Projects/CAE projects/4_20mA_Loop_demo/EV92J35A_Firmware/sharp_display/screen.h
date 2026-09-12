/**
 * SHARP Memory Display - Character Cell Driver
 *
 * @file screen.h
 *
 * @brief RAM-efficient text display driver for the Adafruit 1.3" SHARP Memory
 *        Display (144x168). Uses a character cell model with dirty-line
 *        tracking to minimize SPI traffic and RAM usage (~278 bytes total).
 *
 * Features:
 *   - 13 columns x 9 rows text grid (FreeMono 9pt, 11x18 pixel cells)
 *   - printf-style formatted output
 *   - Per-character font style (Normal, Bold, Oblique, Bold+Oblique)
 *   - Per-row inversion (white-on-black)
 *   - Dirty-line tracking (only changed rows are sent to display)
 *
 * Typical usage:
 *   screen_init();
 *   screen_set_font_style(FONT_STYLE_BOLD);
 *   screen_printf(0, 0, "Hello World");
 *   screen_set_font_style(FONT_STYLE_NORMAL);
 *   screen_printf(1, 0, "Temp: %d.%dC", t/10, t%10);
 *   screen_refresh();
 *
 * Origin: Ported from Adafruit GFX Library (Arduino) to PIC18 XC8.
 *         Font data from GNU FreeFont project (GPLv3).
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdbool.h>

/* Display grid dimensions */
#define SCREEN_ROWS         9       /* Text rows (168 / 18 = 9) */
#define SCREEN_COLS         13      /* Text columns (144 / 11 = 13) */

/* Pixel dimensions of each character cell */
#define CELL_WIDTH          11      /* FreeMono 9pt xAdvance */
#define CELL_HEIGHT         18      /* FreeMono 9pt yAdvance */

/* Row attribute flags (used internally) */
#define ROW_ATTR_INVERTED   0x01

/* Font style constants for screen_set_font_style() */
#define FONT_STYLE_NORMAL       0x00    /* Regular weight, upright */
#define FONT_STYLE_BOLD         0x01    /* Bold weight, upright */
#define FONT_STYLE_OBLIQUE      0x02    /* Regular weight, slanted */
#define FONT_STYLE_BOLD_OBLIQUE 0x03    /* Bold weight, slanted */

/**
 * @brief Initialize the display hardware and clear the screen.
 *
 * Must be called once after SYSTEM_Initialize(). Configures SPI, clears
 * the SHARP display hardware, and renders an empty text grid.
 *
 * Example:
 *   SYSTEM_Initialize();
 *   screen_init();
 */
void screen_init(void);

/**
 * @brief Clear the entire screen to spaces and reset all attributes.
 *
 * Resets font styles to NORMAL and inversion to OFF for all rows.
 * The display is not updated until screen_refresh() is called.
 *
 * Example:
 *   screen_clear();
 *   screen_printf(0, 0, "Fresh start");
 *   screen_refresh();
 */
void screen_clear(void);

/**
 * @brief Clear a single row to spaces and reset its attributes.
 *
 * @param row Row number (0 to SCREEN_ROWS-1)
 *
 * Example:
 *   screen_clear_row(3);  // Blank row 3, remove inversion
 *   screen_refresh();
 */
void screen_clear_row(uint8_t row);

/**
 * @brief Set a single character at a position using the current font style.
 *
 * Does NOT clear other characters on the row. Useful for updating
 * individual characters without reformatting the entire row.
 *
 * @param row Row number (0 to SCREEN_ROWS-1)
 * @param col Column number (0 to SCREEN_COLS-1)
 * @param c   ASCII character (0x20-0x7E)
 *
 * Example:
 *   screen_set_char(0, 12, '>');  // Place cursor indicator
 */
void screen_set_char(uint8_t row, uint8_t col, char c);

/**
 * @brief Printf-style formatted text output to a row.
 *
 * Writes formatted text starting at (row, col) using the current font
 * style. All columns from end-of-string to end-of-row are cleared to
 * spaces (prevents stale characters when updating shorter strings).
 *
 * @param row Row number (0 to SCREEN_ROWS-1)
 * @param col Starting column (0 to SCREEN_COLS-1)
 * @param fmt Printf format string
 * @param ... Format arguments
 *
 * Example:
 *   screen_printf(0, 0, "RPM: %5u", rpm);
 *   screen_printf(1, 0, "T: %3d.%dC", temp/10, temp%10);
 */
void screen_printf(uint8_t row, uint8_t col, const char *fmt, ...);

/**
 * @brief Set row inversion (white text on black background).
 *
 * Inversion is a row-level attribute. Useful for menu selection
 * highlighting or status bars.
 *
 * @param row      Row number (0 to SCREEN_ROWS-1)
 * @param inverted true = white-on-black, false = black-on-white
 *
 * Example:
 *   screen_set_inverted(selected_row, true);   // Highlight
 *   screen_set_inverted(prev_row, false);      // Un-highlight
 *   screen_refresh();
 */
void screen_set_inverted(uint8_t row, bool inverted);

/**
 * @brief Set a row back to normal (black text on white background).
 *
 * Convenience wrapper for screen_set_inverted(row, false).
 *
 * @param row Row number (0 to SCREEN_ROWS-1)
 */
void screen_set_normal(uint8_t row);

/**
 * @brief Set the font style for subsequent text output.
 *
 * Affects all following screen_printf() and screen_set_char() calls.
 * The style is "sticky" - it remains active until changed.
 * screen_clear() does NOT reset the current style.
 *
 * @param style One of FONT_STYLE_NORMAL, FONT_STYLE_BOLD,
 *              FONT_STYLE_OBLIQUE, or FONT_STYLE_BOLD_OBLIQUE
 *
 * Example:
 *   screen_set_font_style(FONT_STYLE_BOLD);
 *   screen_printf(0, 0, "Title");
 *   screen_set_font_style(FONT_STYLE_NORMAL);
 *   screen_printf(1, 0, "Body text");
 */
void screen_set_font_style(uint8_t style);

/**
 * @brief Send changed rows to the display.
 *
 * Only rows modified since the last refresh are transmitted over SPI.
 * Call this after making all your text/attribute changes for a frame.
 * Typical refresh of 1-2 dirty rows takes <2ms at 2MHz SPI.
 *
 * Example:
 *   screen_printf(2, 0, "Value: %d", val);
 *   screen_refresh();  // Only row 2 is sent
 */
void screen_refresh(void);

/**
 * @brief Force-refresh the entire display (all 9 rows).
 *
 * Useful after waking from sleep or to recover from display glitches.
 * Takes ~9ms at 2MHz SPI.
 */
void screen_refresh_all(void);

#endif /* SCREEN_H */
