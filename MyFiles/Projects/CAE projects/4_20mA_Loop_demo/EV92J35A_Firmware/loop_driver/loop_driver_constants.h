/**
 * Loop Driver Constants — Compile-Time Calibration Defaults
 *
 * @file loop_driver_constants.h
 *
 * @brief Default values for the loop driver's calibration constants. Loaded
 *        into RAM by LoopDriver_Init() at startup.
 *
 * Extended loop range:
 *   The EV34C35A current loop driver operates over approximately 3.6 mA to
 *   22 mA. With the digipot properly trimmed and DAC=0, the loop produces
 *   ~3.6 mA (the low alarm floor). The 4-20 mA valid measurement band falls
 *   at specific DAC codes within this range — those codes are calibration
 *   constants measured by the DAC calibration procedure.
 *
 * NOTE: DEFAULT_DAC_AT_4MA and DEFAULT_DAC_AT_20MA are approximations based
 * on a linear model between (3.6 mA, DAC=0) and (22 mA, DAC=4095). The
 * actual theoretical values from the EV34C35A circuit formula need
 * verification. The software architecture does not depend on correct defaults
 * — the DAC calibration procedure measures the actual values.
 *
 * No .c file — this header contains only preprocessor constants (no RAM cost).
 */

#ifndef LOOP_DRIVER_CONSTANTS_H
#define LOOP_DRIVER_CONSTANTS_H

/* Digipot wiper position that produces ~3.6 mA at DAC=0.
 * Mid-scale is a safe starting point before trim calibration. */
#define LOOP_DRIVER_DEFAULT_DIGIPOT_TRIM    (128u)

/* DAC code that produces exactly 4.000 mA (low end of valid measurement band).
 * Linear approximation: (4.0 - 3.6) / (22.0 - 3.6) * 4095 ≈ 89 */
#define LOOP_DRIVER_DEFAULT_DAC_AT_4MA      (89u)

/* DAC code that produces exactly 20.000 mA (high end of valid measurement band).
 * Linear approximation: (20.0 - 3.6) / (22.0 - 3.6) * 4095 ≈ 3650 */
#define LOOP_DRIVER_DEFAULT_DAC_AT_20MA     (3650u)

#endif /* LOOP_DRIVER_CONSTANTS_H */
