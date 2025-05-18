// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "bnk9_user.h"

#if defined(VIAL_PROTOCOL_VERSION) || defined(BUILD_ID)
#    error "This keymap is not intended for VIAL. Please use QMK."
#endif

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
#    include "sr_caffeine.h"
#endif

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    include "sr_version.h"
#endif

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
#    include "bp_double_tap_lite.h"
#endif

// ---------- Layer Buttons -----------

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#    define BNK9_KEYMAP_LAYER_COUNT DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define BNK9_KEYMAP_LAYER_COUNT 4
#endif

bool process_bnk9_layer_up(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        uint8_t next_layer    = (current_layer + 1) % BNK9_KEYMAP_LAYER_COUNT;
        layer_move(next_layer);
    }
    return false;
}

bool process_bnk9_layer_down(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        uint8_t prev_layer    = (current_layer == 0) ? (BNK9_KEYMAP_LAYER_COUNT - 1) : (current_layer - 1);
        layer_move(prev_layer);
    }
    return false;
}

// ---------- Optional Add-ons -----------

// .......... Caffeine ..........

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_indicators_sr_caffeine()) return false;
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_sr_caffeine();
}

#endif // COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

// .......... Double Tap ..........

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
// clang-format off
dt_keycodes_t double_tap_keycodes[] = {
    {.kcc = B9_MUTE_PLAY_DOUBLE, .mode = DT_MODE_KEYCODE,  .kc1 = KC_MUTE,               .kc2 = KC_MPLY},
    {.kcc = B9_LAYER_JUMP,       .mode = DT_MODE_FUNCTION, .fn1 = process_bnk9_layer_up, .fn2 = process_bnk9_layer_down}
};
// clang-format on
#endif

// ---------- RGB Matrix ----------

bool get_leds_is_on(void) {
    return rgb_matrix_get_flags() != LED_FLAG_NONE;
}

bool set_leds_on(keyrecord_t *record) {
    if (record->event.pressed) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_enable_noeeprom();
    }
    return false;
}

bool set_leds_off(keyrecord_t *record) {
    if (record->event.pressed) {
        rgb_matrix_set_flags(LED_FLAG_NONE);
        rgb_matrix_set_color_all(0, 0, 0);
    }
    return false;
}

// ========== Process Record ==========

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_TOGG: {
            if (record->event.pressed) {
                if (get_leds_is_on()) {
                    return set_leds_off(record);
                } else {
                    return set_leds_on(record);
                }
            }
            return false;
        }

        case RM_ON: {
            return set_leds_on(record);
        }

        case RM_OFF: {
            return set_leds_off(record);
        }

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
        // !! : no, it's not duplication, this is for VIA keymaps
        case B9_CAFFEINE_TOGGLE: {
            return process_keycode_sr_caffeine_toggle(record);
        }

            // `B9_MUTE_PLAY_DOUBLE` & `B9_LAYER_JUMP` are handled by `process_record_bp_double_tap_lite`

        case B9_LAYER_UP: {
            return process_bnk9_layer_up(record);
        }

        case B9_LAYER_DOWN: {
            // Layer down
            return process_bnk9_layer_down(record);
        }

        case B9_LAYER_PRINT: {
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                char    layer_str[4];
                snprintf(layer_str, sizeof(layer_str), "%d", current_layer);
                SEND_STRING(layer_str);
            }
            return false;
        }

        case B9_CAFFEINE_ON: {
            return process_keycode_sr_caffeine_on(record);
        }

        case B9_CAFFEINE_OFF: {
            return process_keycode_sr_caffeine_off(record);
        }
#endif // COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

#ifdef COMMUNITY_MODULE_SR_VERSION_ENABLE
        case USER_SET_KEYCODE_SEND_VERSION: {
            return process_keycode_sr_version(record);
        }
#endif // COMMUNITY_MODULE_SR_VERSION_ENABLE
    }
    return true;
}
