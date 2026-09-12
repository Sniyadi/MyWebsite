/**
 * STATE_DEMO — Manual DAC adjustment with live mA readback
 *
 * @file state_demo.c
 *
 * @brief Allows the user to manually step the external DAC up/down using the
 *        joystick, while displaying the corresponding loop current computed
 *        from the DAC code via the inverse TF3 transfer function.
 *
 *        UP/DOWN buttons increment/decrement the DAC code by DEMO_DAC_STEP.
 *        The display shows both the computed mA value and the raw DAC code.
 *        LEFT exits back to the menu.
 *
 * Display suppression:
 *        The DAC value only changes on button press. Display and DAC writes
 *        are performed only when the value actually changes, eliminating all
 *        font rendering and SPI traffic on idle ticks (zero work when no
 *        buttons are pressed).
 */

#include "state_demo.h"
#include "../sm.h"
#include "../input_manager.h"
#include "../../fixed_point/q16.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"

#include <stdbool.h>
#include <stdint.h>


/* DAC counts per button press — adjust to control step granularity */
#define DEMO_DAC_STEP   (64u)

/* Triangle wave state */
static uint16_t dac_value;
static bool increasing;

/* Display suppression: only refresh after a button press changes dac_value */
static bool display_needs_update;

void StateDemo_Entry(void) {
    /* Title bar: bold, white-on-black */
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "     DEMO    ");
    screen_set_inverted(0, true);

    /* Static labels and initial values */
    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(2, 0, "REQUESTED CURRENT:");
    screen_printf(3, 0, "  4.0 mA");
    screen_printf(5, 0, "DAC VALUE:");
    screen_printf(6, 0, "  0");

    /* Navigation hint */
    screen_printf(8, 0, "< MENU");

    /* Initialize at bottom of range */
    dac_value = 0;
    increasing = true;
    LoopDriver_SetDac(0);

    screen_refresh();

    /* Mark as needing no further update until a button is pressed */
    display_needs_update = false;
}

void StateDemo_Do(void) {
    /* Check for menu navigation */
    InputEvent_t evt = InputManager_GetEvent();
    if (evt == EVENT_LEFT) {
        SM_Transition(STATE_MENU);
        return;
    }


    // Triangle wave generation
    if(increasing) {
        /* Increment DAC value with clamp at maximum */
        if (dac_value + DEMO_DAC_STEP >= LOOP_DAC_MAX) {
            dac_value = LOOP_DAC_MAX;
            increasing = false;
        } else {
            dac_value += DEMO_DAC_STEP;
        }
        display_needs_update = true;
    }
    else {
        /* Decrement DAC value with underflow protection */
        if (dac_value < DEMO_DAC_STEP) {
            dac_value = 0;
            increasing = true;
        } else {
            dac_value -= DEMO_DAC_STEP;
        }
        display_needs_update = true;
    }

    /* Only drive DAC and refresh display when dac_value actually changed */
    if (display_needs_update) {
        display_needs_update = false;

        LoopDriver_SetDac(dac_value);

        /* Compute and display the current in mA via inverse TF3 */
        int32_t current_q16 = LoopDriver_ComputeCurrent_mA_q16(dac_value);
        int16_t ma_whole;
        uint8_t ma_frac;
        q16_split_whole_tenths(current_q16, &ma_whole, &ma_frac);
        screen_printf(3, 0, "  %d.%u mA", ma_whole, ma_frac);

        /* Display raw DAC value (trailing spaces clear shorter previous values) */
        screen_printf(6, 0, "  %u   ", dac_value);

        screen_refresh();
    }
}

void StateDemo_Exit(void) {
    screen_clear();
    screen_refresh();
}
