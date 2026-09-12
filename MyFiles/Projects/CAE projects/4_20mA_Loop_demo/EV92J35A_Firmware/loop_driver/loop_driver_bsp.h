/**
 * Loop Driver Board Support Package
 *
 * @file loop_driver_bsp.h
 *
 * @brief Hardware abstraction layer for the EV34C35A 4-20 mA current loop
 *        driver board. Defines chip select macros, SPI configuration, and
 *        the dummy/real implementation toggle.
 *
 * This is the single file that contains all board-specific knowledge:
 *   - Which GPIO pins are the chip selects
 *   - Which MCC SPI configuration to use
 *   - Whether to compile real SPI code or dummy (in-memory) stubs
 *
 * Porting guide:
 *   To use the MCP48CMD21 and MCP4152 drivers on a different board, only
 *   this file needs to change. Update the #include paths to your MCC pins
 *   and SPI headers, then redefine the CS macros for your pin assignments.
 *
 * Hardware (EV34C35A on PIC18F56Q71 Curiosity Nano):
 *   - MCP48CMD21 (12-bit DAC):  CS on RC3, active-LOW
 *   - MCP4152 (8-bit digipot):  CS on RC1, active-LOW
 *   - Both share SPI1 with SHARP display via config switching
 *   - SPI Mode 0,0 (CKP=0, CKE=1), MSB-first, 500 kHz at 1 MHz Fosc
 */

#ifndef LOOP_DRIVER_BSP_H
#define LOOP_DRIVER_BSP_H

#include "../config.mcc/mcc_generated_files/system/pins.h"
#include "../config.mcc/mcc_generated_files/spi/spi1.h"

/**
 * Dummy/Real implementation toggle.
 *
 * Set to 1: Device drivers use static variables to track state (no SPI).
 *           Use this when the loop driver circuit is not connected.
 * Set to 0: Device drivers perform real SPI transactions.
 *           Use this when the EV34C35A board is wired up and ready.
 */
#define LOOP_DRIVER_USE_DUMMY   0

/**
 * MCP48CMD21 (External DAC) chip select — active-LOW.
 * RC3 on PIC18F56Q71 Curiosity Nano.
 */
#define LOOP_DAC_CS_ASSERT()        CS_LOOPDRIVER_DAC_SetLow()
#define LOOP_DAC_CS_DEASSERT()      CS_LOOPDRIVER_DAC_SetHigh()

/**
 * MCP4152 (Digital Potentiometer) chip select — active-LOW.
 * RC1 on PIC18F56Q71 Curiosity Nano.
 */
#define LOOP_DIGIPOT_CS_ASSERT()    CS_LOOPDRIVER_DIGIPOT_SetLow()
#define LOOP_DIGIPOT_CS_DEASSERT()  CS_LOOPDRIVER_DIGIPOT_SetHigh()

/**
 * SPI configuration index for both loop driver devices.
 * HOST_CONFIG: Mode 0,0, MSB-first, BAUD=3 (~125 kHz at Fosc=1 MHz).
 * Defined in MCC-generated spi1.c configuration array.
 */
#define LOOP_SPI_CONFIG             LOOP_DRIVER

#endif /* LOOP_DRIVER_BSP_H */
