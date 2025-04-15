// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 16 // needed for custom save to work

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* The below overrides the QMK repo keyboard.json sets */

#ifdef OS_DETECTION_ENABLE
    // res at 2 does not work so well on macOS, each click moves by 2
#    define ENCODER_RESOLUTION_MACOS 4
#endif

#ifdef RGB_MATRIX_LED_PROCESS_LIMIT
#    undef RGB_MATRIX_LED_PROCESS_LIMIT
#    define RGB_MATRIX_LED_PROCESS_LIMIT 8
#endif
