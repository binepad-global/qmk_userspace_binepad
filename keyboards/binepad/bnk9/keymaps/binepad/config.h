// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 36 // needed for custom save to work

#define DYNAMIC_KEYMAP_LAYER_COUNT 9

/* The below overrides the QMK repo keyboard.json sets */

#ifdef ENCODER_RESOLUTION
#    undef ENCODER_RESOLUTION  // res at 2 does not work so well on macOS, each click moves by 2
#    define ENCODER_RESOLUTION 4
#endif

#define MIDI_ADVANCED
