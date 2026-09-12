/**
 * State Machine Context — Shared Calibration Data and Computation API
 *
 * @file sm_context.h
 *
 * @brief Owns all calibration constants, user range settings, and derived
 *        transfer function parameters. Provides getter/setter access to
 *        calibration data and computation functions that convert ADC readings
 *        to engineering values.
 *
 * Software architecture (constants-centric calibration):
 *   Raw calibration constants (CalibrationConstants_t) and user range
 *   settings (RangeSettings_t) are the source of truth. All transfer
 *   function parameters are derived from them by a single function:
 *   SmContext_RecomputeTransferFunctions().
 *
 *   Callers modify individual constants via setters, then call Recompute
 *   to update all derived parameters. The Compute functions (hot path)
 *   use only the cached derived parameters — no struct access at runtime.
 *
 * Four derived transfer functions:
 *   ADC-to-Current:  ADC counts -> loop current (mA)       [Q16]
 *   ADC-to-Pressure: ADC counts -> displayed pressure (PSI) [Q16]
 *   Current-to-DAC:  loop current (mA) -> DAC code          [Q16, owned by loop_driver]
 *   ADC-to-DAC:      ADC counts -> DAC code (composite)     [Q16, hot path]
 *
 * Variable scoping:
 *   All parameters are static inside sm_context.c. External access is
 *   exclusively through the getter/setter/compute API declared here.
 */

#ifndef SM_CONTEXT_H
#define SM_CONTEXT_H

#include <stdint.h>

/**
 * Calibration Constants — Characterize the sensor/AFE hardware.
 * Populated by calibration routines. Source of truth for sensor-side TFs.
 *
 * Loop driver calibration constants (digipot_trim, dac_at_4mA, dac_at_20mA)
 * are owned by the loop_driver module — see loop_driver.h.
 */
typedef struct {
    uint16_t afe_dac_trim;       /* MCU DAC1 code -> AFE offset nulled */
    uint16_t adc_at_sensor_low;  /* ADC reading at sensor physical minimum */
    uint16_t adc_at_sensor_high; /* ADC reading at sensor physical maximum */
} CalibrationConstants_t;

/**
 * Range Settings — Characterize user intent.
 * Defines which portion of the sensor's pressure range maps to the 4-20 mA
 * measurement band. Not calibration — this is a user preference.
 */
typedef struct {
    int32_t low_pressure_q16;    /* pressure (Q16 PSI) at 4 mA */
    int32_t high_pressure_q16;   /* pressure (Q16 PSI) at 20 mA */
} RangeSettings_t;

/**
 * @brief Seed all calibration constants and range settings from compile-time
 *        defaults, then derive all transfer functions.
 *
 * Called by STATE_INIT entry action. After this call, all getters return
 * default values and all Compute functions produce valid output.
 */
void SmContext_Init(void);

/* --- Calibration constant setters (sensor/AFE, individual) ---
 * Write one constant. Call SmContext_RecomputeTransferFunctions() after
 * modifying any constant that affects TF derivation.
 * Loop driver constants (digipot, dac endpoints) are set via loop_driver.h. */
void SmContext_SetAfeDacTrim(uint16_t value);
void SmContext_SetAdcAtSensorLow(uint16_t value);
void SmContext_SetAdcAtSensorHigh(uint16_t value);

/* --- Calibration constant getters (sensor/AFE, individual) --- */
uint16_t SmContext_GetAfeDacTrim(void);
uint16_t SmContext_GetAdcAtSensorLow(void);
uint16_t SmContext_GetAdcAtSensorHigh(void);

/* --- Range settings (individual) ---
 * Call SmContext_RecomputeTransferFunctions() after modifying. */
void SmContext_SetRangeLowPressure_q16(int32_t pressure_q16);
void SmContext_SetRangeHighPressure_q16(int32_t pressure_q16);
int32_t SmContext_GetRangeLowPressure_q16(void);
int32_t SmContext_GetRangeHighPressure_q16(void);

/**
 * @brief Derive all transfer function parameters from the current calibration
 *        constants and range settings.
 *
 * Must be called after modifying any calibration constant or range setting
 * that affects TF derivation (dac_at_4mA, dac_at_20mA, adc_at_sensor_low,
 * adc_at_sensor_high, or either range pressure endpoint).
 *
 * Computes and caches:
 *   - Current-to-DAC (pushed to loop_driver module)
 *   - ADC-to-Pressure
 *   - ADC-to-Current
 *   - ADC-to-DAC (composite)
 */
void SmContext_RecomputeTransferFunctions(void);

/**
 * @brief Compute the requested loop current from an ADC reading (Q16 result).
 * @param adc_counts 12-bit ADC result (0-4095)
 * @return Loop current in milliamps, Q16 format
 */
int32_t SmContext_ComputeLoopCurrent_mA_q16(uint16_t adc_counts);

/**
 * @brief Compute displayed pressure from an ADC reading (Q16 result).
 * @param adc_counts 12-bit ADC result (0-4095)
 * @return Pressure in PSI, Q16 format
 */
int32_t SmContext_ComputePressure_q16(uint16_t adc_counts);

/**
 * @brief Convert an ADC reading directly to an external DAC output value.
 *
 * This is the primary per-tick computation in STATE_MONITOR. Uses the
 * ADC-to-DAC composite transfer function for a single integer multiply-add.
 *
 * @param adc_counts 12-bit ADC result (0-4095)
 * @return 12-bit DAC value clamped to [0, 4095]
 */
uint16_t SmContext_ComputeDacFromAdc(uint16_t adc_counts);

/**
 * @brief Compute the MCU's internal DAC output voltage in millivolts.
 * Cosmetic utility — not part of calibration chain.
 * @param dac_code 10-bit DAC code (0-1023)
 * @return Voltage in millivolts (0-3300)
 */
uint16_t SmContext_ComputeMCUDacVoltage_mV(uint16_t dac_code);

/**
 * @brief Compute the ADC input voltage in millivolts.
 * Cosmetic utility — not part of calibration chain.
 * @param adc_code 12-bit ADC result (0-4095)
 * @return Voltage in millivolts (0-3300)
 */
uint16_t SmContext_ComputeAdcVoltage_mV(uint16_t adc_code);

#endif /* SM_CONTEXT_H */
