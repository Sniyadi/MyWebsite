/**
 * MCP48CMD21 — 12-Bit Single-Channel DAC Driver
 *
 * @file mcp48cmd21.h
 *
 * @brief Device driver for the Microchip MCP48CMD21 12-bit voltage-output DAC
 *        with SPI interface. Provides write, read, power-down, and power-up
 *        operations on the volatile DAC0 output register.
 *
 * Device overview:
 *   The MCP48CMD21 is a single-channel, 12-bit buffered voltage output DAC
 *   with 1 LSb INL and SPI interface (Mode 0,0 or 1,1, up to 50 MHz write).
 *   It supports an external voltage reference (VREF pin), internal band gap,
 *   or VDD as the reference source. Output gain is selectable (1x or 2x).
 *
 * SPI protocol:
 *   All commands are 24-bit (3-byte) frames: [Command Byte] [Data High] [Data Low]
 *   Command byte: AD4:AD0 (5-bit address) | C1:C0 (command) | X (reserved)
 *   Commands: C1:C0 = 00 (Write), 11 (Read)
 *
 * Circuit context (EV34C35A reference design):
 *   - External 2.5V precision reference (MCP1501-25) on VREF pin
 *   - Gain = 1x, output range 0–2.5V
 *   - DAC code 0x000 → 0V (circuit outputs 4 mA, set by digipot)
 *   - DAC code 0xFFF → 2.5V (circuit outputs 20 mA)
 *   - LAT pin tied LOW (output updates immediately on write)
 *
 * Portability:
 *   This driver depends only on loop_driver_bsp.h for CS pin control and
 *   SPI functions. To use on a different board, adapt the BSP header.
 */

#ifndef MCP48CMD21_H
#define MCP48CMD21_H

#include <stdint.h>

/**
 * @brief Initialize the MCP48CMD21 DAC.
 *
 * Deasserts CS (idle HIGH) and sets the output to 0 (zero-scale).
 * In dummy mode, initializes the tracking variable to 0.
 */
void MCP48CMD21_Init(void);

/**
 * @brief Write a 12-bit code to the volatile DAC0 output register.
 *
 * The output voltage updates immediately (LAT pin tied LOW).
 * Values > 4095 are clamped to 4095.
 *
 * @param dac_code 12-bit output value (0–4095)
 */
void MCP48CMD21_Write(uint16_t dac_code);

/**
 * @brief Read back the current DAC0 output register value.
 *
 * In real mode, performs a 24-bit read transaction.
 * In dummy mode, returns the last value written.
 *
 * @return 12-bit DAC code (0–4095)
 */
uint16_t MCP48CMD21_Read(void);

/**
 * @brief Enter power-down mode (VOUT becomes high-impedance).
 *
 * Writes PD0B:PD0A = 11 to the volatile power-down register (address 09h),
 * which disconnects the output buffer and leaves VOUT open-circuit.
 * The DAC register value is retained and restored on power-up.
 */
void MCP48CMD21_PowerDown(void);

/**
 * @brief Exit power-down mode (resume normal output operation).
 *
 * Writes PD0B:PD0A = 00 to the volatile power-down register (address 09h),
 * which re-enables the output buffer. VOUT drives to the voltage
 * corresponding to the current DAC register value.
 */
void MCP48CMD21_PowerUp(void);

/**
 * @brief Configure VREF source to external pin, unbuffered.
 *
 * Writes VR0B:VR0A = 10 to the volatile VREF register (address 08h).
 * This selects the external VREF pin as the DAC reference voltage with
 * the internal buffer disabled (unbuffered mode).
 *
 * On the EV34C35A, the VREF pin is driven by an MCP1501-25 precision
 * 2.5V reference with low output impedance, so the internal buffer is
 * unnecessary. Using unbuffered mode avoids extra offset and current draw.
 *
 * This MUST be called before writing DAC codes, otherwise the device uses
 * VDD (~3.3V) as the reference (POR default), which destroys output accuracy.
 * Called automatically by MCP48CMD21_Init().
 */
void MCP48CMD21_SetVrefExternal(void);

#endif /* MCP48CMD21_H */
