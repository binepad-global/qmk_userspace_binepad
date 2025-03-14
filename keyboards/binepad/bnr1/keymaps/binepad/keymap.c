/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#include "binepad_common.h"

#ifndef VIAL_PROTOCOL_VERSION
#    error "This keymap is only intended for VIAL. Please use VIAL-QMK."
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x1(
        LT(1, KC_MUTE)
    ),

    [1] = LAYOUT_ortho_1x1(
        _______
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) }
};
// clang-format on
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // call into binepad_common.c
    if (!process_record_binepad(keycode, record)) {
        return false;
    }
    return true;
}
