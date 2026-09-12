/**
 * STATE_MENU — Scrollable mode selection menu
 *
 * @file state_menu.h
 *
 * @brief Displays a 6-item menu allowing the user to select which operating
 *        mode to enter. Up/down moves the highlight (with wrap), push confirms
 *        selection and transitions to the chosen state.
 */

#ifndef STATE_MENU_H
#define STATE_MENU_H

void StateMenu_Entry(void);
void StateMenu_Do(void);
void StateMenu_Exit(void);

#endif // STATE_MENU_H
