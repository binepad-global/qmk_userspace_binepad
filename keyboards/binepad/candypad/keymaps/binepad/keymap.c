// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "sr_version.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_9:
            return process_record_sr_version(COMMUNITY_MODULE_SEND_VERSION, record);
            break;
    }
    return true; // For all other keys, use default processing
}
