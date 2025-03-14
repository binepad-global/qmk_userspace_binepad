// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "binepad_common.h"

#ifdef VIAL_PROTOCOL_VERSION
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 0 │ 1 │ 2 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_0,
        KC_1,
        KC_2
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
