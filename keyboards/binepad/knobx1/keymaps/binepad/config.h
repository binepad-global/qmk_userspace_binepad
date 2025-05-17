// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* QMK Settings */

// #define DYNAMIC_KEYMAP_LAYER_COUNT 4 // 4 is default

#define MIDI_ADVANCED

/* Vile {yes, the adjective :) } */

#define VIAL_KEYBOARD_UID {0xD4, 0x53, 0xBC, 0x59, 0x4B, 0x30, 0x22, 0xFA}

// 0,1 is the knob, as the button is hidden
#define VIAL_UNLOCK_COMBO_ROWS {0}
#define VIAL_UNLOCK_COMBO_COLS {1}

/* Community modules */

#define USER_SET_KEYCODE_SEND_VERSION QK_KB_9

#define DOUBLE_TAP_TERM 250
#define DOUBLE_TAP_KEY_COUNT 1

#ifdef OS_DETECTION_ENABLE
#    define ENCODER_RESOLUTION_MACOS 4 // Used by BP_Encoder_Config community module
#endif
