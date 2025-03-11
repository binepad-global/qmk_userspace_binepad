// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

// clang-format off
enum bnk9_keyboard {
    #ifdef CAFFEINE_ENABLE
    KC_CAFFEINE_TOGGLE = QK_KB_0
    #endif // CAFFEINE_ENABLE
};
// clang-format on

#ifdef CAFFEINE_ENABLE
#    define KC_COFFEE KC_CAFFEINE_TOGGLE
#endif // CAFFEINE_ENABLE

#ifdef VIA_ENABLE // Only works if VIA is enabled

// clang-format off
enum via_per_key_value {
    id_custom_color = 1
};
// clang-format on


typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} HS;

typedef union {
    uint8_t raw[18];
    struct {
        HS color[9];
    };
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
