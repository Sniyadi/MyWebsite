/**
 * SHARP Memory Display - Low-Level SPI Driver
 *
 * @file sharp_mem.h
 *
 * @brief Hardware abstraction layer for the Adafruit 1.3" SHARP Memory
 *        Display (LS013B7DH03, 144x168 pixels). Handles SPI communication
 *        and display protocol. Called internally by screen.c.
 *
 * Hardware Requirements:
 *   - SPI peripheral: Mode 0, LSB-first, max 2 MHz clock (no minimum)
 *   - MCC SPI client config named "SHARP_DISPLAY"
 *   - GPIO pin for CS (active HIGH!) with macros CS_SHARP_SetHigh/SetLow
 *   - NCO or timer output for EXTCOMIN (~2Hz square wave for VCOM)
 *
 * Adafruit Breakout Pinout (all 9 pins):
 *   VIN      -> Board 3.3V or 5V (powers the breakout's onboard LDO)
 *   3V3      -> NOTHING (this is the LDO's output, not an input!)
 *   GND      -> Board GND
 *   SCLK     -> RC6 (SPI1 SCK)
 *   DI       -> RC2 (SPI1 SDO, data from MCU to display)
 *   CS       -> RA5 (GPIO, active HIGH - unusual for SPI)
 *   EXTCOMIN -> RD2 (NCO1 output, ~2Hz square wave)
 *   DISP     -> VCC (tie HIGH to keep display always on)
 *   EXTMODE  -> VCC (tie HIGH for external VCOM mode)
 *
 * Porting Notes:
 *   To use with a different MCU, update the #include paths in sharp_mem.c
 *   to point to your MCC-generated SPI and system headers. The pin macros
 *   (CS_SHARP_SetHigh, CS_SHARP_SetLow) come from MCC's pins.h.
 */

#ifndef SHARP_MEM_H
#define SHARP_MEM_H

#include <stdint.h>
#include <stdbool.h>

#define SHARP_WIDTH   144
#define SHARP_HEIGHT  168

/**
 * @brief Initialize display hardware (sets CS low).
 * @return true on success
 */
bool sharp_init(void);

/**
 * @brief Clear entire display to white using hardware clear command.
 */
void sharp_clear_display(void);

/**
 * @brief Begin a multi-line write transaction.
 * Opens SPI, asserts CS HIGH, sends write command byte.
 * Must be paired with sharp_end_frame().
 */
void sharp_begin_frame(void);

/**
 * @brief End a multi-line write transaction.
 * Sends trailer byte, deasserts CS, closes SPI.
 */
void sharp_end_frame(void);

/**
 * @brief Write one scan line of pixel data.
 * Must be called between sharp_begin_frame() and sharp_end_frame().
 * @param line_num Line number (1-based, 1 to 168)
 * @param data     Pixel data (18 bytes for 144 pixels, LSB=leftmost)
 * @param len      Number of data bytes (18 for full width)
 */
void sharp_write_line(uint8_t line_num, const uint8_t *data, uint8_t len);

#endif /* SHARP_MEM_H */
