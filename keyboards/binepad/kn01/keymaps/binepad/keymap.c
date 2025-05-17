/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#ifndef VIAL_PROTOCOL_VERSION
#    error "This keymap is intended for VIAL. Please use VIAL-QMK."
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case USER_SET_KEYCODE_SEND_VERSION: {
            return process_keycode_sr_version(record);
        }
#endif
    }
    return true;
}
