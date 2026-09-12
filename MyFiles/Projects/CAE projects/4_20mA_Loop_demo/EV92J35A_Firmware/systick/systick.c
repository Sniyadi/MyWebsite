/**
 * Systick — Implementation
 *
 * @file systick.c
 *
 * @brief Implements the system tick counter using TMR0's overflow callback.
 *
 * TMR0 is configured by MCC at 10 Hz (100 ms period). On each overflow,
 * the ISR callback increments a 32-bit tick counter and sets a pending flag.
 * The main loop polls the pending flag to decide when to run the state machine.
 *
 * Atomic access:
 *   The PIC18 is an 8-bit core — reading/writing a 32-bit variable is not
 *   atomic. We briefly disable interrupts during GetTicks() to prevent a
 *   torn read if the ISR fires mid-copy.
 */

#include "systick.h"
#include <xc.h>
#include "../config.mcc/mcc_generated_files/timer/tmr0.h"
#include "../config.mcc/mcc_generated_files/system/interrupt.h"

/* Tick counter — incremented by TMR0 ISR callback at 10 Hz.
 * Volatile because it's modified in interrupt context. */
static volatile uint32_t tick_count = 0;

/* Pending flag — set by ISR, cleared by main loop after SM_Run(). */
static volatile bool tick_pending = false;

/**
 * TMR0 overflow callback — called from TMR0_ISR() at 10 Hz.
 * Runs in interrupt context. Must be fast (two writes, no function calls).
 */
static void on_tick(void) {
    tick_count++;
    tick_pending = true;
}

void Systick_Init(void) {
    /* Register our callback with the MCC-generated TMR0 driver.
     * TMR0 is already initialized and running (via SYSTEM_Initialize). */
    TMR0_OverflowCallbackRegister(on_tick);
}

uint32_t Systick_GetTicks(void) {
    /* Atomic 32-bit read: disable interrupts to prevent torn value if
     * the ISR fires between byte reads on this 8-bit core. */
    INTERRUPT_GlobalInterruptDisable();
    uint32_t snapshot = tick_count;
    INTERRUPT_GlobalInterruptEnable();
    return snapshot;
}

bool Systick_Elapsed(uint32_t start, uint32_t duration) {
    /* Unsigned subtraction handles wrap-around correctly:
     * if tick_count wrapped past start, (current - start) is still the
     * true elapsed count due to unsigned arithmetic. */
    return (Systick_GetTicks() - start) >= duration;
}

bool Systick_IsPending(void) {
    return tick_pending;
}

void Systick_ClearPending(void) {
    tick_pending = false;
}
