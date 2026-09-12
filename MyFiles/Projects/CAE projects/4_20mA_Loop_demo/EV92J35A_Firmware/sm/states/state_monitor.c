/**
 * STATE_MONITOR — Default operating mode (read sensor, drive loop, display)
 *
 * @file state_monitor.c
 *
 * @brief Implements the primary operating loop of the firmware:
 *        1. Read the 12-bit ADC connected to the pressure sensor
 *        2. Compute tank pressure (PSI) and requested loop current (mA)
 *        3. Check for NAMUR NE43 alarm conditions (under/over-range)
 *        4. Drive the loop: normal DAC code, or alarm current via SetCurrent
 *        5. Update the SHARP display with PSI, mA, and alarm status
 *
 * NAMUR NE43 alarm behavior:
 *        When the computed current falls outside the 4-20 mA valid band
 *        (because the measured pressure is outside the user-defined range),
 *        the transmitter drives an alarm current:
 *          Under-range (< 4 mA): drives 3.6 mA
 *          Over-range (> 20 mA): drives 21.0 mA
 *        The alarm condition and current are displayed on the screen.
 */

#include "state_monitor.h"
#include "../sm.h"
#include "../sm_context.h"
#include "../sm_constants.h"
#include "../input_manager.h"
#include "../../fixed_point/q16.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"
#include "../adc_read.h"

typedef enum {
    LOOP_NORMAL,
    LOOP_UNDER_RANGE,
    LOOP_OVER_RANGE
} LoopStatus_t;

static int32_t last_displayed_pressure_q16;
static int32_t last_displayed_current_q16;
static LoopStatus_t last_status;

void StateMonitor_Entry(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "   MONITOR   ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(2, 0, "      PSI");
    screen_printf(4, 0, "      mA");

    screen_printf(8, 0, "< MENU");
    screen_refresh();

    last_displayed_pressure_q16 = 0x7FFFFFFFL;
    last_displayed_current_q16  = 0x7FFFFFFFL;
    last_status = LOOP_NORMAL;
}

void StateMonitor_Do(void) {
    InputEvent_t evt = InputManager_GetEvent();
    if (evt == EVENT_LEFT) {
        SM_Transition(STATE_MENU);
        return;
    }

    uint16_t adc_counts = adc_read_filtered();

    int32_t pressure_q16 = SmContext_ComputePressure_q16(adc_counts);
    int32_t current_q16  = SmContext_ComputeLoopCurrent_mA_q16(adc_counts);

    /* Determine alarm status with hysteresis */
    LoopStatus_t status;

    if (last_status == LOOP_NORMAL) {
        if (current_q16 < ALARM_ENTER_LOW_Q16) {
            status = LOOP_UNDER_RANGE;
        } else if (current_q16 > ALARM_ENTER_HIGH_Q16) {
            status = LOOP_OVER_RANGE;
        } else {
            status = LOOP_NORMAL;
        }
    } else if (last_status == LOOP_UNDER_RANGE) {
        if (current_q16 > ALARM_EXIT_LOW_Q16) {
            status = LOOP_NORMAL;
        } else {
            status = LOOP_UNDER_RANGE;
        }
    } else {
        if (current_q16 < ALARM_EXIT_HIGH_Q16) {
            status = LOOP_NORMAL;
        } else {
            status = LOOP_OVER_RANGE;
        }
    }

    /* Drive the loop based on alarm status */
    int32_t displayed_current_q16;

    if (status == LOOP_UNDER_RANGE) {
        displayed_current_q16 = ALARM_CURRENT_LOW_Q16;
        LoopDriver_SetCurrent_mA_q16(ALARM_CURRENT_LOW_Q16);
    } else if (status == LOOP_OVER_RANGE) {
        displayed_current_q16 = ALARM_CURRENT_HIGH_Q16;
        LoopDriver_SetCurrent_mA_q16(ALARM_CURRENT_HIGH_Q16);
    } else {
        displayed_current_q16 = current_q16;
        uint16_t dac_code = SmContext_ComputeDacFromAdc(adc_counts);
        LoopDriver_SetDac(dac_code);
    }

    /* Update pressure display */
    if ((pressure_q16 >> 13) != (last_displayed_pressure_q16 >> 13)) {
        int16_t psi_whole;
        uint8_t psi_frac;
        q16_split_whole_tenths(pressure_q16, &psi_whole, &psi_frac);
        screen_printf(2, 0, "  %d.%u PSI  ", psi_whole, psi_frac);
        last_displayed_pressure_q16 = pressure_q16;
    }

    /* Update current display */
    if ((displayed_current_q16 >> 13) != (last_displayed_current_q16 >> 13)) {
        int16_t ma_whole;
        uint8_t ma_frac;
        q16_split_whole_tenths(displayed_current_q16, &ma_whole, &ma_frac);
        screen_printf(4, 0, "  %d.%u mA  ", ma_whole, ma_frac);
        last_displayed_current_q16 = displayed_current_q16;
    }

    /* Update alarm status display (row 6) on status change */
    if (status != last_status) {
        switch (status) {
        case LOOP_UNDER_RANGE:
            screen_printf(6, 0, "  LO ALARM   ");
            break;
        case LOOP_OVER_RANGE:
            screen_printf(6, 0, "  HI ALARM   ");
            break;
        case LOOP_NORMAL:
            screen_printf(6, 0, "             ");
            break;
        }
        last_status = status;
    }

    screen_refresh();
}

void StateMonitor_Exit(void) {
    screen_clear();
    screen_refresh();
}
