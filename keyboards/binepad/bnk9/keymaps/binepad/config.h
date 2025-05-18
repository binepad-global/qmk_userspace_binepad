// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 38 // needed for custom save to work, calc. from user_config_t
#define VIA_FIRMWARE_VERSION 2           // needed to load next version of via json

#define DYNAMIC_KEYMAP_LAYER_COUNT 9

#define MIDI_ADVANCED // wanted by some customers

/* Community modules */

#define USER_SET_KEYCODE_SEND_VERSION QK_KB_9

#define DOUBLE_TAP_KEY_COUNT 2

// The below overrides the QMK repo keyboard.json sets
#if defined(ENCODER_RESOLUTION) && defined(OS_DETECTION_ENABLE)
#    define ENCODER_RESOLUTION_MACOS 4 // Used by BP_Encoder_Config community module
// #    if ENCODER_RESOLUTION == 4
// #        define ENCODER_DEFAULT_POS 0x3
// #    endif
#endif
