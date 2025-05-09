// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

#ifdef VIA_ENABLE // Only works if VIA is enabled

// clang-format off
enum via_per_key_value {
    id_custom_color  = 1,
    id_custom_lyrclr = 2

};
// clang-format on

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} hs_t;

typedef union {
    uint8_t raw[16];
    struct {
        hs_t color[8];
        hs_t lyrclr[8];
    };
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
