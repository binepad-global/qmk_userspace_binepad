// Copyright 2023 Binepad
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "binepad_common.h"

#ifndef VIAL_PROTOCOL_VERSION
#    error "This keymap is only intended for VIAL. Please use VIAL-QMK."
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 1 │ 2 │ 3 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    )

    // The rest defaults to `_______` for each key
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // call into binepad_common.c
    if (!process_record_binepad(keycode, record)) {
        return false;
    }
    return true;
}
