// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x1B, 0x53, 0xBF, 0xA3, 0x2E, 0x38, 0x7E, 0xBC}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* The below overrides the QMK repo keyboard.json sets */

// #ifdef ENCODER_RESOLUTION
// #    undef ENCODER_RESOLUTION // res at 2 does not work so well on macOS, each click moves by 2
// #    define ENCODER_RESOLUTION 4
// #endif
