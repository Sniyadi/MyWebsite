/**
 * STATE_INIT — One-shot initialization, then transition to MONITOR
 *
 * @file state_init.h
 */

#ifndef STATE_INIT_H
#define STATE_INIT_H

void StateInit_Entry(void);
void StateInit_Do(void);
void StateInit_Exit(void);

#endif // STATE_INIT_H
