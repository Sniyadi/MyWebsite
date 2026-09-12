/**
 * STATE_INIT — One-shot initialization, then transition to SPLASH
 *
 * @file state_init.c
 *
 * @brief Initializes all peripherals and drivers, seeds calibration constants
 *        from compile-time defaults, then overrides with NVM-stored values if
 *        a valid calibration exists in EEPROM. Immediately transitions to
 *        STATE_SPLASH.
 *
 * Init ordering:
 *   1. LoopDriver_Init() — hardware + compile-time defaults for loop driver
 *   2. DAC1_Initialize() — AFE offset DAC hardware
 *   3. InputManager_Init() — button input
 *   4. SmContext_Init() — compile-time defaults + Recompute (reads loop_driver)
 *   5. NVM load — overrides RAM values if valid calibration stored
 */

#include "state_init.h"
#include "../sm.h"
#include "../sm_context.h"
#include "../nvm_cal.h"
#include "../input_manager.h"
#include "../../sharp_display/screen.h"
#include "../../loop_driver/loop_driver.h"
#include "../../config.mcc/mcc_generated_files/dac/dac1.h"

void StateInit_Entry(void) {
    LoopDriver_Init();
    DAC1_Initialize();
    InputManager_Init();
    SmContext_Init();

    if (NvmCal_IsValid()) {
        NvmCalData_t stored;
        NvmCal_Read(&stored);

        LoopDriver_SetDigipotTrim(stored.digipot_trim);
        LoopDriver_SetDacAt4mA(stored.dac_at_4mA);
        LoopDriver_SetDacAt20mA(stored.dac_at_20mA);
        LoopDriver_RecomputeTransfer();

        SmContext_SetAfeDacTrim(stored.afe_dac_trim);
        DAC1_SetOutput(stored.afe_dac_trim);
        SmContext_SetAdcAtSensorLow(stored.adc_at_sensor_low);
        SmContext_SetAdcAtSensorHigh(stored.adc_at_sensor_high);
        SmContext_RecomputeTransferFunctions();
    }
}

void StateInit_Do(void) {
    SM_Transition(STATE_SPLASH);
}

void StateInit_Exit(void) {
    // Clear screen so MONITOR starts with a blank slate
    screen_clear();
    screen_refresh();
}
