/**
 * STATE_SYSTEM_CALIBRATE — Unified system calibration wizard
 *
 * @file state_system_calibrate.h
 *
 * @brief Declares the entry/do/exit functions for the unified calibration
 *        state that walks the user through all calibration steps in
 *        dependency order.
 */

#ifndef STATE_SYSTEM_CALIBRATE_H
#define STATE_SYSTEM_CALIBRATE_H

void StateSystemCalibrate_Entry(void);
void StateSystemCalibrate_Do(void);
void StateSystemCalibrate_Exit(void);

#endif /* STATE_SYSTEM_CALIBRATE_H */
