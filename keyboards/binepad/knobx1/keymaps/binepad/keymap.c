// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "knobx1_user.h"

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

#ifdef COMMUNITY_MODULE_BP_ENCODER_CONFIGURABLE_ENABLE
#    include "bp_encoder_configurable.h"
#endif

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
#    include "knobx1.h"
#    include "bp_double_tap_lite.h"
#endif

// ---------- Optional Add-ons -----------

// .......... Version ..........

#ifndef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    error "This build requires COMMUNITY_MODULE_SR_VERSION_ENABLE"
#endif // COMMUNITY_MODULE_SR_VERSION_ENABLE

// .......... Double Tap ..........

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
// clang-format off
dt_keycodes_t double_tap_keycodes[] = {
    {.kcc = X1_LAYER_JUMP, .mode = DT_MODE_FUNCTION, .fn1 = process_x1_layer_up, .fn2 = process_x1_layer_down}
};
// clang-format on
#else
#    error "Needs COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE"
#endif

// ========== Process Record ==========

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case X1_LAYER_UP: {
            return process_x1_layer_up(record);
        }
        case X1_LAYER_DOWN: {
            return process_x1_layer_down(record);
        }

        // X1_LAYER_JUMP handled by `process_record_bp_double_tap_lite`

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case USER_SET_KEYCODE_SEND_VERSION: {
            return process_keycode_sr_version(record);
        }
#endif
    }
    return true;
}
