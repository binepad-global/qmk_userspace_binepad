// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "bnk8.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#ifdef VIAL_PROTOCOL_VERSION
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
#    include "sr_caffeine.h"
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

#ifdef CONSOLE_ENABLE
void matrix_init_user(void) {
    debug_enable = true; // Enables debug prints
    // debug_matrix = true;          // Shows matrix changes
    debug_keyboard = true; // Shows keyboard-level events
    // debug_mouse = true;           // Shows mouse-level events
}
#endif

// ---------- Technicaly not needed, but good to optimise ----------

#ifdef MATRIX_MASKED
// clang-format off
const matrix_row_t matrix_mask[] = {
    0b110,
    0b111,
    0b111,
};
// clang-format on
#endif

#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_ortho_3x3(
    'R', 'R', 'R',
    'R', 'R', 'R',
    'R', 'R', 'R'
);
// clang-format on
#endif

// ---------- Optional Add-ons -----------

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_indicators_sr_caffeine()) return false;
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_sr_caffeine();
}

// !! : Not needed when used as a module
// void housekeeping_task_user(void) {
//     housekeeping_task_sr_caffeine();
// }

#else
#    error "This build requires COMMUNITY_MODULE_SR_CAFFEINE_ENABLE"
#endif // COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

#ifndef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    error "This build requires COMMUNITY_MODULE_SR_VERSION_ENABLE"
#endif // COMMUNITY_MODULE_SR_VERSION_ENABLE

bool get_leds_is_on(void) {
    return rgb_matrix_get_flags() != LED_FLAG_NONE;
}

bool set_leds_on(keyrecord_t *record) {
    if (record->event.pressed) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_enable_noeeprom();
    }
    return false;
}

bool set_leds_off(keyrecord_t *record) {
    if (record->event.pressed) {
        rgb_matrix_set_flags(LED_FLAG_NONE);
        rgb_matrix_set_color_all(0, 0, 0);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
        case RM_TOGG: {
#    ifdef CONSOLE_ENABLE
            print("RM_TOGG\n");
#    endif
            if (record->event.pressed) {
                if (get_leds_is_on()) {
                    return set_leds_off(record);
                } else {
                    return set_leds_on(record);
                }
            }
            return false;
        }

        case RM_ON: {
#    ifdef CONSOLE_ENABLE
            print("RM_ON\n");
#    endif
            return set_leds_on(record);
        }

        case RM_OFF: {
#    ifdef CONSOLE_ENABLE
            print("RM_OFF\n");
#    endif
            return set_leds_off(record);
        }

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
        // !! : no, it's not duplication, this is for VIA keymaps
        case QK_KB_0: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_toggle\n");
#    endif
            return process_keycode_sr_caffeine_toggle(record);
        }

        case QK_KB_1: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_on\n");
#    endif
            return process_keycode_sr_caffeine_on(record);
        }

        case QK_KB_2: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_off\n");
#    endif
            return process_keycode_sr_caffeine_off(record);
        }
#else
#    error "!!"
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case QK_KB_9: {
#    ifdef CONSOLE_ENABLE
            print("VERSION\n");
#    endif
            return process_keycode_sr_version(record);
        }
#else
#    error "!!"
#endif
    }
    return true;
}
