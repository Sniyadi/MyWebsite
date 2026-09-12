/**
 * Systick — System-Wide Tick Counter and Idle Sleep Framework
 *
 * @file systick.h
 *
 * @brief Provides a monotonic tick counter driven by TMR0 at 10 Hz (100 ms
 *        period). The main loop uses this to gate SM_Run() execution and
 *        enter Idle sleep between ticks, reducing CPU utilization to < 1%
 *        on idle ticks.
 *
 * Tick rate:
 *   10 Hz (100 ms period). TMR0 is configured by MCC Melody with HFINTOSC
 *   clock source, 1:2 prescaler (500 kHz), 16-bit mode, counting 50000 to
 *   overflow. The overflow interrupt fires the registered callback.
 *
 * Usage in main.c:
 *   Systick_Init();
 *   CPUDOZEbits.IDLEN = 1;  // SLEEP enters Idle mode (peripherals run)
 *   while (1) {
 *       if (Systick_IsPending()) {
 *           Systick_ClearPending();
 *           SM_Run();
 *       }
 *       SLEEP();
 *   }
 *
 * Usage in states (rate-limiting example):
 *   static uint32_t last_adc_tick = 0;
 *   if (Systick_Elapsed(last_adc_tick, 5)) {  // every 500 ms
 *       last_adc_tick = Systick_GetTicks();
 *       adc_counts = ADC_ChannelSelectAndConvert(ADC_IN);
 *   }
 *
 * Tick counter wrap:
 *   The uint32_t counter wraps at 2^32. At 10 Hz, this is ~13.6 years.
 *   Systick_Elapsed() uses unsigned subtraction and handles wrap correctly.
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize the systick module.
 *
 * Registers the TMR0 overflow callback to increment the tick counter and
 * set the pending flag. TMR0 must already be initialized and running
 * (handled by SYSTEM_Initialize via MCC).
 *
 * Call once from main() after SYSTEM_Initialize().
 */
void Systick_Init(void);

/**
 * @brief Get the current monotonic tick count.
 *
 * Returns the number of ticks elapsed since Systick_Init(). Reads are
 * atomic (interrupts briefly disabled during the 32-bit copy on PIC18).
 *
 * @return Monotonic tick count (wraps at 2^32)
 */
uint32_t Systick_GetTicks(void);

/**
 * @brief Check if a duration has elapsed since a starting tick.
 *
 * Uses unsigned subtraction to handle counter wrap-around correctly.
 * Example: Systick_Elapsed(start, 10) returns true after 10 ticks (1 sec).
 *
 * @param start     Tick value captured at the start of the interval
 * @param duration  Number of ticks that must have passed
 * @return true if (current_ticks - start) >= duration
 */
bool Systick_Elapsed(uint32_t start, uint32_t duration);

/**
 * @brief Check if a tick has fired since the last ClearPending call.
 *
 * Used by the main loop to determine whether to run SM_Run() this iteration.
 *
 * @return true if one or more ticks have fired since last ClearPending
 */
bool Systick_IsPending(void);

/**
 * @brief Clear the pending tick flag.
 *
 * Called by the main loop after dispatching SM_Run(). The flag will be set
 * again by the next TMR0 overflow interrupt.
 */
void Systick_ClearPending(void);

#endif /* SYSTICK_H */
