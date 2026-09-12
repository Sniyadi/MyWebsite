/**
 * STATE_DEMO — Triangle wave sweep of 4-20 mA loop current
 *
 * @file state_demo.h
 *
 * @brief Sweeps the loop driver DAC through its full 12-bit range in a
 *        continuous triangle wave pattern (4 mA → 20 mA → 4 mA), displaying
 *        the current value on screen. LEFT returns to menu.
 */

#ifndef STATE_DEMO_H
#define STATE_DEMO_H

void StateDemo_Entry(void);
void StateDemo_Do(void);
void StateDemo_Exit(void);

#endif // STATE_DEMO_H
