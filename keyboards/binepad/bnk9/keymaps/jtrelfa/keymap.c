// Copyright 2025 Jon Trelfa (@jtrelfa)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "bnk9_user.h"

bool rgb_matrix_indicators_user(void) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
