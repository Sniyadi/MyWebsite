/**
 * MCP4152 — 8-Bit Digital Potentiometer Driver Implementation
 *
 * @file mcp4152.c
 *
 * @brief SPI protocol implementation for the MCP4152 digital potentiometer.
 *        Contains both the real hardware driver and a dummy (in-memory)
 *        implementation, selectable via LOOP_DRIVER_USE_DUMMY in loop_driver_bsp.h.
 *
 * SPI frame formats (MSB-first, Mode 0,0):
 *
 *   16-bit Write: [AD3:AD0 | 00 | D9 D8] [D7:D0]
 *     Address 0000 (wiper 0), Write command 00, D9 unused (0), D8 = MSbit
 *     Byte 1 = 0x00 | (position >> 8)    — always 0x00 or 0x01
 *     Byte 2 = position & 0xFF
 *
 *   16-bit Read:  [AD3:AD0 | 11 | X  X ] [don't care]
 *     Byte 1 = 0x0C (address 0000, read command 11, don't-care data bits)
 *     SDO returns: CMDERR bit on clock 7, then D8:D0 on clocks 8–16
 *
 *   8-bit Increment: [AD3:AD0 | 01 | X X]
 *     Byte 1 = 0x04 (address 0000, increment command 01)
 *
 *   8-bit Decrement: [AD3:AD0 | 10 | X X]
 *     Byte 1 = 0x08 (address 0000, decrement command 10)
 *
 * Transaction sequence:
 *   SPI1_Open(HOST_CONFIG) → CS LOW → clock bytes → CS HIGH → SPI1_Close()
 */

#include "mcp4152.h"
#include "loop_driver_bsp.h"

/* Command byte constants for wiper 0 (address 0000).
 * Bits 7:4 = address, bits 3:2 = command, bits 1:0 = D9:D8 or don't-care. */
#define MCP4152_CMD_WRITE       0x00u   /* 0000_00_xx — Write wiper 0 */
#define MCP4152_CMD_READ        0x0Cu   /* 0000_11_xx — Read wiper 0 */
#define MCP4152_CMD_INCREMENT   0x04u   /* 0000_01_xx — Increment wiper 0 */
#define MCP4152_CMD_DECREMENT   0x08u   /* 0000_10_xx — Decrement wiper 0 */

#define MCP4152_DEFAULT_WIPER   0x80u   /* matches POR value */

#if LOOP_DRIVER_USE_DUMMY

/* ========================================================================
 * DUMMY IMPLEMENTATION — tracks wiper state in RAM, no SPI transactions.
 * Used when the EV34C35A board is not connected.
 * ======================================================================== */

static uint8_t dummy_wiper = 0x80u;     /* POR default: mid-scale */

void MCP4152_Init(void) {
    dummy_wiper = 0x80u;
}

void MCP4152_WriteWiper(uint8_t position) {
    dummy_wiper = position;
}

uint8_t MCP4152_ReadWiper(void) {
    return dummy_wiper;
}

void MCP4152_Increment(void) {
    if (dummy_wiper < 255u) {
        dummy_wiper++;
    }
}

void MCP4152_Decrement(void) {
    if (dummy_wiper > 0u) {
        dummy_wiper--;
    }
}

#else

/* ========================================================================
 * REAL IMPLEMENTATION — performs SPI transactions with the MCP4152.
 * Enable by setting LOOP_DRIVER_USE_DUMMY to 0 in loop_driver_bsp.h.
 * ======================================================================== */

void MCP4152_Init(void) {
    LOOP_DIGIPOT_CS_DEASSERT();
    MCP4152_WriteWiper(MCP4152_DEFAULT_WIPER);
}

void MCP4152_WriteWiper(uint8_t position) {
    /* D8 is always 0 for positions 0–255 (bit 8 = 0).
     * The command byte D9:D8 bits are 00, so cmd = 0x00. */
    uint8_t cmd  = MCP4152_CMD_WRITE;
    uint8_t data = position;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DIGIPOT_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    SPI1_ByteExchange(data);
    LOOP_DIGIPOT_CS_DEASSERT();
    SPI1_Close();
}

uint8_t MCP4152_ReadWiper(void) {
    uint8_t cmd = MCP4152_CMD_READ;

    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DIGIPOT_CS_ASSERT();
    SPI1_ByteExchange(cmd);
    uint8_t data = SPI1_ByteExchange(0xFF);
    LOOP_DIGIPOT_CS_DEASSERT();
    SPI1_Close();

    /* Data byte contains D7:D0. D8 was in bit 0 of the command response
     * but we limit to 0–255 so we only need the data byte. */
    return data;
}

void MCP4152_Increment(void) {
    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DIGIPOT_CS_ASSERT();
    SPI1_ByteExchange(MCP4152_CMD_INCREMENT);
    LOOP_DIGIPOT_CS_DEASSERT();
    SPI1_Close();
}

void MCP4152_Decrement(void) {
    SPI1_Open(LOOP_SPI_CONFIG);
    LOOP_DIGIPOT_CS_ASSERT();
    SPI1_ByteExchange(MCP4152_CMD_DECREMENT);
    LOOP_DIGIPOT_CS_DEASSERT();
    SPI1_Close();
}

#endif /* LOOP_DRIVER_USE_DUMMY */
