/**
 * Input Manager — Implementation
 *
 * @file input_manager.c
 *
 * @brief Debounced button event generation using IOC + timer architecture.
 *
 * Debounce mechanism:
 *   1. A falling edge on any joystick pin triggers an IOC interrupt.
 *   2. The IOC callback sets a "pending" bit for that button and restarts the
 *      30ms debounce timer (TMR2). If the button is still bouncing, subsequent
 *      edges keep restarting the timer — the timeout never fires until the
 *      contact settles.
 *   3. When TMR2 reaches its period (~30ms after the LAST edge), the timer
 *      callback fires. It reads each pending button's GPIO state: if the pin
 *      is still low (button held), the pending bit is promoted to "confirmed."
 *      If the pin bounced back high (false trigger or release), it is discarded.
 *   4. The main loop calls InputManager_GetEvent(), which atomically snapshots
 *      and clears the confirmed flags, then returns a single event enum value.
 *
 * Volatile flags and ISR/main-loop interaction:
 *   - pending_flags:   Written by IOC ISRs, read/cleared by timer ISR.
 *   - confirmed_flags: Written by timer ISR, read/cleared by GetEvent().
 *   - GetEvent() disables interrupts briefly to prevent tearing during the
 *     snapshot-and-clear operation (see design doc Section 8.3).
 *
 * Hardware dependencies:
 *   - 5 joystick pins with IOC negative-edge enabled (MCC Pin Manager)
 *   - TMR2 configured for ~30ms period with interrupt (MCC Timer module)
 *   - Active-low buttons with weak pull-ups (WPU set in MCC Pin Manager)
 */

#include "input_manager.h"
#include "../config.mcc/mcc_generated_files/system/pins.h"
#include "../config.mcc/mcc_generated_files/timer/tmr2.h"
#include "../config.mcc/mcc_generated_files/system/interrupt.h"

/* Bitmask positions for each button in the flag bytes.
 * Literal values used instead of bit-shift expressions because the
 * PIC18F56Q71 has no barrel shifter. */
#define FLAG_UP     0x01u
#define FLAG_DOWN   0x02u
#define FLAG_LEFT   0x04u
#define FLAG_RIGHT  0x08u
#define FLAG_PUSH   0x10u

/* pending_flags: set by IOC ISRs, cleared by timer ISR after promotion.
 * confirmed_flags: set by timer ISR, cleared by InputManager_GetEvent(). */
static volatile uint8_t pending_flags = 0;
static volatile uint8_t confirmed_flags = 0;

/*
 * IOC callbacks — one per button.
 * Each sets its pending bit and restarts the debounce timer. Restarting on
 * every edge means the 30ms window only begins AFTER bouncing has stopped.
 */

static void on_up_press(void) {
    pending_flags |= FLAG_UP;
    TMR2_CounterSet(0);
    TMR2_Start();
}

static void on_down_press(void) {
    pending_flags |= FLAG_DOWN;
    TMR2_CounterSet(0);
    TMR2_Start();
}

static void on_left_press(void) {
    pending_flags |= FLAG_LEFT;
    TMR2_CounterSet(0);
    TMR2_Start();
}

static void on_right_press(void) {
    pending_flags |= FLAG_RIGHT;
    TMR2_CounterSet(0);
    TMR2_Start();
}

static void on_push_press(void) {
    pending_flags |= FLAG_PUSH;
    TMR2_CounterSet(0);
    TMR2_Start();
}

/**
 * @brief TMR2 period match callback — fires ~30ms after the last button edge.
 *
 * For each pending button, reads the GPIO pin to verify the button is still
 * physically held down (active-low: GetValue() == 0 means pressed). Only
 * buttons that pass this check are promoted to confirmed. This rejects
 * spurious edges from ESD, crosstalk, or incomplete presses.
 */
static void on_debounce_timeout(void) {
    uint8_t promoted = 0;

    if ((pending_flags & FLAG_UP) && !JS_UP_GetValue())
        promoted |= FLAG_UP;
    if ((pending_flags & FLAG_DOWN) && !JS_DOWN_GetValue())
        promoted |= FLAG_DOWN;
    if ((pending_flags & FLAG_LEFT) && !JS_LEFT_GetValue())
        promoted |= FLAG_LEFT;
    if ((pending_flags & FLAG_RIGHT) && !JS_RIGHT_GetValue())
        promoted |= FLAG_RIGHT;
    if ((pending_flags & FLAG_PUSH) && !JS_PUSH_GetValue())
        promoted |= FLAG_PUSH;

    confirmed_flags |= promoted;
    pending_flags = 0;
    TMR2_Stop();
}

void InputManager_Init(void) {
    // TMR2 starts running after SYSTEM_Initialize(); stop it until needed
    TMR2_Stop();

    // Register our callbacks as the IOC handlers for each joystick pin
    JS_UP_SetInterruptHandler(on_up_press);
    JS_DOWN_SetInterruptHandler(on_down_press);
    JS_LEFT_SetInterruptHandler(on_left_press);
    JS_RIGHT_SetInterruptHandler(on_right_press);
    JS_PUSH_SetInterruptHandler(on_push_press);

    // Register the debounce timeout as the TMR2 period-match callback
    TMR2_PeriodMatchCallbackRegister(on_debounce_timeout);
}

InputEvent_t InputManager_GetEvent(void) {
    // Atomic snapshot: disable interrupts to prevent the timer ISR from
    // modifying confirmed_flags between the read and the clear
    INTERRUPT_GlobalInterruptDisable();
    uint8_t snapshot = confirmed_flags;
    confirmed_flags = 0;
    INTERRUPT_GlobalInterruptEnable();

    if (snapshot == 0)
        return EVENT_NONE;

    // Count how many buttons were confirmed in this debounce window
    uint8_t count = 0;
    if (snapshot & FLAG_UP)    count++;
    if (snapshot & FLAG_DOWN)  count++;
    if (snapshot & FLAG_LEFT)  count++;
    if (snapshot & FLAG_RIGHT) count++;
    if (snapshot & FLAG_PUSH)  count++;

    // Multiple simultaneous buttons — the design doc specifies this as a
    // distinct event so states can explicitly choose to ignore it
    if (count > 1)
        return EVENT_CONFLICT;

    // Exactly one button — return the corresponding event
    if (snapshot & FLAG_UP)    return EVENT_UP;
    if (snapshot & FLAG_DOWN)  return EVENT_DOWN;
    if (snapshot & FLAG_LEFT)  return EVENT_LEFT;
    if (snapshot & FLAG_RIGHT) return EVENT_RIGHT;
    return EVENT_PUSH;
}
