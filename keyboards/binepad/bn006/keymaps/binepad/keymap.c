/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#include "binepad_common.h"

#ifndef VIAL_PROTOCOL_VERSION
#    error "This keymap is only intended for VIAL. Please use VIAL-QMK."
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_MPLY, KC_MUTE, KC_VOLU,
        KC_MPRV, KC_MNXT, KC_VOLD
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
