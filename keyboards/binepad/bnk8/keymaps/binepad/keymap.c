// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// #include "binepad_common.h"
#include "bnk8.h"
#include "caffeine.h"

#ifdef VIAL_PROTOCOL_VERSION
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
// #    error CONSOLE_ENABLE is ON!
#endif

#ifdef COMMUNITY_MODULE_CAFFEINE_ENABLE
#    include "caffeine.h"
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

#if defined(COMMUNITY_MODULE_CAFFEINE_ENABLE) && defined(COMMUNITY_MODULE_SILVINOR_CAFFEINE_ENABLE)

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_indicators_caffeine()) return false;
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_caffeine();
}

// !! : Not needed when used as a module
// void housekeeping_task_user(void) {
//     housekeeping_task_caffeine();
// }

#else
#    error "This build requires COMMUNITY_MODULE_SILVINOR_CAFFEINE_ENABLE"
#endif // All the optionals

/* !! : Only needed when debugging
void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
    #endif
}
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef COMMUNITY_MODULE_CAFFEINE_ENABLE
        // !! : no, it's not duplication, this is for VIA keymaps
        case KC_CAFFEINE_TOGGLE:
            return process_keycode_caffeine_toggle(record);
            break;
#endif

#ifdef COMMUNITY_MODULE_GLOBE_KEY_ENABLE
        case KC_APPLE_GLOBE:
            return process_record_globe_key(KC_GLOBE, record);
            break;
#endif

#ifdef COMMUNITY_MODULE_VERSION_ENABLE
        case KC_PRINT_VERSION:
            return process_record_version(COMMUNITY_MODULE_SEND_VERSION, record);
            break;
#endif
    }
    return true;
}
