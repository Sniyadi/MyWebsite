/**
 * State Machine Context — Implementation (Constants-Centric Calibration)
 *
 * @file sm_context.c
 *
 * @brief Stores sensor/AFE calibration constants and user range settings as
 *        file-scope statics. Derives transfer function parameters from those
 *        constants (and the loop_driver's calibrated DAC endpoints) via
 *        SmContext_RecomputeTransferFunctions(). Provides the linear
 *        computation functions used by the per-tick hot path.
 *
 * Software architecture:
 *   CalibrationConstants_t and RangeSettings_t are the source of truth for
 *   this module. The loop_driver module owns its own calibration constants
 *   (dac_at_4mA, dac_at_20mA, digipot_trim) and the Current-to-DAC transfer
 *   function. This module reads the loop_driver's DAC endpoints via getters
 *   to derive the composite ADC-to-DAC mapping.
 *
 * Derived transfer functions (owned by this module):
 *   ADC-to-Current:  ADC counts -> mA       (used by ComputeLoopCurrent_mA_q16)
 *   ADC-to-Pressure: ADC counts -> PSI      (used by ComputePressure_q16)
 *   ADC-to-DAC:      ADC counts -> DAC code (used by ComputeDacFromAdc)
 *
 * Per-tick cost: single int32 multiply-add per Compute call (~260 cycles at
 * 1 MHz on PIC18F56Q71, no FPU).
 */

#include "sm_context.h"
#include "sm_constants.h"
#include "../loop_driver/loop_driver.h"

/* --- Source of truth: sensor/AFE calibration and user preferences --- */

static CalibrationConstants_t cal;
static RangeSettings_t range;

/* --- Derived/cached transfer function parameters (Q16 format) ---
 * Written only by SmContext_RecomputeTransferFunctions(). */

static int32_t adc_to_current_slope_q16;
static int32_t adc_to_current_intercept_q16;

static int32_t adc_to_pressure_slope_q16;
static int32_t adc_to_pressure_intercept_q16;

static int32_t adc_to_dac_slope_q16;
static int32_t adc_to_dac_intercept_q16;

/* ======================================================================== */
/* Initialization                                                           */
/* ======================================================================== */

void SmContext_Init(void) {
    cal.afe_dac_trim       = DEFAULT_AFE_DAC_TRIM;
    cal.adc_at_sensor_low  = DEFAULT_ADC_AT_SENSOR_LOW;
    cal.adc_at_sensor_high = DEFAULT_ADC_AT_SENSOR_HIGH;

    range.low_pressure_q16  = (int32_t)DEFAULT_USER_RANGE_LOW_PSI * 65536L;
    range.high_pressure_q16 = (int32_t)DEFAULT_USER_RANGE_HIGH_PSI * 65536L;

    SmContext_RecomputeTransferFunctions();
}

/* ======================================================================== */
/* Transfer Function Derivation                                             */
/* ======================================================================== */

void SmContext_RecomputeTransferFunctions(void) {
    /* Read loop driver's calibrated DAC endpoints */
    uint16_t dac_4  = LoopDriver_GetDacAt4mA();
    uint16_t dac_20 = LoopDriver_GetDacAt20mA();
    int32_t dac_delta = (int32_t)dac_20 - (int32_t)dac_4;

    /* --- ADC-to-Pressure (from adc_at_sensor_low/high + sensor range) ---
     * Two-point fit across the full sensor physical span. */
    int32_t adc_sensor_delta = (int32_t)cal.adc_at_sensor_high
                             - (int32_t)cal.adc_at_sensor_low;
    if (adc_sensor_delta == 0) adc_sensor_delta = 1;

    int32_t pressure_range_q16 =
        (int32_t)(SENSOR_RANGE_HIGH_PSI - SENSOR_RANGE_LOW_PSI) * 65536L;

    adc_to_pressure_slope_q16 = pressure_range_q16 / adc_sensor_delta;
    adc_to_pressure_intercept_q16 = (int32_t)SENSOR_RANGE_LOW_PSI * 65536L
        - adc_to_pressure_slope_q16 * (int32_t)cal.adc_at_sensor_low;

    /* --- Determine ADC values at user's 4 mA and 20 mA pressure endpoints ---
     * Invert ADC-to-Pressure: adc = (pressure_q16 - intercept) / slope */
    int32_t adc_at_range_low;
    int32_t adc_at_range_high;

    if (adc_to_pressure_slope_q16 != 0) {
        adc_at_range_low = (range.low_pressure_q16
                            - adc_to_pressure_intercept_q16)
                           / adc_to_pressure_slope_q16;
        adc_at_range_high = (range.high_pressure_q16
                             - adc_to_pressure_intercept_q16)
                            / adc_to_pressure_slope_q16;
    } else {
        adc_at_range_low = 0;
        adc_at_range_high = (int32_t)ADC_MAX;
    }

    /* --- ADC-to-Current (from range boundary ADC values -> 4-20 mA) ---
     * Two-point fit: adc_at_range_low -> 4 mA, adc_at_range_high -> 20 mA */
    int32_t adc_range_delta = adc_at_range_high - adc_at_range_low;
    if (adc_range_delta == 0) adc_range_delta = 1;

    int32_t current_range_q16 = VALID_CURRENT_HIGH_Q16 - VALID_CURRENT_LOW_Q16;
    adc_to_current_slope_q16 = current_range_q16 / adc_range_delta;
    adc_to_current_intercept_q16 = VALID_CURRENT_LOW_Q16
        - adc_to_current_slope_q16 * adc_at_range_low;

    /* --- ADC-to-DAC (composite two-point fit, avoids Q16*Q16 overflow) ---
     * Maps adc_at_range_low -> dac_at_4mA, adc_at_range_high -> dac_at_20mA */
    int32_t dac_range_q16 = dac_delta << 16;
    adc_to_dac_slope_q16 = dac_range_q16 / adc_range_delta;
    adc_to_dac_intercept_q16 = ((int32_t)dac_4 << 16)
                               - adc_to_dac_slope_q16 * adc_at_range_low;
}

