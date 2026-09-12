/**
 * Loop Driver Board-Level API — Implementation
 *
 * @file loop_driver.c
 *
 * @brief Facade that composes the MCP48CMD21 and MCP4152 device drivers into
 *        the board-level LoopDriver_* API, and owns the Current-to-DAC
 *        transfer function and its calibration constants.
 *
 * This module provides:
 *   1. Single init point — LoopDriver_Init() initializes both devices.
 *   2. Calibration constant storage — digipot_trim, dac_at_4mA, dac_at_20mA.
 *   3. Current-to-DAC transfer function — derived from dac_at_4mA/dac_at_20mA,
 *      fully encapsulated (no external access to raw slope/intercept).
 *   4. Pre-computed inverse — avoids 32-bit division at runtime.
 *
 * Current-to-DAC transfer function (Q16 format):
 *   Forward: dac_code = (slope_q16 * current_mA_q16) >> 16 + intercept_q16) >> 16
 *   Inverse: mA_q16 = inv_slope_q16 * (dac_counts + neg_intercept_int)
 *
 *   Derived from two calibration points:
 *     4.000 mA -> dac_at_4mA
 *     20.000 mA -> dac_at_20mA
 *
 * Extended loop range:
 *   DAC=0 with digipot trimmed -> ~3.6 mA (low alarm floor)
 *   DAC=dac_at_4mA            -> 4.000 mA (valid measurement low)
 *   DAC=dac_at_20mA           -> 20.000 mA (valid measurement high)
 *   DAC=4095                  -> ~22 mA (high alarm ceiling)
 */

#include "loop_driver.h"
#include "loop_driver_constants.h"
#include "mcp48cmd21.h"
#include "mcp4152.h"

/* --- Calibration constants (source of truth for this module) --- */

static uint8_t  loop_digipot_trim;
static uint16_t loop_dac_at_4mA;
static uint16_t loop_dac_at_20mA;

/* --- Current-to-DAC transfer function parameters (Q16, derived) --- */

static int32_t current_to_dac_slope_q16;
static int32_t current_to_dac_intercept_q16;

/* --- Inverse transfer function parameters (pre-computed, division-free) --- */

static int32_t inv_slope_q16;
static int32_t neg_intercept_int;

/* --- Cached last-written DAC value (skips redundant SPI writes) --- */

static uint16_t last_written_dac;

/* ======================================================================== */
/* Initialization                                                           */
/* ======================================================================== */

void LoopDriver_Init(void) {
    MCP48CMD21_Init();
    MCP4152_Init();

    last_written_dac = 0xFFFF;

    loop_digipot_trim = LOOP_DRIVER_DEFAULT_DIGIPOT_TRIM;
    loop_dac_at_4mA   = LOOP_DRIVER_DEFAULT_DAC_AT_4MA;
    loop_dac_at_20mA  = LOOP_DRIVER_DEFAULT_DAC_AT_20MA;

    LoopDriver_RecomputeTransfer();
}

/* ======================================================================== */
/* Calibration Constant Setters                                             */
/* ======================================================================== */

void LoopDriver_SetDigipotTrim(uint8_t value) {
    loop_digipot_trim = value;
    MCP4152_WriteWiper(value);
}

void LoopDriver_SetDacAt4mA(uint16_t value) {
    loop_dac_at_4mA = value;
}

void LoopDriver_SetDacAt20mA(uint16_t value) {
    loop_dac_at_20mA = value;
}

/* ======================================================================== */
/* Calibration Constant Getters                                             */
/* ======================================================================== */

uint8_t LoopDriver_GetDigipotTrim(void) {
    return loop_digipot_trim;
}

uint16_t LoopDriver_GetDacAt4mA(void) {
    return loop_dac_at_4mA;
}

uint16_t LoopDriver_GetDacAt20mA(void) {
    return loop_dac_at_20mA;
}

/* ======================================================================== */
/* Current-to-DAC Transfer Function Derivation                              */
/* ======================================================================== */

