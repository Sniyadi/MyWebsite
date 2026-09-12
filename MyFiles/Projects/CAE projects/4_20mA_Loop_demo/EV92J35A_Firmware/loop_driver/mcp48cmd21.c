/**
 * MCP48CMD21 — 12-Bit Single-Channel DAC Driver Implementation
 *
 * @file mcp48cmd21.c
 *
 * @brief SPI protocol implementation for the MCP48CMD21 DAC. Contains both
 *        the real hardware driver and a dummy (in-memory) implementation,
 *        selectable via LOOP_DRIVER_USE_DUMMY in loop_driver_bsp.h. Init
 *        configures VREF to external unbuffered (MCP1501-25) before first use.
 *
 * SPI frame format (24-bit, MSB-first):
 *   Byte 1: [AD4 AD3 AD2 AD1 AD0 | C1 C0 | X]  — Command byte
 *   Byte 2: [x   x   x   x  | D11 D10 D9 D8]   — Data high (upper 4 bits unused)
 *   Byte 3: [D7  D6  D5  D4 | D3  D2  D1 D0]   — Data low
 *
 * Transaction sequence (same pattern as SHARP display driver):
 *   1. SPI1_Open(HOST_CONFIG) — select Mode 0,0 MSB-first config
 *   2. Assert CS (drive LOW)
 *   3. Clock out 3 bytes via SPI1_ByteExchange()
 *   4. Deassert CS (drive HIGH)
 *   5. SPI1_Close() — release SPI peripheral for other devices
 *
 * Memory map addresses used:
 *   0x00 — Volatile DAC0 Output Register (12-bit, right-justified)
 *   0x08 — Volatile VREF Register (bits 1:0 = VR0B:VR0A for single-channel)
 *   0x09 — Volatile Power-Down Register (bits 1:0 = PD0B:PD0A)
 */

#include "mcp48cmd21.h"
#include "loop_driver_bsp.h"

/* Command byte construction macros.
 * Address occupies bits 7:3, command occupies bits 2:1, bit 0 is reserved. */
#define MCP48CMD21_CMD_WRITE        0x00u   /* C1:C0 = 00, shifted into bits 2:1 */
#define MCP48CMD21_CMD_READ         0x06u   /* C1:C0 = 11, shifted into bits 2:1 */

/* Address constants (pre-shifted into bits 7:3 of the command byte) */
#define MCP48CMD21_ADDR_DAC0        0x00u   /* Address 00h << 3 = 0x00 */
#define MCP48CMD21_ADDR_VREF        0x40u   /* Address 08h << 3 = 0x40 */
#define MCP48CMD21_ADDR_POWERDOWN   0x48u   /* Address 09h << 3 = 0x48 */

/* Power-down mode bits (written to data word bits 1:0) */
#define MCP48CMD21_PD_NORMAL        0x00u   /* PD0B:PD0A = 00 — normal operation */
#define MCP48CMD21_PD_OPEN_CIRCUIT  0x03u   /* PD0B:PD0A = 11 — VOUT open */

/* VREF source selection bits (written to data word bits 1:0) */
#define MCP48CMD21_VREF_VDD         0x00u   /* VR0B:VR0A = 00 — VDD (POR default) */
#define MCP48CMD21_VREF_EXT_UNBUF   0x02u   /* VR0B:VR0A = 10 — External, unbuffered */
#define MCP48CMD21_VREF_EXT_BUF     0x03u   /* VR0B:VR0A = 11 — External, buffered */

#if LOOP_DRIVER_USE_DUMMY

/* ========================================================================
 * DUMMY IMPLEMENTATION — tracks DAC state in RAM, no SPI transactions.
 * Used when the EV34C35A board is not connected.
 * ======================================================================== */

static uint16_t dummy_dac_value = 0;
static bool     dummy_powered_down = false;
static bool     dummy_vref_external = false;

void MCP48CMD21_Init(void) {
    dummy_dac_value = 0;
    dummy_powered_down = false;
    MCP48CMD21_SetVrefExternal();
}

void MCP48CMD21_Write(uint16_t dac_code) {
    if (dac_code > 4095u) dac_code = 4095u;
    dummy_dac_value = dac_code;
}

uint16_t MCP48CMD21_Read(void) {
    return dummy_dac_value;
}

void MCP48CMD21_PowerDown(void) {
    dummy_powered_down = true;
}

void MCP48CMD21_PowerUp(void) {
    dummy_powered_down = false;
}

void MCP48CMD21_SetVrefExternal(void) {
    dummy_vref_external = true;
}

#else

/* ========================================================================
 * REAL IMPLEMENTATION — performs SPI transactions with the MCP48CMD21.
 * Enable by setting LOOP_DRIVER_USE_DUMMY to 0 in loop_driver_bsp.h.
 * ======================================================================== */

void MCP48CMD21_Init(void) {
    LOOP_DAC_CS_DEASSERT();
    MCP48CMD21_SetVrefExternal();
    MCP48CMD21_Write(0);
}

void MCP48CMD21_Write(uint16_t dac_code) {
    if (dac_code > 4095u) dac_code = 4095u;

    uint8_t cmd  = MCP48CMD21_ADDR_DAC0 | MCP48CMD21_CMD_WRITE;
    uint8_t high = (uint8_t)(dac_code >> 8);
    uint8_t low  = (uint8_t)(dac_code & 0xFFu);

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DAC_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    SPI1_ByteExchange(high);
    SPI1_ByteExchange(low);
    LOOP_DAC_CS_DEASSERT();
    SPI1_Close();
}

uint16_t MCP48CMD21_Read(void) {
    uint8_t cmd = MCP48CMD21_ADDR_DAC0 | MCP48CMD21_CMD_READ;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DAC_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    uint8_t high = SPI1_ByteExchange(0x00);
    uint8_t low  = SPI1_ByteExchange(0x00);
    LOOP_DAC_CS_DEASSERT();
    SPI1_Close();

    return (uint16_t)((high & 0x0Fu) << 8) | low;
}

void MCP48CMD21_PowerDown(void) {
    uint8_t cmd = MCP48CMD21_ADDR_POWERDOWN | MCP48CMD21_CMD_WRITE;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DAC_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    SPI1_ByteExchange(0x00);
    SPI1_ByteExchange(MCP48CMD21_PD_OPEN_CIRCUIT);
    LOOP_DAC_CS_DEASSERT();
    SPI1_Close();
}

void MCP48CMD21_PowerUp(void) {
    uint8_t cmd = MCP48CMD21_ADDR_POWERDOWN | MCP48CMD21_CMD_WRITE;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DAC_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    SPI1_ByteExchange(0x00);
    SPI1_ByteExchange(MCP48CMD21_PD_NORMAL);
    LOOP_DAC_CS_DEASSERT();
    SPI1_Close();
}

void MCP48CMD21_SetVrefExternal(void) {
    uint8_t cmd = MCP48CMD21_ADDR_VREF | MCP48CMD21_CMD_WRITE;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DAC_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    SPI1_ByteExchange(0x00);
    SPI1_ByteExchange(MCP48CMD21_VREF_EXT_UNBUF);
    LOOP_DAC_CS_DEASSERT();
    SPI1_Close();
}

#endif /* LOOP_DRIVER_USE_DUMMY */
