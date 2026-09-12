/**
 * State Machine Framework — Implementation
 *
 * @file sm.c
 *
 * @brief Contains the state descriptor array, current_state variable, and
 *        SM_Init/SM_Run/SM_Transition/SM_GetState implementations.
 *
 * This is the central coordinator of the firmware. It owns only the framework:
 *   - The dispatch mechanism (function pointer table)
 *   - The transition enforcement (exit → update → entry sequence)
 *   - The current_state variable (hidden from all other modules)
 *
 * Each state's entry/do/exit logic lives in its own file under sm/states/.
 * This file includes those headers and wires their functions into the
 * dispatch table. The framework functions never need modification when
 * state behavior changes — only the state files themselves are edited.
 *
 * Memory layout:
 *   - states[] array is const — lives in program flash, costs zero RAM
 *   - current_state is one byte of RAM (enum fits in uint8_t on XC8)
 *
 * Transition safety (see loop_driver_firmware_context.md, Section 3.4):
 *   SM_Transition() is the only function that writes current_state. This is
 *   the single enforcement point where debug logging, assertions, watchdog
 *   kicks, or illegal-transition guards can be added for all transitions at
 *   once. States never assign to current_state directly.
 */

#include "sm.h"
#include "states/state_init.h"
#include "states/state_splash.h"
#include "states/state_monitor.h"
#include "states/state_menu.h"
#include "states/state_range_set.h"
#include "states/state_system_calibrate.h"
#include "states/state_manual.h"
#include "states/state_demo.h"

/* --- State Descriptor Struct ---
 *
 * Each state is fully described by three function pointers. The struct is
 * intentionally minimal — no state name string, no transition table, no
 * sub-state storage. Those belong in individual state modules, not here.
 *
 * The typedef is private to this file because nothing outside sm.c needs
 * to know the internal representation of states. */
typedef struct {
    void (*entry)(void);
    void (*do_action)(void);
    void (*exit)(void);
} StateDescriptor_t;

/* --- State Descriptor Array ---
 *
 * Const qualifier places this in program flash on PIC18, saving 7×6 = 42
 * bytes of RAM (each entry is 3 function pointers × 2 bytes on PIC18).
 *
 * Designated initializers ([STATE_INIT] = {...}) ensure correctness even if
 * the enum order changes. XC8 supports C99 designated initializers.
 *
 * The array is indexed by SmState_t values, which are guaranteed contiguous
 * starting at 0. SM_Run() and SM_Transition() index directly without bounds
 * checking — the caller is trusted to pass valid enum values. */
static const StateDescriptor_t states[] = {
    [STATE_INIT]              = { StateInit_Entry,            StateInit_Do,            StateInit_Exit },
    [STATE_SPLASH]            = { StateSplash_Entry,          StateSplash_Do,          StateSplash_Exit },
    [STATE_MONITOR]           = { StateMonitor_Entry,         StateMonitor_Do,         StateMonitor_Exit },
    [STATE_MENU]              = { StateMenu_Entry,            StateMenu_Do,            StateMenu_Exit },
    [STATE_RANGE_SET]         = { StateRangeSet_Entry,        StateRangeSet_Do,        StateRangeSet_Exit },
    [STATE_SYSTEM_CALIBRATE]  = { StateSystemCalibrate_Entry, StateSystemCalibrate_Do, StateSystemCalibrate_Exit },
    [STATE_MANUAL]            = { StateManual_Entry,          StateManual_Do,          StateManual_Exit },
    [STATE_DEMO]              = { StateDemo_Entry,            StateDemo_Do,            StateDemo_Exit },
};

/* --- Module State ---
 *
 * The single variable that tracks which state the machine is in. Static
 * file-scope means no other module can read or write it — SM_GetState()
 * provides read-only access, SM_Transition() provides write access.
 * This encapsulation guarantees all transitions are auditable at one point. */
static SmState_t current_state;

// ============================================================================
// Public API
// ============================================================================

void SM_Init(void) {
    current_state = STATE_INIT;
    states[STATE_INIT].entry();
}

void SM_Run(void) {
    states[current_state].do_action();
}

void SM_Transition(SmState_t new_state) {
    states[current_state].exit();
    current_state = new_state;
    states[new_state].entry();
}

SmState_t SM_GetState(void) {
    return current_state;
}
