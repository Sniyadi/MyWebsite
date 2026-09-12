/**
 * Loop Driver Board-Level API
 *
 * @file loop_driver.h
 *
 * @brief Unified interface for the EV34C35A 4-20 mA current loop driver board.
 *        Composes the MCP48CMD21 (external DAC) and MCP4152 (digital
 *        potentiometer) device drivers into a single, application-friendly API.
 *
 * This module owns all loop driver hardware and the Current-to-DAC transfer
 * function that maps milliamp values to 12-bit DAC codes.
 *
 * Extended loop range:
 *   The loop operates over approximately 3.6 mA to 22 mA:
 *     - DAC=0 with digipot trimmed -> ~3.6 mA (low alarm floor)
 *     - DAC=dac_at_4mA            -> 4.000 mA (valid measurement low)
 *     - DAC=dac_at_20mA           -> 20.000 mA (valid measurement high)
 *     - DAC=4095                  -> ~22 mA (high alarm ceiling)
 *   The DAC codes for 4 mA and 20 mA are calibration constants, not the
 *   DAC endpoints (0 and 4095).
 *
 * Calibration constants owned by this module:
 *   - digipot_trim: wiper position that sets the ~3.6 mA floor at DAC=0
 *   - dac_at_4mA:   DAC code producing exactly 4.000 mA
 *   - dac_at_20mA:  DAC code producing exactly 20.000 mA
 *
 * Current-to-DAC transfer function (internal):
 *   Linear mapping from milliamps to DAC code, derived from dac_at_4mA and
 *   dac_at_20mA. Fully encapsulated — external code sets milliamp values
 *   via LoopDriver_SetCurrent_mA_q16() or reads back via
 *   LoopDriver_ComputeCurrent_mA_q16(). No direct access to the raw
 *   slope/intercept parameters.
 *
 * Fixed-point representation:
 *   Current values use Q16 format (int32_t scaled by 65536).
 *
 * Dummy/real switching:
 *   Controlled by LOOP_DRIVER_USE_DUMMY in loop_driver_bsp.h.
 */

#ifndef LOOP_DRIVER_H
#define LOOP_DRIVER_H

#include <stdint.h>

/* 12-bit external DAC full-scale value, used for output clamping */
#define LOOP_DAC_MAX    (4095u)

/**
 * @brief Initialize both devices on the loop driver board.
 *
 * Initializes the MCP48CMD21 (DAC output = 0, producing ~3.6 mA floor) and
 * MCP4152 (wiper = default trim). Loads default calibration constants and
 * computes the Current-to-DAC transfer function.
 * Call once from STATE_INIT entry action, after SYSTEM_Initialize().
 */
void LoopDriver_Init(void);

/* === Calibration Constants === */

/**
 * @brief Set the digipot trim value (and write to hardware).
 *
 * The digipot sets the loop current floor when DAC=0. Target: ~3.6 mA.
 * Note: changing this invalidates dac_at_4mA and dac_at_20mA — the DAC
 * calibration procedure must be re-performed afterward.
 *
 * @param value Wiper position (0-255)
 */
void LoopDriver_SetDigipotTrim(uint8_t value);

/**
 * @brief Set the DAC code that produces exactly 4.000 mA.
 * Call LoopDriver_RecomputeTransfer() after modifying.
 * @param value 12-bit DAC code
 */
void LoopDriver_SetDacAt4mA(uint16_t value);

/**
 * @brief Set the DAC code that produces exactly 20.000 mA.
 * Call LoopDriver_RecomputeTransfer() after modifying.
 * @param value 12-bit DAC code
 */
void LoopDriver_SetDacAt20mA(uint16_t value);

/** @brief Get the stored digipot trim value. */
uint8_t LoopDriver_GetDigipotTrim(void);

/** @brief Get the stored DAC code for 4 mA. */
uint16_t LoopDriver_GetDacAt4mA(void);

/** @brief Get the stored DAC code for 20 mA. */
uint16_t LoopDriver_GetDacAt20mA(void);

/**
 * @brief Recompute the Current-to-DAC transfer function from stored constants.
 *
 * Derives slope and intercept from dac_at_4mA and dac_at_20mA, and
 * pre-computes the inverse for division-free readback.
 * Must be called after modifying dac_at_4mA or dac_at_20mA.
 */
void LoopDriver_RecomputeTransfer(void);

/* === External DAC (MCP48CMD21) — sets loop current === */

/**
 * @brief Write a 12-bit code directly to the external DAC.
 * @param counts 12-bit DAC code (0-4095). Values > 4095 are clamped.
 */
void LoopDriver_SetDac(uint16_t counts);

/**
 * @brief Read back the current DAC output code.
 * @return 12-bit DAC code (0-4095)
 */
uint16_t LoopDriver_GetDac(void);

/**
 * @brief Set the loop current by milliamp value (Q16).
 *
 * Converts the requested current to a 12-bit DAC code using the internal
 * Current-to-DAC transfer function, then writes it to the external DAC.
 * Output is clamped to [0, 4095].
 *
 * @param current_mA_q16 Desired loop current in milliamps, Q16 format
 */
void LoopDriver_SetCurrent_mA_q16(int32_t current_mA_q16);

/**
 * @brief Compute the loop current corresponding to a given DAC code (Q16).
 *
 * Inverse of the Current-to-DAC transfer function. Uses a pre-computed
 * inverse slope to avoid runtime division.
 *
 * @param dac_counts 12-bit DAC code (0-4095)
 * @return Corresponding loop current in milliamps, Q16 format
 */
int32_t LoopDriver_ComputeCurrent_mA_q16(uint16_t dac_counts);

/* === Digital Potentiometer (MCP4152) — direct hardware access === */

/**
 * @brief Write a wiper position to the digital potentiometer.
 * @param position Wiper position (0-255)
 */
void LoopDriver_SetDigipot(uint8_t position);

/**
 * @brief Read back the current digipot wiper position.
 * @return Wiper position (0-255)
 */
uint8_t LoopDriver_GetDigipot(void);

/** @brief Increment the digipot wiper by one step. Clamps at 255. */
void LoopDriver_IncrementDigipot(void);

/** @brief Decrement the digipot wiper by one step. Clamps at 0. */
void LoopDriver_DecrementDigipot(void);

#endif /* LOOP_DRIVER_H */
