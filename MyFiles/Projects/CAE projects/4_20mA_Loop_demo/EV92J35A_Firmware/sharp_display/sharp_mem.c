/**
 * SHARP Memory Display Low-Level Driver for PIC18F56Q71
 *
 * @file sharp_mem.c
 *
 * @brief Low-level SPI interface for SHARP Memory Display (LS013B7DH03).
 *
 * CS is active-HIGH (unusual for SPI) and is controlled via GPIO, not the
 * SPI peripheral's hardware SS. The SPI is configured LSB-first (LSBF=1)
 * to match the display's native bit ordering.
 *
 * Line pixel data (18 bytes) is sent via SPI1_BufferWrite() as a single
 * block transfer to minimize per-byte setup overhead. The line number and
 * trailer bytes are sent individually via SPI1_ByteExchange().
 */

#include "sharp_mem.h"
#include "../config.mcc/mcc_generated_files/system/system.h"
#include "../config.mcc/mcc_generated_files/spi/spi1.h"

#define SHARPMEM_BIT_WRITECMD   0x01
#define SHARPMEM_BIT_CLEAR      0x04

static void spi_begin(void) {
    SPI1_Close();
    SPI1_Open(SHARP_DISPLAY);
}

static void spi_end(void) {
    SPI1_Close();
}

static void spi_write_byte(uint8_t data) {
    SPI1_ByteExchange(data);
}

bool sharp_init(void) {
    CS_SHARP_SetLow();
    return true;
}

void sharp_clear_display(void) {
    spi_begin();
    CS_SHARP_SetHigh();

    spi_write_byte(SHARPMEM_BIT_CLEAR);
    spi_write_byte(0x00);

    CS_SHARP_SetLow();
    spi_end();
}

void sharp_begin_frame(void) {
    spi_begin();
    CS_SHARP_SetHigh();
    spi_write_byte(SHARPMEM_BIT_WRITECMD);
}

void sharp_end_frame(void) {
    spi_write_byte(0x00);
    CS_SHARP_SetLow();
    spi_end();
}

void sharp_write_line(uint8_t line_num, const uint8_t *data, uint8_t len) {
    spi_write_byte(line_num);
    SPI1_BufferWrite((void *)data, len);
    spi_write_byte(0x00);
}
