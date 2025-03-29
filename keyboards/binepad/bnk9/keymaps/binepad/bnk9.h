// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

// clang-format off
enum bnk9_keyboard {
    #ifdef COMMUNITY_MODULE_CAFFEINE_ENABLE
    KC_CAFFEINE_TOGGLE = QK_KB_0,
    #endif // COMMUNITY_MODULE_CAFFEINE_ENABLE
    KC_LAYER_SELECTOR = QK_KB_1,
    #ifdef COMMUNITY_MODULE_VERSION_ENABLE
    KC_PRINT_VERSION = QK_KB_9,
    #endif // COMMUNITY_MODULE_VERSION_ENABLE
};
// clang-format on

#define KC_LAYR KC_LAYER_SELECTOR
#ifdef COMMUNITY_MODULE_CAFFEINE_ENABLE
#    define KC_COFY KC_CAFFEINE_TOGGLE
#endif // COMMUNITY_MODULE_CAFFEINE_ENABLE

#ifdef VIA_ENABLE // Only works if VIA is enabled

// clang-format off
enum via_per_key_value {
    id_custom_color = 1,
    id_custom_lyrclr = 2,
};
// clang-format on

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} HS;

typedef union {
    uint8_t raw[36];
    struct {
        HS color[9];
        HS lyrclr[9];
    };
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
