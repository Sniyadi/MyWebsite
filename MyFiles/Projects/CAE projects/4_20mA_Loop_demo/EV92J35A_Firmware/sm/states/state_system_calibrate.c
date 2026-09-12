/**
 * STATE_SYSTEM_CALIBRATE — Unified system calibration wizard
 *
 * @file state_system_calibrate.c
 *
 * @brief Walks the user through all calibration steps in dependency order:
 *
 *        Step 1: AFE Offset Trim (sensor at 0 PSI required)
 *        Step 2: Digipot Trim (set loop floor to ~3.6 mA)
 *        Step 3: DAC at 4 mA (external meter required)
 *        Step 4: DAC at 20 mA (external meter required)
 *        Step 5: Sensor Low (apply 0 PSI, capture ADC)
 *        Step 6: Sensor High (apply 50 PSI, capture ADC)
 *        Step 7: Confirm and apply all values
 *
 *        Controls (consistent across all steps):
 *          UP/DOWN — adjust current parameter (steps 1-4)
 *          RIGHT   — confirm this step / advance to next
 *          LEFT    — cancel ALL changes, restore originals, return to menu
 *
 *        Cancel at any step restores all hardware to its entry state.
 *        Apply at the final step commits all constants and recomputes TFs.
 */

#include "state_system_calibrate.h"
#include "../sm.h"
#include "../sm_context.h"
#include "../sm_constants.h"
#include "../nvm_cal.h"
#include "../input_manager.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"
#include "../../config.mcc/mcc_generated_files/dac/dac1.h"
#include "../adc_read.h"

/* --- Step sizes --- */
#define AFE_TRIM_STEP       (8u)
#define DIGIPOT_TRIM_STEP   (1u)
#define DAC_CAL_STEP        (16u)

/* --- Sub-state machine --- */

typedef enum {
    SUB_AFE_TRIM,
    SUB_DIGIPOT_TRIM,
    SUB_DAC_4MA,
    SUB_DAC_20MA,
    SUB_SENSOR_LOW,
    SUB_SENSOR_HIGH,
    SUB_CONFIRM
} CalibSubState_t;

static CalibSubState_t sub_state;

/* --- Working values (modified during calibration) --- */
static uint16_t current_afe_dac;
static uint8_t  current_digipot;
static uint16_t captured_dac_4ma;
static uint16_t captured_dac_20ma;
static uint16_t current_dac;
static uint16_t captured_adc_low;
static uint16_t captured_adc_high;

/* --- Original values (restored on cancel) --- */
static uint16_t orig_afe_dac;
static uint8_t  orig_digipot;
static uint16_t orig_dac_at_4mA;
static uint16_t orig_dac_at_20mA;
static uint16_t orig_adc_sensor_low;
static uint16_t orig_adc_sensor_high;

/* --- Display suppression --- */
static uint16_t last_displayed_val;

/* --- Cancel: restore all originals and return to menu --- */

static void cancel_and_restore(void) {
    DAC1_SetOutput(orig_afe_dac);
    LoopDriver_SetDigipot(orig_digipot);
    LoopDriver_SetDacAt4mA(orig_dac_at_4mA);
    LoopDriver_SetDacAt20mA(orig_dac_at_20mA);
    LoopDriver_RecomputeTransfer();
    SmContext_SetAdcAtSensorLow(orig_adc_sensor_low);
    SmContext_SetAdcAtSensorHigh(orig_adc_sensor_high);
    SmContext_RecomputeTransferFunctions();
    SM_Transition(STATE_MENU);
}

/* --- Draw helpers (one per sub-state) --- */

static void draw_title(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "  SYS CALIB  ");
    screen_set_inverted(0, true);
    screen_set_font_style(FONT_STYLE_NORMAL);
}

