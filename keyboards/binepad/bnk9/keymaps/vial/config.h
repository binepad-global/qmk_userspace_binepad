// Copyright 2025 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0xB1, 0x0B, 0x35, 0xC4, 0xAF, 0x17, 0x09, 0x02}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 9

#define MIDI_ADVANCED

/* The below overrides the QMK repo keyboard.json sets */

// #ifdef ENCODER_RESOLUTION
// #    undef ENCODER_RESOLUTION  // res at 2 does not work so well on macOS, each click moves by 2
// #    define ENCODER_RESOLUTION 4
// #endif
