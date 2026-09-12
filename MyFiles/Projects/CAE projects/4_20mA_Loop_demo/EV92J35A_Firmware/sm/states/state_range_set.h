/**
 * STATE_RANGE_SET — Capture ADC readings at 4/20 mA to calibrate transfer functions
 *
 * @file state_range_set.h
 *
 * @brief Guides the user through a 3-step calibration: capture ADC at 4 mA,
 *        capture ADC at 20 mA, then confirm. On confirm, computes new TF1
 *        (ADC→mA) and TF4 (ADC→DAC) from the two captured endpoints. On cancel
 *        at any step, no parameters are modified.
 */

#ifndef STATE_RANGE_SET_H
#define STATE_RANGE_SET_H

void StateRangeSet_Entry(void);
void StateRangeSet_Do(void);
void StateRangeSet_Exit(void);

#endif // STATE_RANGE_SET_H
