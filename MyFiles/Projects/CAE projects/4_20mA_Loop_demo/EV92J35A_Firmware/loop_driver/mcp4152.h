/**
 * MCP4152 — 8-Bit Single-Channel Digital Potentiometer Driver
 *
 * @file mcp4152.h
 *
 * @brief Device driver for the Microchip MCP4152 8-bit SPI digital
 *        potentiometer (257 steps, volatile memory, rheostat configuration).
 *        Provides write, read, increment, and decrement operations on the
 *        volatile wiper 0 register.
 *
 * Device overview:
 *   The MCP4152 is a single-channel 8-bit digital potentiometer with SPI
 *   interface (Mode 0,0 or 1,1, up to 10 MHz). It has 256 resistors in a
 *   string between terminals A and B, with 257 possible wiper positions
 *   (0x000 = terminal B through 0x100 = terminal A). The device uses
 *   volatile (RAM) memory — wiper resets to mid-scale (0x80) on power-up.
 *
 * SPI protocol:
 *   - 16-bit frame (write/read): [Command Byte] [Data Byte]
 *   - 8-bit frame (increment/decrement): [Command Byte] only
 *   Command byte: AD3:AD0 (4-bit address) | C1:C0 (command) | D9:D8 (data)
 *   Commands: C1:C0 = 00 (Write), 11 (Read), 01 (Increment), 10 (Decrement)
 *
 * Circuit context (EV34C35A reference design):
 *   The MCP4152-503 (50 kΩ) provides offset trimming for the 4 mA zero-point
 *   of the current loop driver. When the DAC outputs 0V, the digipot sets the
 *   exact 4 mA low-scale current. Mid-scale (128) is the factory default.
 *
 * Wiper range:
 *   Although the device supports positions 0–256 (9-bit), this driver exposes
 *   a uint8_t interface (0–255) for simplicity. Position 256 (full-scale,
 *   wiper connected directly to terminal A) is not needed in this application
 *   and would require a wider type for a single edge case.
 *
 * Portability:
 *   This driver depends only on loop_driver_bsp.h for CS pin control and
 *   SPI functions. To use on a different board, adapt the BSP header.
 */

#ifndef MCP4152_H
#define MCP4152_H

#include <stdint.h>

/**
 * @brief Initialize the MCP4152 digital potentiometer.
 *
 * Deasserts CS (idle HIGH). In dummy mode, sets the tracking variable
 * to the POR default (mid-scale = 0x80).
 */
void MCP4152_Init(void);

/**
 * @brief Write a wiper position to the volatile wiper 0 register.
 *
 * @param position Wiper position (0–255). The device supports 0–256 but
 *                 this driver limits to uint8_t range for simplicity.
 */
void MCP4152_WriteWiper(uint8_t position);

/**
 * @brief Read back the current wiper 0 position.
 *
 * In real mode, performs a 16-bit read transaction.
 * In dummy mode, returns the last written/incremented/decremented value.
 *
 * @return Current wiper position (0–255)
 */
uint8_t MCP4152_ReadWiper(void);

/**
 * @brief Increment the wiper position by 1.
 *
 * Uses the device's native 8-bit increment command for efficiency (no data
 * byte needed). The device internally clamps at full-scale (0x100); this
 * driver clamps the tracked value at 255.
 */
void MCP4152_Increment(void);

/**
 * @brief Decrement the wiper position by 1.
 *
 * Uses the device's native 8-bit decrement command for efficiency. The
 * device internally clamps at zero-scale (0x000); this driver clamps at 0.
 */
void MCP4152_Decrement(void);

#endif /* MCP4152_H */
