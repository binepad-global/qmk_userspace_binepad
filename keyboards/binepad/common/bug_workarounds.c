// Copyright 2023 Silvino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "bug_workarounds.h"

// VIA does not support the new Separate RGBLight/RGB Matrix keycode handling
// (#23679)[https://github.com/qmk/qmk_firmware/pull/23679]
// This maps the old keys to the new ones, so that you can set them in VIA and still work here

typedef struct {
    unsigned int old_value;
    unsigned int new_value;
} tLegacyKeycodeMap;

#define LEGACY_KEYCODE_MAP_SIZE 25

// Define an array of RGB keycode mappings
tLegacyKeycodeMap legacyKeycodeMap[LEGACY_KEYCODE_MAP_SIZE] = {
    // backlight
    {QK_BACKLIGHT_ON, QK_RGB_MATRIX_ON},
    {QK_BACKLIGHT_OFF, QK_RGB_MATRIX_OFF},
    {QK_BACKLIGHT_TOGGLE, QK_RGB_MATRIX_TOGGLE},
    {QK_BACKLIGHT_DOWN, QK_RGB_MATRIX_VALUE_UP},
    {QK_BACKLIGHT_UP, QK_RGB_MATRIX_VALUE_DOWN},
    // LED matrix
    {QK_LED_MATRIX_ON, QK_RGB_MATRIX_ON},
    {QK_LED_MATRIX_OFF, QK_RGB_MATRIX_OFF},
    {QK_LED_MATRIX_TOGGLE, QK_RGB_MATRIX_TOGGLE},
    {QK_LED_MATRIX_MODE_NEXT, QK_RGB_MATRIX_MODE_NEXT},
    {QK_LED_MATRIX_MODE_PREVIOUS, QK_RGB_MATRIX_MODE_PREVIOUS},
    {QK_LED_MATRIX_BRIGHTNESS_UP, QK_RGB_MATRIX_VALUE_UP},
    {QK_LED_MATRIX_BRIGHTNESS_DOWN, QK_RGB_MATRIX_VALUE_DOWN},
    {QK_LED_MATRIX_SPEED_UP, QK_RGB_MATRIX_SPEED_UP},
    {QK_LED_MATRIX_SPEED_DOWN, QK_RGB_MATRIX_SPEED_DOWN},
    // RGB Underglow
    {QK_UNDERGLOW_TOGGLE, QK_RGB_MATRIX_TOGGLE},
    {QK_UNDERGLOW_MODE_NEXT, QK_RGB_MATRIX_MODE_NEXT},
    {QK_UNDERGLOW_MODE_PREVIOUS, QK_RGB_MATRIX_MODE_PREVIOUS},
    {QK_UNDERGLOW_HUE_UP, QK_RGB_MATRIX_HUE_UP},
    {QK_UNDERGLOW_HUE_DOWN, QK_RGB_MATRIX_HUE_DOWN},
    {QK_UNDERGLOW_SATURATION_UP, QK_RGB_MATRIX_SATURATION_UP},
    {QK_UNDERGLOW_SATURATION_DOWN, QK_RGB_MATRIX_SATURATION_DOWN},
    {QK_UNDERGLOW_VALUE_UP, QK_RGB_MATRIX_VALUE_UP},
    {QK_UNDERGLOW_VALUE_DOWN, QK_RGB_MATRIX_VALUE_DOWN},
    {QK_UNDERGLOW_SPEED_UP, QK_RGB_MATRIX_SPEED_UP},
    {QK_UNDERGLOW_SPEED_DOWN, QK_RGB_MATRIX_SPEED_DOWN}};

// Function to find a mapped value
uint16_t find_legacy_keycode(uint16_t old_val) {
    for (int i = 0; i < LEGACY_KEYCODE_MAP_SIZE; i++) {
        if (legacyKeycodeMap[i].old_value == old_val) {
            return legacyKeycodeMap[i].new_value;
        }
    }
    return old_val; // Return old value if not found
}

bool process_record_bugfixes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_BACKLIGHT_ON:
        case QK_BACKLIGHT_OFF:
        case QK_BACKLIGHT_TOGGLE:
        case QK_BACKLIGHT_DOWN:
        case QK_BACKLIGHT_UP:
        case QK_LED_MATRIX_ON:
        case QK_LED_MATRIX_OFF:
        case QK_LED_MATRIX_TOGGLE:
        case QK_LED_MATRIX_MODE_NEXT:
        case QK_LED_MATRIX_MODE_PREVIOUS:
        case QK_LED_MATRIX_BRIGHTNESS_UP:
        case QK_LED_MATRIX_BRIGHTNESS_DOWN:
        case QK_LED_MATRIX_SPEED_UP:
        case QK_LED_MATRIX_SPEED_DOWN:
        case QK_UNDERGLOW_TOGGLE:
        case QK_UNDERGLOW_MODE_NEXT:
        case QK_UNDERGLOW_MODE_PREVIOUS:
        case QK_UNDERGLOW_HUE_UP:
        case QK_UNDERGLOW_HUE_DOWN:
        case QK_UNDERGLOW_SATURATION_UP:
        case QK_UNDERGLOW_SATURATION_DOWN:
        case QK_UNDERGLOW_VALUE_UP:
        case QK_UNDERGLOW_VALUE_DOWN:
        case QK_UNDERGLOW_SPEED_UP:
        case QK_UNDERGLOW_SPEED_DOWN:
            keycode = find_legacy_keycode(keycode);
            if (record->event.pressed) {
                register_code(keycode);
            } else {
                unregister_code(keycode);
            }
            return false; // Skip all further processing of this key

        default:
            return true; // Process all other keycodes normally
    }
}