void LoopDriver_RecomputeTransfer(void) {
    /* Two-point fit: 4.0 mA -> dac_at_4mA, 20.0 mA -> dac_at_20mA
     *
     * slope_real = (dac_at_20mA - dac_at_4mA) / 16.0  [DAC codes per mA]
     * slope_q16  = dac_delta * 65536 / 16 = dac_delta * 4096
     *
     * intercept from: dac_at_4mA = slope_real * 4.0 + intercept_real
     * intercept_q16 = (dac_at_4mA << 16) - slope_q16 * 4 */
    int32_t dac_delta = (int32_t)loop_dac_at_20mA - (int32_t)loop_dac_at_4mA;

    current_to_dac_slope_q16 = dac_delta * 4096L;
    current_to_dac_intercept_q16 =
        ((int32_t)loop_dac_at_4mA << 16) - current_to_dac_slope_q16 * 4L;

    /* Pre-compute inverse for division-free LoopDriver_ComputeCurrent_mA_q16():
     *   inv_slope_q16 = 65536 * 256 / (slope_q16 >> 8)
     *   neg_intercept_int = -(intercept_q16 >> 16)
     *
     * Formula: mA_q16 = inv_slope_q16 * (dac_counts + neg_intercept_int) */
    int32_t slope_q8 = current_to_dac_slope_q16 >> 8;
    if (slope_q8 != 0) {
        inv_slope_q16 = (65536L * 256L) / slope_q8;
    } else {
        inv_slope_q16 = 0;
    }
    neg_intercept_int = -(current_to_dac_intercept_q16 >> 16);
}

/* ======================================================================== */
/* External DAC (MCP48CMD21)                                                */
/* ======================================================================== */

void LoopDriver_SetDac(uint16_t counts) {
    if (counts > LOOP_DAC_MAX) counts = LOOP_DAC_MAX;
    if (counts == last_written_dac) return;
    MCP48CMD21_Write(counts);
    last_written_dac = counts;
}

uint16_t LoopDriver_GetDac(void) {
    return MCP48CMD21_Read();
}

/* ======================================================================== */
/* Current-Based Interface (uses Current-to-DAC transfer function)          */
/* ======================================================================== */

void LoopDriver_SetCurrent_mA_q16(int32_t current_mA_q16) {
    /* Forward Current-to-DAC: dac = slope * mA + intercept (all Q16).
     *
     * To avoid overflow (slope_q16 * current_q16 can exceed int32), use the
     * split-multiply approach: shift both operands right by 8 first,
     * then multiply to get a Q16 result directly (Q8 * Q8 = Q16). */
    uint16_t s_q8 = (uint16_t)(current_to_dac_slope_q16 >> 8);
    int16_t c_q8  = (int16_t)(current_mA_q16 >> 8);

    int32_t result_q16 = (int32_t)s_q8 * (int32_t)c_q8
                       + current_to_dac_intercept_q16;
    int16_t dac_code = (int16_t)(result_q16 >> 16);

    if (dac_code < 0) dac_code = 0;
    if (dac_code > (int16_t)LOOP_DAC_MAX) dac_code = (int16_t)LOOP_DAC_MAX;

    MCP48CMD21_Write((uint16_t)dac_code);
    last_written_dac = (uint16_t)dac_code;
}

int32_t LoopDriver_ComputeCurrent_mA_q16(uint16_t dac_counts) {
    /* Inverse Current-to-DAC: mA = (dac - intercept) / slope
     * Using pre-computed inverse: mA_q16 = inv_slope_q16 * (dac + neg_intercept) */
    if (dac_counts > LOOP_DAC_MAX) dac_counts = LOOP_DAC_MAX;
    int32_t adjusted = (int32_t)dac_counts + neg_intercept_int;
    return inv_slope_q16 * adjusted;
}

/* ======================================================================== */
/* Digital Potentiometer (MCP4152) — direct hardware access                 */
/* ======================================================================== */

void LoopDriver_SetDigipot(uint8_t position) {
    MCP4152_WriteWiper(position);
}

uint8_t LoopDriver_GetDigipot(void) {
    return MCP4152_ReadWiper();
}

void LoopDriver_IncrementDigipot(void) {
    MCP4152_Increment();
}

void LoopDriver_DecrementDigipot(void) {
    MCP4152_Decrement();
}
