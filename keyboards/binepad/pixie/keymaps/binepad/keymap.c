// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(VIAL_PROTOCOL_VERSION) || defined(BUILD_ID)
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'R', 'R',
    'R', 'R'
);
// clang-format on
#endif

#ifndef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    error "This build requires COMMUNITY_MODULE_SR_VERSION_ENABLE"
#endif // COMMUNITY_MODULE_SR_VERSION_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case USER_SET_KEYCODE_SEND_VERSION: {
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
