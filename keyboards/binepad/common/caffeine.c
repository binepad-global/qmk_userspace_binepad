// Copyright 2023 Vino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include <quantum.h>
#include <report.h>
#include "binepad_common.h"
#include "caffeine.h"

// needed for rand()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #ifdef CONSOLE_ENABLE
// #include "print.h"
// #endif

#define RGB_MATRIX_MINIMUM_BRIGHTNESS 64

bool     is_caffeine_on        = false; // No Screen Saver
uint32_t timer_caffeine_buffer = 0;     // No Screen Saver timer buffer

#ifdef RGB_MATRIX_ENABLE
uint8_t  caffeine_key_index = UINT8_MAX;
rgb_t    caffeine_color;
uint8_t  caffeine_color_loop    = 0;
bool     is_blink_rgb_on        = false; // Blink LED timer buffer
uint32_t timer_blink_rgb_buffer = 0;     // Blink LED timer buffer
#endif                                   // RGB_MATRIX_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    ifndef CAFFEINE_RGB_BLINK_DELAY
#        define CAFFEINE_RGB_BLINK_DELAY 1000
#    endif // CAFFEINE_RGB_BLINK_DELAY
#endif     // RGB_MATRIX_ENABLE

#ifndef CAFFEINE_KEY_DELAY
#    define CAFFEINE_KEY_DELAY 59000 // 1 sec shy of 1 minute
#endif                               // CAFFEINE_KEY_DELAY

#ifndef CAFFEINE_KEY_CODE
#    define CAFFEINE_KEY_CODE KC_RIGHT_CTRL // Right Control
#endif                                      // CAFFEINE_KEY_CODE

void matrix_scan_caffeine(void) {
    if (is_caffeine_on) {
        /* Keycode and Mouse Jiggle code */

        if (sync_timer_elapsed32(timer_caffeine_buffer) > CAFFEINE_KEY_DELAY) { // default = 59 sec
            timer_caffeine_buffer = sync_timer_read32();                        // reset timer
            // --- tap a key ---
            tap_code(CAFFEINE_KEY_CODE);
        }
    }
}

void housekeeping_task_caffeine(void) {
#ifdef RGB_MATRIX_ENABLE
    // switch off blinking if RGB has been toggled off
    if (is_blink_rgb_on && !rgb_matrix_is_enabled()) {
        is_blink_rgb_on = false;
        if (caffeine_key_index != UINT8_MAX) {
            rgb_matrix_set_color(caffeine_key_index, RGB_OFF);
        }
    }
#endif // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE

static void __caffeine_blink_rgb(void) {
    if (is_caffeine_on && rgb_matrix_is_enabled()) {
        if (sync_timer_elapsed32(timer_blink_rgb_buffer) > CAFFEINE_RGB_BLINK_DELAY) { // every second
            timer_blink_rgb_buffer = sync_timer_read32();                              // reset timer
            is_blink_rgb_on        = !is_blink_rgb_on;
            if (is_blink_rgb_on) {
                HSV hsv;
                hsv.h = caffeine_color_loop * 51;
                hsv.s = 255;
                hsv.v = rgb_matrix_get_val(); // current brightness
                if (hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                if (hsv.v < RGB_MATRIX_MINIMUM_BRIGHTNESS) hsv.v = RGB_MATRIX_MINIMUM_BRIGHTNESS;
                // set the new color
                caffeine_color = hsv_to_rgb(hsv);
                caffeine_color_loop = (caffeine_color_loop + 1) % 6;
            }
        }
    }

    if ((caffeine_key_index != UINT8_MAX) && is_blink_rgb_on) {
        rgb_matrix_set_color(caffeine_key_index, caffeine_color.r, caffeine_color.g, caffeine_color.b);
    }
}

bool rgb_matrix_indicators_caffeine(void) {
    __caffeine_blink_rgb();
    return true;
}

#endif // RGB_MATRIX_ENABLE

// void keyboard_post_init_caffeine(void) {
//     // #ifdef CONSOLE_ENABLE
//     // dprint("f: keyboard_post_init_caffeine");
//     // #endif
// }

// void eeconfig_init_caffeine(void) {
//     // #ifdef CONSOLE_ENABLE
//     // dprint("f: eeconfig_init_caffeine");
//     // #endif
// }

bool caffeine_process_on_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = true;
        tap_code(CAFFEINE_KEY_CODE); // dummy tap the default keycode so that the kb registers a key tap
#ifdef RGB_MATRIX_ENABLE
        caffeine_key_index = g_led_config.matrix_co[record->event.key.row][record->event.key.col]; // bind the key that was pressed
#endif                                                                                             // RGB_MATRIX_ENABLE
        timer_caffeine_buffer = sync_timer_read32();                                               // start the timer
    }
    return false;
}

bool caffeine_process_off_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = false;

#ifdef RGB_MATRIX_ENABLE
        caffeine_key_index = UINT8_MAX;
        is_blink_rgb_on    = false;
#endif // RGB_MATRIX_ENABLE
    }
    return false;
}

bool caffeine_process_toggle_keycode(keyrecord_t *record) {
    // if (!is_caffeine_init) __caffeine_init();
    if (record->event.pressed) {
        is_caffeine_on = !is_caffeine_on;
        if (is_caffeine_on) {
            return caffeine_process_on_keycode(record);
        } else {
            return caffeine_process_off_keycode(record);
        }
    }
    return false;
}
