// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "binepad_common.h"

#ifdef VIAL_PROTOCOL_VERSION
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY,
        KC_MPRV, KC_MNXT
    )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    }
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
