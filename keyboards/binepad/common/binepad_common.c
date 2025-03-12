// Copyright 2023 Silvino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "report.h"
#include "binepad_common.h"

#include "color.h"
#include "version.h"

#if defined(RGB_MATRIX_ENABLE) || defined(RGB_LIGHT_ENABLE)
RGB adjust_to_brightness(uint8_t r, uint8_t g, uint8_t b, uint8_t min, uint8_t max) {
    RGB ret = {r : 0, g : 0, b : 0};

#    ifdef RGB_MATRIX_ENABLE
    uint8_t brightness = rgb_matrix_get_val();
#    endif
#    ifdef RGB_LIGHT_ENABLE
    uint8_t brightness = rgblight_get_val();
#    endif
    if (brightness > max) brightness = max;
    if (brightness < min) brightness = min;

    ret.r = (uint16_t)(r * (brightness / 255));
    ret.g = (uint16_t)(g * (brightness / 255));
    ret.b = (uint16_t)(b * (brightness / 255));

    return ret;
}
#endif

bool process_record_binepad(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_9: // `CUSTOM(9)` in VIA app
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " [" QMK_BUILDDATE "]");
            }
            return false;
            break;

#ifdef RGB_MATRIX_ENABLE
        case QK_CLEAR_EEPROM:
            if (record->event.pressed) {
                if (!rgb_matrix_is_enabled()) {
                    rgb_matrix_enable();
                }
                rgb_matrix_set_color_all(RGB_YELLOW);
                rgb_matrix_update_pwm_buffers();
                wait_ms(500); // 1/2 sec
            }
            return true; // let QMK do the rest
            break;

        case QK_BOOT:
            if (record->event.pressed) {
                if (!rgb_matrix_is_enabled()) {
                    rgb_matrix_enable();
                }
                rgb_matrix_set_color_all(RGB_RED);
                rgb_matrix_update_pwm_buffers();
                wait_ms(500); // 1/2 sec
            }
            return true; // let QMK do the rest
            break;
#endif

        default:
            return true; // Process all other keycodes normally
    }
}

// uint16_t find_key_index(uint16_t target_keycode) {
//     if (target_keycode == KC_NO) return UINT16_MAX;

//     for (int row = 0; row < MATRIX_ROWS; ++row) {
//         for (int col = 0; col < MATRIX_COLS; ++col) {
//             // TODO: This looks at layer 0 ... what if it's on another layer?
//             uint16_t ret = keymap_key_to_keycode(0, (keypos_t){ .row = row, .col = col });
//             if (ret == target_keycode) {
//                 return ret;
//             }
//         }
//     }

//     // not found
//     return UINT16_MAX;
// }
