// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

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

// #ifndef COMMUNITY_MODULE_SR_VERSION_ENABLE
// #    error "This build requires COMMUNITY_MODULE_SR_VERSION_ENABLE"
// #endif // COMMUNITY_MODULE_SR_VERSION_ENABLE

// .......... Double Tap ..........

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
// clang-format off
dt_keycodes_t double_tap_keycodes[] = {
    {.kcc = QK_KB_2, .mode = DT_MODE_FUNCTION, .fn1 = process_x1_layer_up, .fn2 = process_x1_layer_down}
};
// clang-format on
#else
#    error "Needs COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE"
#endif

// ========== Process Record ==========

// #ifdef CONSOLE_ENABLE

// uint8_t last_layer = 0xFF;

// void housekeeping_task_user(void) {
//     uint8_t layer = get_highest_layer(layer_state);
//     if (layer != last_layer) {
//         last_layer = layer;
//         uprintf("Layer %d\n", layer);
//     }
// }

// void keyboard_post_init_user(void) {
//     // Customise these values to desired behaviour
//     debug_enable = true;
//     // debug_matrix = true;
//     // debug_keyboard = true;
//     // debug_mouse = true;
// }

// #endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // #ifdef CONSOLE_ENABLE
    //     if (record->event.pressed) {
    //         uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    //     }
    // #endif

    switch (keycode) {
        case QK_KB_0: {
            return process_x1_layer_up(record);
        }
        case QK_KB_1: {
            return process_x1_layer_down(record);
        }

        // QK_KB_2 handled by `process_record_bp_double_tap_lite`

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case USER_SET_KEYCODE_SEND_VERSION: {
            return process_keycode_sr_version(record);
        }
#endif
    }
    return true;
}
