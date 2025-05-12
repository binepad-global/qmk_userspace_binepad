// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "bnk8_user.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

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

// ---------- Technicaly not needed, but good to optimise ----------

#ifdef MATRIX_MASKED
// clang-format off
const matrix_row_t matrix_mask[] = {
    0b110,
    0b111,
    0b111,
};
// clang-format on
#endif

#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_ortho_3x3(
    'R', 'R', 'R',
    'R', 'R', 'R',
    'R', 'R', 'R'
);
// clang-format on
#endif

// ---------- Debug ----------

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    /* Customise these values to desired behaviour */
    debug_enable = true; // Enables debug prints
    // debug_matrix = true;          // Shows matrix changes
    // debug_keyboard = true; // Shows keyboard-level events
    // debug_mouse = true;           // Shows mouse-level events
}
#endif

// ---------- Layer Buttons -----------

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#    define BNK8_KEYMAP_LAYER_COUNT DYNAMIC_KEYMAP_LAYER_COUNT
#else
#    define BNK8_KEYMAP_LAYER_COUNT 4
#endif

bool process_bnk8_layer_up(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        uint8_t next_layer    = (current_layer + 1) % BNK8_KEYMAP_LAYER_COUNT;
        layer_move(next_layer);
    }
    return false;
}

bool process_bnk8_layer_down(keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t current_layer = get_highest_layer(layer_state);
        uint8_t prev_layer    = (current_layer == 0) ? (BNK8_KEYMAP_LAYER_COUNT - 1) : (current_layer - 1);
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

#else
#    error "This build requires COMMUNITY_MODULE_SR_CAFFEINE_ENABLE"
#endif // COMMUNITY_MODULE_SR_CAFFEINE_ENABLE

// .......... Version ..........

#ifndef COMMUNITY_MODULE_SR_VERSION_ENABLE
#    error "This build requires COMMUNITY_MODULE_SR_VERSION_ENABLE"
#endif // COMMUNITY_MODULE_SR_VERSION_ENABLE

// .......... Double Tap ..........

#ifdef COMMUNITY_MODULE_BP_DOUBLE_TAP_LITE_ENABLE
// clang-format off
dt_keycodes_t double_tap_keycodes[] = {
    {.kcc = QK_KB_1, .mode = DT_MODE_KEYCODE, .kc1 = KC_MUTE, .kc2 = KC_MPLY},
    {.kcc = QK_KB_2, .mode = DT_MODE_FUNCTION, .fn1 = process_bnk8_layer_up, .fn2 = process_bnk8_layer_down}
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
    // #ifdef CONSOLE_ENABLE
    //     uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    // #endif

    switch (keycode) {
        case RM_TOGG: {
#ifdef CONSOLE_ENABLE
            print("RM_TOGG\n");
#endif
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
#ifdef CONSOLE_ENABLE
            print("RM_ON\n");
#endif
            return set_leds_on(record);
        }

        case RM_OFF: {
#ifdef CONSOLE_ENABLE
            print("RM_OFF\n");
#endif
            return set_leds_off(record);
        }

#ifdef COMMUNITY_MODULE_SR_CAFFEINE_ENABLE
        // !! : no, it's not duplication, this is for VIA keymaps
        case B8_CAFFEINE_TOGGLE: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_toggle\n");
#    endif
            return process_keycode_sr_caffeine_toggle(record);
        }

            // `B8_MUTE_PLAY_DOUBLE` & `B8_LAYER_JUMP` are handled by `process_record_bp_double_tap_lite`

        case B8_LAYER_UP: {
            return process_bnk8_layer_up(record);
        }

        case B8_LAYER_DOWN: {
            // Layer down
            return process_bnk8_layer_down(record);
        }

        case B8_LAYER_PRINT: {
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                char    layer_str[4];
                snprintf(layer_str, sizeof(layer_str), "%d", current_layer);
                SEND_STRING(layer_str);
            }
            return false;
        }

        case B8_CAFFEINE_ON: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_on\n");
#    endif
            return process_keycode_sr_caffeine_on(record);
        }

        case B8_CAFFEINE_OFF: {
#    ifdef CONSOLE_ENABLE
            print("caffeine_off\n");
#    endif
            return process_keycode_sr_caffeine_off(record);
        }
#else
#    error "!!"
#endif

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
