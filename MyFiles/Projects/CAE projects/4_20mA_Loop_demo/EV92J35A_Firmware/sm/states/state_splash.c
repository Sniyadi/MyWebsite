/**
 * STATE_SPLASH — Display Microchip logo for a fixed duration
 *
 * @file state_splash.c
 *
 * @brief Streams the Microchip logo bitmap to the SHARP display and holds it
 *        for SPLASH_DURATION_TICKS before transitioning to STATE_MONITOR.
 *        The logo is stored in program flash and streamed one scan line at a
 *        time — no RAM framebuffer required.
 */

#include "state_splash.h"
#include "../sm.h"
#include "../../systick/systick.h"
#include "../../sharp_display/sharp_mem.h"
#include "../../sharp_display/screen.h"
#include "../../sharp_display/microchip_logo_144x168.h"

#define SPLASH_DURATION_TICKS   30  /* 3 seconds at 10 Hz */

static uint32_t start_tick;

void StateSplash_Entry(void) {
    sharp_begin_frame();
    for (uint8_t line = 1; line <= LOGO_HEIGHT; line++) {
        sharp_write_line(line, &microchip_logo[(line - 1) * 18], 18);
    }
    sharp_end_frame();

    start_tick = Systick_GetTicks();
}

void StateSplash_Do(void) {
    if (Systick_Elapsed(start_tick, SPLASH_DURATION_TICKS)) {
        SM_Transition(STATE_MONITOR);
    }
}

void StateSplash_Exit(void) {
    screen_clear();
    screen_refresh();
}