static void draw_afe_trim(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 1/6");
    screen_printf(2, 0, "AFE OFFSET");
    screen_printf(3, 0, "APPLY 0 PSI");
    uint16_t dac_mv = SmContext_ComputeMCUDacVoltage_mV(current_afe_dac);
    screen_printf(4, 0, "DAC: %u mV  ", dac_mv);
    uint16_t adc_mv = SmContext_ComputeAdcVoltage_mV(adc_read_filtered());
    screen_printf(5, 0, "ADC: %u mV  ", adc_mv);
    screen_printf(6, 0, "INC: ^ DEC: v");
    screen_printf(7, 0, "NEXT: >");
    screen_printf(8, 0, "CANCEL: <");
    last_displayed_val = 0xFFFF;
    screen_refresh();
}

static void draw_digipot_trim(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 2/6");
    screen_printf(2, 0, "LOOP FLOOR");
    screen_printf(3, 0, "TARGET: 3.6mA");
    screen_printf(4, 0, "WIPER: %u   ", current_digipot);
    screen_printf(6, 0, "INC: ^ DEC: v");
    screen_printf(7, 0, "NEXT: >");
    screen_printf(8, 0, "CANCEL: <");
    screen_refresh();
}

static void draw_dac_4ma(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 3/6");
    screen_printf(2, 0, "SET 4.000 mA");
    screen_printf(3, 0, "DAC: %u   ", current_dac);
    screen_printf(6, 0, "INC: ^ DEC: v");
    screen_printf(7, 0, "NEXT: >");
    screen_printf(8, 0, "CANCEL: <");
    screen_refresh();
}

static void draw_dac_20ma(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 4/6");
    screen_printf(2, 0, "SET 20.000 mA");
    screen_printf(3, 0, "DAC: %u   ", current_dac);
    screen_printf(6, 0, "INC: ^ DEC: v");
    screen_printf(7, 0, "NEXT: >");
    screen_printf(8, 0, "CANCEL: <");
    screen_refresh();
}

static void draw_sensor_low(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 5/6");
    screen_printf(2, 0, "APPLY 0 PSI");
    screen_printf(3, 0, "ADC: %u   ", adc_read_filtered());
    screen_printf(7, 0, "CAPTURE: >");
    screen_printf(8, 0, "CANCEL: <");
    last_displayed_val = 0xFFFF;
    screen_refresh();
}

static void draw_sensor_high(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "STEP 6/6");
    screen_printf(2, 0, "APPLY 50 PSI");
    screen_printf(3, 0, "ADC: %u   ", adc_read_filtered());
    screen_printf(7, 0, "CAPTURE: >");
    screen_printf(8, 0, "CANCEL: <");
    last_displayed_val = 0xFFFF;
    screen_refresh();
}

static void draw_confirm(void) {
    screen_clear();
    draw_title();
    screen_printf(1, 0, "RESULTS:");
    screen_printf(2, 0, "AFE: %u", current_afe_dac);
    screen_printf(3, 0, "DPOT: %u", current_digipot);
    screen_printf(4, 0, "4mA: %u", captured_dac_4ma);
    screen_printf(5, 0, "20mA: %u", captured_dac_20ma);
    screen_printf(6, 0, "ADC LO: %u", captured_adc_low);
    screen_printf(7, 0, "APPLY: >");
    screen_printf(8, 0, "CANCEL: <");
    screen_refresh();
}

/* --- Entry / Do / Exit --- */

void StateSystemCalibrate_Entry(void) {
    /* Save all originals for cancel-restore */
    orig_afe_dac         = DAC1_GetOutput();
    orig_digipot         = LoopDriver_GetDigipot();
    orig_dac_at_4mA      = LoopDriver_GetDacAt4mA();
    orig_dac_at_20mA     = LoopDriver_GetDacAt20mA();
    orig_adc_sensor_low  = SmContext_GetAdcAtSensorLow();
    orig_adc_sensor_high = SmContext_GetAdcAtSensorHigh();

    /* Initialize working values from current state */
    current_afe_dac  = orig_afe_dac;
    current_digipot  = orig_digipot;
    current_dac      = 0;
    captured_dac_4ma = orig_dac_at_4mA;
    captured_dac_20ma = orig_dac_at_20mA;
    captured_adc_low = 0;
    captured_adc_high = 0;

    sub_state = SUB_AFE_TRIM;
    draw_afe_trim();
}

