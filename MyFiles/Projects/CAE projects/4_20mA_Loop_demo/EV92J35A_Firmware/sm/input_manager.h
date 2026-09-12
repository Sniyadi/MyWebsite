/**
 * Input Manager — Debounced Button Event Interface
 *
 * @file input_manager.h
 *
 * @brief Provides a single-event-per-tick interface between the 5-button
 *        joystick hardware and the state machine. The state machine never
 *        reads GPIO directly; all button input flows through this module.
 *
 * Architecture (see loop_driver_firmware_context.md, Section 8):
 *   - IOC ISRs on each button pin set volatile "pending" flags
 *   - A hardware timer (TMR2, ~30ms) debounces by waiting for bouncing to stop
 *   - When the timer fires, pending flags are promoted to "confirmed" if the
 *     pin is still held low (active-low buttons with weak pull-ups)
 *   - InputManager_GetEvent() atomically consumes confirmed flags once per
 *     main loop tick and returns a single InputEvent_t value
 *
 * Usage:
 *   InputManager_Init();           // after SYSTEM_Initialize(), before main loop
 *   while (1) {
 *       InputEvent_t evt = InputManager_GetEvent();
 *       // pass evt to current state's do-action
 *   }
 */

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdint.h>

/**
 * @brief Events returned by InputManager_GetEvent().
 *
 * EVENT_NONE means no button was pressed since the last call.
 * EVENT_CONFLICT means two or more buttons were confirmed simultaneously;
 * most states should treat this as "ignored" per the design doc.
 */
typedef enum {
    EVENT_NONE,
    EVENT_UP,
    EVENT_DOWN,
    EVENT_LEFT,
    EVENT_RIGHT,
    EVENT_PUSH,
    EVENT_CONFLICT
} InputEvent_t;

/**
 * @brief Initialize the input manager.
 *
 * Registers IOC interrupt callbacks for all 5 joystick pins and configures
 * TMR2 as the debounce timer. Must be called after SYSTEM_Initialize() and
 * after global interrupts are enabled.
 */
void InputManager_Init(void);

/**
 * @brief Consume and return the next button event.
 *
 * Atomically snapshots and clears the confirmed-event flags (interrupts are
 * briefly disabled to prevent a race with the timer ISR). Returns exactly one
 * event per call — if multiple buttons were confirmed in the same debounce
 * window, returns EVENT_CONFLICT.
 *
 * Call once per main loop tick. The returned event is consumed; calling again
 * without a new button press returns EVENT_NONE.
 */
InputEvent_t InputManager_GetEvent(void);

#endif // INPUT_MANAGER_H
