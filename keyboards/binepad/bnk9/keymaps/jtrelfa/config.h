// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 38 // needed for custom save to work, calc. from user_config_t
#define VIA_FIRMWARE_VERSION 2           // needed to load next version of via json

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#define MIDI_ADVANCED // wanted by some customers


#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SPLASH

/* Community modules */

//Pomodoro Timer
#define POM_WORK_MINUTES 50
#define POM_REST_MINUTES 10
#define POM_PREPARE_COLOR RGB_YELLOW
#define POM_WORKING_COLOR RGB_GREEN
#define POM_DONE_WORKING_COLOR RGB_RED
#define POM_RESTING_COLOR RGB_BLUE