/* ======================================================================== */
/* Calibration Constant Setters                                             */
/* ======================================================================== */

void SmContext_SetAfeDacTrim(uint16_t value) {
    cal.afe_dac_trim = value;
}

void SmContext_SetAdcAtSensorLow(uint16_t value) {
    cal.adc_at_sensor_low = value;
}

void SmContext_SetAdcAtSensorHigh(uint16_t value) {
    cal.adc_at_sensor_high = value;
}

/* ======================================================================== */
/* Calibration Constant Getters                                             */
/* ======================================================================== */

uint16_t SmContext_GetAfeDacTrim(void) {
    return cal.afe_dac_trim;
}

uint16_t SmContext_GetAdcAtSensorLow(void) {
    return cal.adc_at_sensor_low;
}

uint16_t SmContext_GetAdcAtSensorHigh(void) {
    return cal.adc_at_sensor_high;
}

/* ======================================================================== */
/* Range Settings                                                           */
/* ======================================================================== */

void SmContext_SetRangeLowPressure_q16(int32_t pressure_q16) {
    range.low_pressure_q16 = pressure_q16;
}

void SmContext_SetRangeHighPressure_q16(int32_t pressure_q16) {
    range.high_pressure_q16 = pressure_q16;
}

int32_t SmContext_GetRangeLowPressure_q16(void) {
    return range.low_pressure_q16;
}

int32_t SmContext_GetRangeHighPressure_q16(void) {
    return range.high_pressure_q16;
}

/* ======================================================================== */
/* Computation Functions (Hot Path — Q16 integer arithmetic)                */
/* ======================================================================== */

int32_t SmContext_ComputeLoopCurrent_mA_q16(uint16_t adc_counts) {
    return adc_to_current_slope_q16 * (int32_t)adc_counts
         + adc_to_current_intercept_q16;
}

int32_t SmContext_ComputePressure_q16(uint16_t adc_counts) {
    return adc_to_pressure_slope_q16 * (int32_t)adc_counts
         + adc_to_pressure_intercept_q16;
}

uint16_t SmContext_ComputeDacFromAdc(uint16_t adc_counts) {
    int32_t result_q16 = adc_to_dac_slope_q16 * (int32_t)adc_counts
                       + adc_to_dac_intercept_q16;
    int16_t result = (int16_t)(result_q16 >> 16);

    if (result < 0) return 0;
    if (result > (int16_t)LOOP_DAC_MAX) return LOOP_DAC_MAX;
    return (uint16_t)result;
}

/* ======================================================================== */
/* Utility Functions (Cosmetic — not in calibration chain)                  */
/* ======================================================================== */

uint16_t SmContext_ComputeMCUDacVoltage_mV(uint16_t dac_code) {
    if (dac_code > AFE_DAC_MAX) dac_code = AFE_DAC_MAX;
    return (uint16_t)(((uint32_t)dac_code * VDD_MV) / AFE_DAC_MAX);
}

uint16_t SmContext_ComputeAdcVoltage_mV(uint16_t adc_code) {
    if (adc_code > ADC_MAX) adc_code = ADC_MAX;
    return (uint16_t)(((uint32_t)adc_code * VDD_MV) / ADC_MAX);
}
