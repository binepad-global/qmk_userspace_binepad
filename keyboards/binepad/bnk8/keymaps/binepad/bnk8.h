// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

#ifdef VIA_ENABLE // Only works if VIA is enabled

#if !defined(VIA_EEPROM_CUSTOM_CONFIG_SIZE) || VIA_EEPROM_CUSTOM_CONFIG_SIZE != 34
#    error "Please set VIA_EEPROM_CUSTOM_CONFIG_SIZE to 34 in config.h"
#endif

// clang-format off

enum via_per_key_value {
    id_custom_color = 1,
    id_custom_lyrclr,      // 2
    id_custom_lyr0on,      // 3
    id_encoder_resolution, // 4
    id_firmware_button     // 5
};

enum via_id_firmware_button {
    id_buton_ignore = 0,
    id_button_bootloader,   // 1
    id_button_reboot,       // 2
    id_button_debug_toggle, // 3
    id_button_clear_eeprom  // 4
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
    union {
        uint8_t flags;
        struct {
            bool lyr0on : 1;
        };
    };
    uint8_t enc_res;
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
