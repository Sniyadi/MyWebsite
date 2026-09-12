# SHARP Memory Display Character Cell Driver

A RAM-efficient text display driver for the **Adafruit 1.3" SHARP Memory Display** (LS013B7DH03, 144x168 pixels) targeting Microchip PIC18 microcontrollers with XC8.

## Origin

- **Font data**: FreeMono 9pt from the [GNU FreeFont](https://www.gnu.org/software/freefont/) project (GPLv3), originally packaged as C headers by the [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library).
- **Display protocol**: Derived from the [Adafruit SHARP Memory Display Arduino library](https://github.com/adafruit/Adafruit_SHARP_Memory_Display), adapted for MCC-generated SPI on PIC18.
- **Architecture**: Designed and implemented with [Claude Code](https://claude.ai/claude-code) as a character cell model to minimize RAM usage on the PIC18F56Q71 (4 KB data memory).

## Architecture

Instead of a full 3 KB framebuffer (144x168/8 = 3024 bytes), this driver uses a **character cell model**:

- A 13x9 grid of ASCII characters (~117 bytes)
- Per-character font style attributes (~117 bytes)
- Dirty-line tracking (only modified rows are sent over SPI)
- Line-at-a-time rendering (18-byte line buffer, rendered on the fly)

**Total RAM usage: ~278 bytes** (vs 3024 for a full framebuffer).

## Features

- **4 font styles**: Normal, Bold, Oblique, Bold+Oblique (FreeMono 9pt monospace)
- **Per-character styling**: Mix bold and normal text on the same row
- **Per-row inversion**: White-on-black highlighting for menus/selection
- **printf API**: `screen_printf(row, col, "Temp: %d.%dC", t/10, t%10)`
- **Dirty tracking**: Only changed rows are sent to the display
- **Minimal dependencies**: Only needs MCC-generated SPI and GPIO

## Hardware Requirements

### Display Breakout Pinout (all 9 pins)

| Breakout Pin | Function | Connect To | Notes |
|--------------|----------|------------|-------|
| VIN | Power input | Board 3.3V or 5V | Powers the breakout board's onboard LDO |
| 3V3 | LDO output | **Nothing** | This is the breakout's regulated 3.3V OUTPUT. Do NOT connect to other board voltages. |
| GND | Ground | Board GND | Common ground reference |
| SCLK | SPI Clock | RC6 (SPI1 SCK) | Max 2 MHz. No minimum; lower clocks reduce power. |
| DI | SPI Data In (MOSI) | RC2 (SPI1 SDO) | Data from MCU to display |
| CS | Chip Select | RA5 (GPIO) | **Active HIGH** (unusual for SPI!) |
| EXTCOMIN | VCOM toggle | RD2 (NCO1 out) | ~2 Hz square wave prevents DC bias damage |
| DISP | Display enable | VCC (3.3V) | Tie HIGH to keep display always on |
| EXTMODE | VCOM mode select | VCC (3.3V) | Tie HIGH for external VCOM mode (EXTCOMIN) |

### SPI Configuration (in MCC)

- **Mode 0** (CPOL=0, CPHA=0)
- **LSB-first bit order** — The MCC GUI does not expose this option. After generating code, manually edit the SPI client configuration in the generated source to set LSB-first bit order (set the `LSBF` bit in the SPI bmode register, or modify the `SPI1_Open` configuration struct).
- **Clock: 2 MHz maximum**, no minimum. For low-power applications, slower clocks (100 kHz - 1 MHz) work fine; the display has no minimum clock speed requirement.
- **Client config named `SHARP_DISPLAY`** — This name is referenced in `sharp_mem.c` when calling `SPI1_Open(SHARP_DISPLAY)`.

## Integration into a New Project

1. **Copy this entire `sharp_display/` folder** into your project directory.

2. **Configure MCC** for your target MCU:
   - Add SPI1 host peripheral, Mode 0, LSB-first
   - Create a client config named `SHARP_DISPLAY`
   - Configure CS pin as output with macro name `CS_SCREEN`
   - Add NCO1 output at ~2 Hz for EXTCOMIN

3. **Update include paths** in `sharp_mem.c` to point to your MCC-generated headers:
   ```c
   #include "../path/to/mcc_generated_files/system/system.h"
   #include "../path/to/mcc_generated_files/spi/spi1.h"
   ```

4. **Include the API** in your application:
   ```c
   #include "path/to/sharp_display/screen.h"
   ```

5. **Call `screen_init()`** after `SYSTEM_Initialize()`.

## API Quick Reference

```c
// Initialization
screen_init();                          // Call once at startup

// Writing text
screen_printf(row, col, fmt, ...);      // Printf at position (clears to end of row)
screen_set_char(row, col, 'X');         // Single character

// Font styling (per-character, sticky)
screen_set_font_style(FONT_STYLE_BOLD);
screen_printf(0, 0, "Title");           // This text is bold
screen_set_font_style(FONT_STYLE_NORMAL);
screen_printf(1, 0, "Body");            // This text is normal

// Row highlighting (per-row)
screen_set_inverted(row, true);         // White on black
screen_set_inverted(row, false);        // Black on white (default)

// Clearing
screen_clear();                         // Entire screen
screen_clear_row(row);                  // Single row

// Display update (call after changes)
screen_refresh();                       // Send only dirty rows
screen_refresh_all();                   // Force all rows
```

## Memory Usage

| Resource | Usage |
|----------|-------|
| RAM | ~278 bytes (char buffer, style buffer, line buffer, etc.) |
| Flash - Fonts | ~6.7 KB (4 variants x ~1.5-1.8 KB each) |
| Flash - Code | ~1.5 KB (screen.c + sharp_mem.c) |

## File Overview

| File | Purpose |
|------|---------|
| `screen.h` | Public API (include this in your application) |
| `screen.c` | Character cell rendering engine |
| `sharp_mem.h` | Low-level SPI display interface |
| `sharp_mem.c` | SPI implementation (edit includes when porting) |
| `font_mono9.h` | FreeMono 9pt Regular + GFXglyph type definitions |
| `font_mono9_bold.h` | FreeMono 9pt Bold |
| `font_mono9_oblique.h` | FreeMono 9pt Oblique |
| `font_mono9_boldoblique.h` | FreeMono 9pt Bold+Oblique |

## License

Font data is from GNU FreeFont, licensed under GPLv3. The display driver code is provided without restriction for use in Microchip PIC projects.
