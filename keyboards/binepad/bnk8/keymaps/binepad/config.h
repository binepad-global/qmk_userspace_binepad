// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 32 // needed for custom save to work
#define VIA_FIRMWARE_VERSION 2 // needed to load next version of via json

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* Community modules */

#define DOUBLE_TAP_KEY_COUNT 0

/* The below overrides the QMK repo keyboard.json sets */

#ifdef ENCODER_RESOLUTION
#    undef ENCODER_RESOLUTION // res at 2 does not work so well on macOS, each click moves by 2
#    define ENCODER_RESOLUTION 4
#endif

#ifdef RGB_MATRIX_LED_PROCESS_LIMIT
#    undef RGB_MATRIX_LED_PROCESS_LIMIT
#    define RGB_MATRIX_LED_PROCESS_LIMIT 8
#endif

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 // with only 8 LEDs we can go full brightness
#endif
