// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MIDI_ADVANCED

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 18

#define DYNAMIC_KEYMAP_LAYER_COUNT 9

#ifdef OS_DETECTION_ENABLE
    // res at 2 does not work so well on macOS, each click moves by 2
#    define ENCODER_RESOLUTION_MACOS 4
#endif
