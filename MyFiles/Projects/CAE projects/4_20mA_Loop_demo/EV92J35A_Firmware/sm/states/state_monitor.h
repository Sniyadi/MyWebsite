/**
 * STATE_MONITOR — Default operating mode (read sensor, drive loop, display)
 *
 * @file state_monitor.h
 *
 * @brief Primary operating state of the loop driver firmware. Reads the
 *        pressure sensor via ADC, computes PSI and loop current, drives the
 *        external DAC to set the 4-20 mA output, and updates the display
 *        with live readings every tick. LEFT transitions to STATE_MENU.
 */

#ifndef STATE_MONITOR_H
#define STATE_MONITOR_H

void StateMonitor_Entry(void);
void StateMonitor_Do(void);
void StateMonitor_Exit(void);

#endif // STATE_MONITOR_H
