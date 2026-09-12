/**
 * State Machine Constants — Compile-Time Calibration Defaults
 *
 * @file sm_constants.h
 *
 * @brief Defines default values for all calibration constants and user range
 *        settings used by the state machine context module. These are loaded
 *        into RAM by SmContext_Init() at startup.
 *
 * Software architecture (constants-centric calibration):
 *   Raw calibration constants are the single source of truth. All transfer
 *   function parameters (ADC-to-Current, ADC-to-Pressure, ADC-to-DAC) are
 *   derived from these constants by SmContext_RecomputeTransferFunctions().
 *
 *   Calibration constants characterize the hardware:
 *     - Level 1 (independent): digipot trim, AFE DAC trim
 *     - Level 2 (requires Level 1): DAC codes at 4 mA and 20 mA
 *     - Level 3 (requires Level 1): ADC readings at sensor endpoints
 *
 *   User range settings characterize intent:
 *     - Which pressure values map to 4 mA and 20 mA
 *     - Independent of calibration — can be changed any time
 *
 * Extended loop range:
 *   The current loop operates over approximately 3.6 mA to 22 mA.
 *   DAC=0 with digipot properly trimmed produces ~3.6 mA (low alarm floor).
 *   The 4-20 mA band is the valid measurement range within this span.
 *   DAC codes for 4 mA and 20 mA are calibration constants, not fixed at
 *   the DAC endpoints (0 and 4095).
 *
 * NVM strategy:
 *   This is a demonstration unit. All calibration is compile-time only.
 *   Calibration routines modify the in-RAM copies during a session but
 *   never persist to NVM. On the next power cycle, these defaults are
 *   restored. In a production build, these would serve as factory defaults,
 *   overridden by NVM-stored values.
 *
 * No .c file — this header contains only preprocessor constants (no RAM cost).
 */

#ifndef SM_CONSTANTS_H
#define SM_CONSTANTS_H

/*
 * Valid measurement band (Q16 format).
 * The 4-20 mA range within which ADC readings represent valid process data.
 * Used by SmContext_RecomputeTransferFunctions() to derive the ADC-to-Current
 * transfer function.
 */
#define VALID_CURRENT_LOW_Q16       (262144L)       /* 4.0 mA * 65536 */
#define VALID_CURRENT_HIGH_Q16      (1310720L)      /* 20.0 mA * 65536 */

/*
 * NAMUR NE43 alarm currents (Q16 format).
 * When the process variable is outside the user-defined measurement range,
 * the transmitter drives these alarm currents to signal the condition:
 *   Under-range (below 4 mA): 3.6 mA (downscale burnout)
 *   Over-range (above 20 mA): 21.0 mA (upscale burnout)
 */
#define ALARM_CURRENT_LOW_Q16       (235929L)       /* 3.6 mA * 65536 */
#define ALARM_CURRENT_HIGH_Q16      (1376256L)      /* 21.0 mA * 65536 */

/*
 * Alarm hysteresis thresholds (Q16 format).
 * Entry thresholds: alarm engages only when current crosses OUTSIDE these.
 * Exit thresholds: alarm clears only when current crosses INSIDE these.
 * The dead band prevents display chattering from ADC noise near the boundary.
 *   Low:  enters alarm at < 3.8 mA, clears at > 4.0 mA (0.2 mA band)
 *   High: enters alarm at > 20.5 mA, clears at < 20.0 mA (0.5 mA band)
 */
#define ALARM_ENTER_LOW_Q16     (249036L)       /* 3.8 mA * 65536 */
#define ALARM_ENTER_HIGH_Q16    (1343488L)      /* 20.5 mA * 65536 */
#define ALARM_EXIT_LOW_Q16      (262144L)       /* 4.0 mA * 65536 */
#define ALARM_EXIT_HIGH_Q16     (1310720L)      /* 20.0 mA * 65536 */

/*
 * Sensor physical range (integer PSI).
 * Describes the full measurement span of the attached pressure transducer.
 * Used by SmContext_RecomputeTransferFunctions() to derive the ADC-to-Pressure
 * transfer function. Multiplied by 65536 at recompute time to produce Q16.
 */
#define SENSOR_RANGE_LOW_PSI        (0)
#define SENSOR_RANGE_HIGH_PSI       (50)

/*
 * Default calibration constants (sensor/AFE — owned by sm_context).
 * Loop driver defaults (digipot, DAC endpoints) are in loop_driver_constants.h.
 */
#define DEFAULT_AFE_DAC_TRIM        (84u)       /* ~270 mV output (matches MCC DAC1 init) */
#define DEFAULT_ADC_AT_SENSOR_LOW   (0u)        /* Placeholder: ADC at 0 PSI */
#define DEFAULT_ADC_AT_SENSOR_HIGH  (4095u)     /* Placeholder: ADC at 50 PSI */

/*
 * Default user range settings (integer PSI).
 * Defines which portion of the sensor's pressure range maps to the 4-20 mA
 * measurement band. Converted to Q16 at init time.
 * Full sensor span by default: 0 PSI = 4 mA, 50 PSI = 20 mA.
 */
#define DEFAULT_USER_RANGE_LOW_PSI      (0)     /* Pressure at 4 mA */
#define DEFAULT_USER_RANGE_HIGH_PSI     (50)    /* Pressure at 20 mA */

/*
 * MCU voltage reference and peripheral resolution constants.
 * Used by SmContext voltage computation utility functions (cosmetic display).
 * Not part of the calibration chain — ratiometric design makes absolute
 * voltage irrelevant to measurement accuracy.
 */
#define VDD_MV              (3300u)     /* MCU supply voltage in millivolts */
#define AFE_DAC_MAX         (1023u)     /* 10-bit internal DAC full-scale */
#define ADC_MAX             (4095u)     /* 12-bit ADC full-scale */

#endif /* SM_CONSTANTS_H */
