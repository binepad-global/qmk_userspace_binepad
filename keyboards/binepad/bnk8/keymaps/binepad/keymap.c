// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "binepad_common.h"
#include "bnk8.h"

#ifdef CAFFEINE_ENABLE
#    include "caffeine.h"
#endif // CAFFEINE_ENABLE

#ifdef CONSOLE_ENABLE
#    include "print.h"
// #    error CONSOLE_ENABLE is ON!
#endif

#ifdef CAFFEINE_ENABLE
#    define COFFEE KC_CAFFEINE_TOGGLE
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 1 │ 2 │(K)│
     * ├───┼───┼───┤
     * │ 3 │ 4 │ 5 │
     * ├───┼───┼───┤
     * │ 6 │ 7 │ 8 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_P1,    KC_P2,    KC_MUTE,
        KC_P3,    KC_P4,    KC_P5,
        KC_P6,    KC_P7,    LT(1, KC_P8)
    ),
    [1] = LAYOUT_ortho_3x3(
        // RM_HUEU, RM_SATU, RM_SPDU,
        // RM_HUED, RM_SATD, RM_SPDD,
        // RM_TOGG, RM_NEXT, _______
        RGB_HUI, RGB_SAI, RGB_SPI,
        RGB_HUD, RGB_SAD, RGB_SPD,
        RGB_TOG, RGB_MOD, _______
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE

// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    // [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
    [1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
// clang-format on

#endif // ENCODER_MAP_ENABLE

// ---------- Optional Add-ons -----------

#if defined(CAFFEINE_ENABLE) // && && &&  ... All the optionals

#    ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
#        ifdef CAFFEINE_ENABLE
    if (!rgb_matrix_indicators_caffeine()) return false;
#        endif
    return true;
}

#    endif // RGB_MATRIX_ENABLE

// void keyboard_post_init_user(void) {

//     // #ifdef CONSOLE_ENABLE
//     // // Customise these values to desired behaviour
//     // debug_enable = true;
//     // // debug_matrix = true;
//     // // debug_keyboard=true;
//     // // debug_mouse=true;
//     // #endif
// }

// void eeconfig_init_user(void) {
// }

void matrix_scan_user(void) {
#    ifdef CAFFEINE_ENABLE
    matrix_scan_caffeine();
#    endif
}

void housekeeping_task_user(void) {
#    ifdef CAFFEINE_ENABLE
    housekeeping_task_caffeine();
#    endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // #ifdef CONSOLE_ENABLE
    // dprintf("kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    // #endif

    switch (keycode) {
        case KC_LAYER_SELECTOR:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                uint8_t next_layer    = current_layer + 1;
                if (next_layer >= DYNAMIC_KEYMAP_LAYER_COUNT) {
                    next_layer = 0;
                }
                layer_move(next_layer);
            }
            return false;

#    ifdef CAFFEINE_ENABLE
        case KC_CAFFEINE_TOGGLE:
            return caffeine_process_toggle_keycode(record);
            break;
#    endif

        default:
            break;
    }

    if (!process_record_binepad(keycode, record)) {
        return false;
    }

    return true;
}

#endif // All the optionals
