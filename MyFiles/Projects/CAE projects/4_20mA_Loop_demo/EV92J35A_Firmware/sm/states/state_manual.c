/**
 * STATE_MANUAL — User-controlled DAC output for evaluation and debugging
 *
 * @file state_manual.c
 *
 * @brief Lets the user directly increment/decrement the loop driver DAC code
 *        and displays the corresponding requested loop current. Useful for
 *        comparing requested vs. actual current (external meter), evaluating
 *        DAC linearity, and debugging calibration discrepancies.
 *
 *        Controls:
 *          UP   — increment DAC code
 *          DOWN — decrement DAC code
 *          LEFT — return to menu
 */

#include "state_manual.h"
#include "../sm.h"
#include "../input_manager.h"
#include "../../fixed_point/q16.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"

#define MANUAL_DAC_STEP  (16u)

static uint16_t current_dac;

static void update_display(void) {
    screen_printf(2, 0, "DAC: %u   ", current_dac);

    int32_t current_q16 = LoopDriver_ComputeCurrent_mA_q16(current_dac);
    int16_t ma_whole;
    uint8_t ma_frac;
    q16_split_whole_tenths(current_q16, &ma_whole, &ma_frac);
    screen_printf(3, 0, "REQ: %d.%u mA  ", ma_whole, ma_frac);

    screen_refresh();
}

void StateManual_Entry(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "   MANUAL    ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(6, 0, "INC: ^ DEC: v");
    screen_printf(8, 0, "< MENU");

    current_dac = 0;
    LoopDriver_SetDac(current_dac);
    update_display();
}

void StateManual_Do(void) {
    InputEvent_t evt = InputManager_GetEvent();

    if (evt == EVENT_LEFT) {
        SM_Transition(STATE_MENU);
        return;
    } else if (evt == EVENT_UP) {
        if (current_dac + MANUAL_DAC_STEP >= LOOP_DAC_MAX) {
            current_dac = LOOP_DAC_MAX;
        } else {
            current_dac += MANUAL_DAC_STEP;
        }
        LoopDriver_SetDac(current_dac);
        update_display();
    } else if (evt == EVENT_DOWN) {
        if (current_dac < MANUAL_DAC_STEP) {
            current_dac = 0;
        } else {
            current_dac -= MANUAL_DAC_STEP;
        }
        LoopDriver_SetDac(current_dac);
        update_display();
    }
}

void StateManual_Exit(void) {
    screen_clear();
    screen_refresh();
}
