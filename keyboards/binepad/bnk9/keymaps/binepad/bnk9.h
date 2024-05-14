// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#    define EEPROM_USER_CONFIG_ADDRESS (VIA_EEPROM_CUSTOM_CONFIG_ADDR + 1)
#endif

#ifdef CAFFEINE_ENABLE

enum bnk9_keyboard {
    KC_SPECIAL_1 = QK_KB_0,
    KC_SPECIAL_2,
    KC_SPECIAL_3,
    KC_SPECIAL_4,
    KC_SPECIAL_5,
    KC_SPECIAL_6,
    KC_SPECIAL_7,
    KC_SPECIAL_8,
    KC_SPECIAL_9,
    KC_SPECIAL_10
};

#    define KC_CAFFEINE_TOGGLE KC_SPECIAL_1

#endif // CAFFEINE_ENABLE

#ifdef VIA_ENABLE // Only works if VIA is enabled

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} HS;

typedef struct {
    HS color[9];
} user_config_t;

extern user_config_t user_config;

#endif // VIA_ENABLE