void StateSystemCalibrate_Do(void) {
    InputEvent_t evt = InputManager_GetEvent();

    /* Global cancel — LEFT at any step */
    if (evt == EVENT_LEFT) {
        cancel_and_restore();
        return;
    }

    switch (sub_state) {

    case SUB_AFE_TRIM:
        if (evt == EVENT_UP) {
            if (current_afe_dac + AFE_TRIM_STEP > AFE_DAC_MAX) {
                current_afe_dac = AFE_DAC_MAX;
            } else {
                current_afe_dac += AFE_TRIM_STEP;
            }
            DAC1_SetOutput(current_afe_dac);
        } else if (evt == EVENT_DOWN) {
            if (current_afe_dac < AFE_TRIM_STEP) {
                current_afe_dac = 0;
            } else {
                current_afe_dac -= AFE_TRIM_STEP;
            }
            DAC1_SetOutput(current_afe_dac);
        } else if (evt == EVENT_RIGHT) {
            /* Advance to digipot trim */
            LoopDriver_SetDac(0);
            sub_state = SUB_DIGIPOT_TRIM;
            draw_digipot_trim();
            return;
        }
        /* Live feedback: update DAC mV and ADC mV displays */
        {
            uint16_t dac_mv = SmContext_ComputeMCUDacVoltage_mV(current_afe_dac);
            screen_printf(4, 0, "DAC: %u mV  ", dac_mv);
            uint16_t adc_mv = SmContext_ComputeAdcVoltage_mV(adc_read_filtered());
            if (adc_mv != last_displayed_val) {
                screen_printf(5, 0, "ADC: %u mV  ", adc_mv);
                last_displayed_val = adc_mv;
            }
            screen_refresh();
        }
        break;

    case SUB_DIGIPOT_TRIM:
        if (evt == EVENT_UP) {
            if ((uint16_t)current_digipot + DIGIPOT_TRIM_STEP > 255u) {
                current_digipot = 255u;
            } else {
                current_digipot += DIGIPOT_TRIM_STEP;
            }
            LoopDriver_SetDigipot(current_digipot);
            screen_printf(4, 0, "WIPER: %u   ", current_digipot);
            screen_refresh();
        } else if (evt == EVENT_DOWN) {
            if (current_digipot < DIGIPOT_TRIM_STEP) {
                current_digipot = 0;
            } else {
                current_digipot -= DIGIPOT_TRIM_STEP;
            }
            LoopDriver_SetDigipot(current_digipot);
            screen_printf(4, 0, "WIPER: %u   ", current_digipot);
            screen_refresh();
        } else if (evt == EVENT_RIGHT) {
            /* Advance to DAC 4 mA — start at last known-good value */
            current_dac = captured_dac_4ma;
            LoopDriver_SetDac(current_dac);
            sub_state = SUB_DAC_4MA;
            draw_dac_4ma();
        }
        break;

    case SUB_DAC_4MA:
        if (evt == EVENT_UP) {
            if (current_dac + DAC_CAL_STEP >= LOOP_DAC_MAX) {
                current_dac = LOOP_DAC_MAX;
            } else {
                current_dac += DAC_CAL_STEP;
            }
            LoopDriver_SetDac(current_dac);
            screen_printf(3, 0, "DAC: %u   ", current_dac);
            screen_refresh();
        } else if (evt == EVENT_DOWN) {
            if (current_dac < DAC_CAL_STEP) {
                current_dac = 0;
            } else {
                current_dac -= DAC_CAL_STEP;
            }
            LoopDriver_SetDac(current_dac);
            screen_printf(3, 0, "DAC: %u   ", current_dac);
            screen_refresh();
        } else if (evt == EVENT_RIGHT) {
            /* Capture 4 mA DAC code, advance to 20 mA */
            captured_dac_4ma = current_dac;
            current_dac = captured_dac_20ma;
            LoopDriver_SetDac(current_dac);
            sub_state = SUB_DAC_20MA;
            draw_dac_20ma();
        }
        break;

    case SUB_DAC_20MA:
        if (evt == EVENT_UP) {
            if (current_dac + DAC_CAL_STEP >= LOOP_DAC_MAX) {
                current_dac = LOOP_DAC_MAX;
            } else {
                current_dac += DAC_CAL_STEP;
            }
            LoopDriver_SetDac(current_dac);
            screen_printf(3, 0, "DAC: %u   ", current_dac);
            screen_refresh();
        } else if (evt == EVENT_DOWN) {
            if (current_dac < DAC_CAL_STEP) {
                current_dac = 0;
            } else {
                current_dac -= DAC_CAL_STEP;
            }
            LoopDriver_SetDac(current_dac);
            screen_printf(3, 0, "DAC: %u   ", current_dac);
            screen_refresh();
        } else if (evt == EVENT_RIGHT) {
            /* Capture 20 mA DAC code, advance to sensor low */
            captured_dac_20ma = current_dac;
            sub_state = SUB_SENSOR_LOW;
            draw_sensor_low();
        }
        break;

    case SUB_SENSOR_LOW:
        if (evt == EVENT_RIGHT) {
            /* Capture current ADC reading as sensor low point */
            captured_adc_low = adc_read_filtered();
            sub_state = SUB_SENSOR_HIGH;
            draw_sensor_high();
        } else {
            /* Live ADC display so user can wait for stability */
            uint16_t adc_val = adc_read_filtered();
            if (adc_val != last_displayed_val) {
                screen_printf(3, 0, "ADC: %u   ", adc_val);
                last_displayed_val = adc_val;
                screen_refresh();
            }
        }
        break;

    case SUB_SENSOR_HIGH:
        if (evt == EVENT_RIGHT) {
            /* Capture current ADC reading as sensor high point */
            captured_adc_high = adc_read_filtered();
            sub_state = SUB_CONFIRM;
            draw_confirm();
        } else {
            /* Live ADC display so user can wait for stability */
            uint16_t adc_val = adc_read_filtered();
            if (adc_val != last_displayed_val) {
                screen_printf(3, 0, "ADC: %u   ", adc_val);
                last_displayed_val = adc_val;
                screen_refresh();
            }
        }
        break;

    case SUB_CONFIRM:
        if (evt == EVENT_RIGHT) {
            /* Apply all calibration constants */
            SmContext_SetAfeDacTrim(current_afe_dac);
            LoopDriver_SetDigipotTrim(current_digipot);
            LoopDriver_SetDacAt4mA(captured_dac_4ma);
            LoopDriver_SetDacAt20mA(captured_dac_20ma);
            LoopDriver_RecomputeTransfer();
            SmContext_SetAdcAtSensorLow(captured_adc_low);
            SmContext_SetAdcAtSensorHigh(captured_adc_high);
            SmContext_RecomputeTransferFunctions();

            NvmCalData_t nvm_data;
            nvm_data.marker = NVM_CAL_VALID_MARKER;
            nvm_data.digipot_trim = current_digipot;
            nvm_data.afe_dac_trim = current_afe_dac;
            nvm_data.dac_at_4mA = captured_dac_4ma;
            nvm_data.dac_at_20mA = captured_dac_20ma;
            nvm_data.adc_at_sensor_low = captured_adc_low;
            nvm_data.adc_at_sensor_high = captured_adc_high;
            NvmCal_Write(&nvm_data);

            SM_Transition(STATE_MENU);
        }
        break;
    }
}

void StateSystemCalibrate_Exit(void) {
    screen_clear();
    screen_refresh();
}
