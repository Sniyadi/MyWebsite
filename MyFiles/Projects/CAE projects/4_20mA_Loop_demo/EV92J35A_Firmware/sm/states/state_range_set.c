/**
 * STATE_RANGE_SET — User preference: choose which pressures map to 4/20 mA
 *
 * @file state_range_set.c
 *
 * @brief Lets the user define the measurement range by capturing the displayed
 *        pressure at the 4 mA and 20 mA loop current endpoints.
 *
 *        This is NOT calibration — it does not characterize hardware. It sets
 *        a user preference: which portion of the sensor's pressure range maps
 *        to the 4-20 mA measurement band.
 *
 *        Procedure:
 *          1. SUB_SET_4MA:  Forces loop to 4 mA, user confirms displayed PSI
 *          2. SUB_SET_20MA: Forces loop to 20 mA, user confirms displayed PSI
 *          3. SUB_CONFIRM:  Shows captured PSI values, user confirms to apply
 *
 *        Controls:
 *          RIGHT — confirm this step / advance
 *          LEFT  — cancel, return to menu without changes
 *
 *        Prerequisites: System calibration must be completed first so that
 *        LoopDriver_GetDacAt4mA()/GetDacAt20mA() return valid calibrated values.
 */

#include "state_range_set.h"
#include "../sm.h"
#include "../sm_context.h"
#include "../input_manager.h"
#include "../../fixed_point/q16.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"
#include "../adc_read.h"

typedef enum {
    SUB_SET_4MA,
    SUB_SET_20MA,
    SUB_CONFIRM
} SubState_t;

static SubState_t sub_state;

static int32_t psi_at_4ma_q16;
static int32_t psi_at_20ma_q16;

// --- Sub-state draw helpers ---

static void draw_set_4ma(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "  RANGE SET  ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(1, 0, "SET 4 mA PSI");
    screen_printf(3, 0, "CURRENT PSI:");
    screen_printf(7, 0, "CONFIRM: >");
    screen_printf(8, 0, "CANCEL: <");

    LoopDriver_SetDac(LoopDriver_GetDacAt4mA());

    screen_refresh();
}

static void draw_set_20ma(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "  RANGE SET  ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(1, 0, "SET 20 mA PSI");
    screen_printf(3, 0, "CURRENT PSI:");
    screen_printf(7, 0, "CONFIRM: >");
    screen_printf(8, 0, "CANCEL: <");

    LoopDriver_SetDac(LoopDriver_GetDacAt20mA());

    screen_refresh();
}

static void draw_confirm(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "  RANGE SET  ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(1, 0, "NEW RANGE:");

    int16_t psi4_whole;
    uint8_t psi4_frac;
    q16_split_whole_tenths(psi_at_4ma_q16, &psi4_whole, &psi4_frac);
    screen_printf(3, 0, "4 mA: %d.%u PSI", psi4_whole, psi4_frac);

    int16_t psi20_whole;
    uint8_t psi20_frac;
    q16_split_whole_tenths(psi_at_20ma_q16, &psi20_whole, &psi20_frac);
    screen_printf(4, 0, "20 mA: %d.%u PSI", psi20_whole, psi20_frac);

    screen_printf(7, 0, "APPLY: >");
    screen_printf(8, 0, "CANCEL: <");

    screen_refresh();
}

// --- Main state entry/do/exit ---

void StateRangeSet_Entry(void) {
    sub_state = SUB_SET_4MA;
    draw_set_4ma();
}

void StateRangeSet_Do(void) {
    InputEvent_t evt = InputManager_GetEvent();

    switch (sub_state) {

    case SUB_SET_4MA:
        if (evt == EVENT_RIGHT) {
            psi_at_4ma_q16 = SmContext_ComputePressure_q16(adc_read_filtered());

            screen_clear();
            draw_set_20ma();
            sub_state = SUB_SET_20MA;

        } else if (evt == EVENT_LEFT) {
            SM_Transition(STATE_MENU);

        } else {
            int32_t psi_q16 = SmContext_ComputePressure_q16(adc_read_filtered());

            int16_t psi_whole;
            uint8_t psi_frac;
            q16_split_whole_tenths(psi_q16, &psi_whole, &psi_frac);
            screen_printf(4, 0, "  %d.%u PSI", psi_whole, psi_frac);
            screen_refresh();
        }
        break;

    case SUB_SET_20MA:
        if (evt == EVENT_RIGHT) {
            psi_at_20ma_q16 = SmContext_ComputePressure_q16(adc_read_filtered());

            screen_clear();
            draw_confirm();
            sub_state = SUB_CONFIRM;

        } else if (evt == EVENT_LEFT) {
            SM_Transition(STATE_MENU);

        } else {
            int32_t psi_q16 = SmContext_ComputePressure_q16(adc_read_filtered());

            int16_t psi_whole;
            uint8_t psi_frac;
            q16_split_whole_tenths(psi_q16, &psi_whole, &psi_frac);
            screen_printf(4, 0, "  %d.%u PSI", psi_whole, psi_frac);
            screen_refresh();
        }
        break;

    case SUB_CONFIRM:
        if (evt == EVENT_RIGHT) {
            if (psi_at_20ma_q16 != psi_at_4ma_q16) {
                SmContext_SetRangeLowPressure_q16(psi_at_4ma_q16);
                SmContext_SetRangeHighPressure_q16(psi_at_20ma_q16);
                SmContext_RecomputeTransferFunctions();
            }
            SM_Transition(STATE_MENU);

        } else if (evt == EVENT_LEFT) {
            SM_Transition(STATE_MENU);
        }
        break;
    }
}

void StateRangeSet_Exit(void) {
    screen_clear();
    screen_refresh();
}
