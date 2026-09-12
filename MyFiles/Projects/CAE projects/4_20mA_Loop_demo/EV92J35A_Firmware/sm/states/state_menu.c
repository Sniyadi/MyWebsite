/**
 * STATE_MENU — Scrollable mode selection menu
 *
 * @file state_menu.c
 *
 * @brief Displays a 5-item menu (MONITOR, RANGE SET, CALIBRATE, DEMO, RE-INIT)
 *        and lets the user scroll with up/down and confirm with push. The
 *        selected item is shown as an inverted row. Selection wraps around.
 */

#include "state_menu.h"
#include "../sm.h"
#include "../nvm_cal.h"
#include "../input_manager.h"
#include "../../sharp_display/screen.h"

#define MENU_ITEM_COUNT  7

static uint8_t selected;

static const SmState_t target_states[MENU_ITEM_COUNT] = {
    STATE_MONITOR,
    STATE_RANGE_SET,
    STATE_SYSTEM_CALIBRATE,
    STATE_MANUAL,
    STATE_DEMO,
    STATE_SPLASH,
    STATE_INIT
};

void StateMenu_Entry(void) {
    screen_set_font_style(FONT_STYLE_BOLD);
    screen_printf(0, 0, "     MENU    ");
    screen_set_inverted(0, true);

    screen_set_font_style(FONT_STYLE_NORMAL);
    screen_printf(2, 0, "MONITOR");
    screen_printf(3, 0, "RANGE SET");
    screen_printf(4, 0, "CALIBRATE");
    screen_printf(5, 0, "MANUAL");
    screen_printf(6, 0, "DEMO");
    screen_printf(7, 0, "SPLASH");
    screen_printf(8, 0, "FACTORY RST");

    selected = 0;
    screen_set_inverted(2, true);

    screen_refresh();
}

void StateMenu_Do(void) {
    InputEvent_t evt = InputManager_GetEvent();

    if (evt == EVENT_DOWN) {
        screen_set_inverted(selected + 2, false);
        selected = (selected + 1) % MENU_ITEM_COUNT;
        screen_set_inverted(selected + 2, true);
        screen_refresh();

    } else if (evt == EVENT_UP) {
        screen_set_inverted(selected + 2, false);
        selected = (selected == 0) ? MENU_ITEM_COUNT - 1 : selected - 1;
        screen_set_inverted(selected + 2, true);
        screen_refresh();

    } else if (evt == EVENT_PUSH) {
        if (selected == MENU_ITEM_COUNT - 1) {
            NvmCal_Invalidate();
        }
        SM_Transition(target_states[selected]);
    }
}

void StateMenu_Exit(void) {
    screen_clear();
    screen_refresh();
}
