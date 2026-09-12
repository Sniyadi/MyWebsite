/**
 * State Machine Framework — Public API
 *
 * @file sm.h
 *
 * @brief Defines the state enum, initialization, per-tick execution, and the
 *        single transition function that all state changes flow through.
 *
 * Architecture (see loop_driver_firmware_context.md, Section 3):
 *   This module is the central skeleton of the firmware. It owns:
 *     - The state enum (SmState_t) giving each mode a named identity
 *     - SM_Init() — called once at startup to enter STATE_INIT
 *     - SM_Run() — called once per main loop tick, dispatches to current do_action
 *     - SM_Transition() — the single enforcement point for all state changes
 *
 * Design pattern (Section 3.2):
 *   Each state is represented by a StateDescriptor_t struct containing three
 *   function pointers: entry, do_action, and exit. A const array of these
 *   structs is indexed by SmState_t. This is data-driven — adding a new state
 *   requires only a new enum member and a new struct entry; SM_Run() and
 *   SM_Transition() never need modification.
 *
 * Encapsulation (Section 3.3):
 *   The current_state variable is static inside sm.c. Nothing outside sm.c
 *   can write to it directly. All state changes must flow through
 *   SM_Transition(), which guarantees symmetric entry/exit calling and
 *   provides a single point for debug logging or illegal-transition guards.
 *
 * Main loop integration (Section 3.6):
 *   The main loop calls SM_Run() once per iteration. SM_Run() dispatches to
 *   the current state's do_action, which is responsible for reading input
 *   (via InputManager_GetEvent), performing per-tick work, and requesting
 *   transitions when appropriate. The run-to-completion model means one
 *   do_action completes fully before the next tick — simple, deterministic,
 *   and interrupt-safe.
 *
 * State lifecycle (Section 3.7):
 *   | Action  | When           | Typical use                              |
 *   |---------|----------------|------------------------------------------|
 *   | entry   | On entering    | Init variables, draw display, enable hw  |
 *   | do      | Every tick     | Poll input, read ADC, update display     |
 *   | exit    | On leaving     | Cleanup, save data, clear display        |
 */

#ifndef SM_H
#define SM_H

/**
 * @brief Enumeration of all states in the firmware state machine.
 *
 * Each member corresponds to one entry in the state descriptor array inside
 * sm.c. The numeric values are used as array indices, so the enum must start
 * at 0 and be contiguous (no gaps, no explicit assignments).
 *
 * STATE_INIT:             One-shot initialization, transitions to SPLASH
 * STATE_SPLASH:           Display Microchip logo for a few seconds
 * STATE_MONITOR:          Default operating mode — reads ADC, drives DAC, displays
 * STATE_MENU:             Scrollable menu for selecting modes
 * STATE_RANGE_SET:        User sets which pressures map to 4/20 mA
 * STATE_SYSTEM_CALIBRATE: Unified calibration wizard (AFE, digipot, DAC, sensor)
 * STATE_MANUAL:           User-controlled DAC output for evaluation/debug
 * STATE_DEMO:             Sweep loop current for demonstration
 */
typedef enum {
    STATE_INIT,
    STATE_SPLASH,
    STATE_MONITOR,
    STATE_MENU,
    STATE_RANGE_SET,
    STATE_SYSTEM_CALIBRATE,
    STATE_MANUAL,
    STATE_DEMO
} SmState_t;

/**
 * @brief Initialize the state machine framework.
 *
 * Sets current_state to STATE_INIT and fires its entry action. The entry
 * action seeds all context parameters (SmContext_Init) and initializes the
 * input manager (InputManager_Init). After this call, the system is in
 * STATE_INIT — the first SM_Run() will trigger the unconditional transition
 * to STATE_MONITOR.
 *
 * Call once from main(), after SYSTEM_Initialize() and screen_init().
 */
void SM_Init(void);

/**
 * @brief Execute one tick of the state machine.
 *
 * Calls states[current_state].do_action(). This is the only call needed in
 * the main loop's while(1) body. Each state's do_action is responsible for
 * reading input, performing per-tick computation, and calling SM_Transition()
 * when a state change is needed.
 *
 * Do actions must be non-blocking — no DELAY_milliseconds() or busy-wait
 * loops. The entire main loop (all states, all peripherals) runs cooperatively
 * through this single call.
 */
void SM_Run(void);

/**
 * @brief Transition to a new state.
 *
 * This is the single enforcement point for ALL state changes in the firmware.
 * The sequence is:
 *   1. Call current state's exit action (cleanup, display clear, etc.)
 *   2. Update current_state to new_state
 *   3. Call new state's entry action (initialization, display draw, etc.)
 *
 * States call this from within their own do_action when they determine a
 * transition is needed (e.g., a specific button was pressed, or initialization
 * is complete). Never assign to current_state directly — always use this.
 *
 * @param new_state The state to transition to (must be a valid SmState_t value)
 */
void SM_Transition(SmState_t new_state);

/**
 * @brief Read the current state (read-only diagnostic access).
 *
 * Used by main.c to detect state changes for display updates, and potentially
 * by future diagnostic/debug screens. Does not modify any state.
 *
 * @return The current SmState_t value
 */
SmState_t SM_GetState(void);

#endif // SM_H
