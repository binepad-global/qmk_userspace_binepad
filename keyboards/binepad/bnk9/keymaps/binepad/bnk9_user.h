// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"

#    if !defined(VIA_EEPROM_CUSTOM_CONFIG_SIZE) || VIA_EEPROM_CUSTOM_CONFIG_SIZE != 38
#        error "Please set VIA_EEPROM_CUSTOM_CONFIG_SIZE to 38 in config.h"
#    endif

// clang-format off

enum via_per_key_value {
    id_custom_color = 1,
    id_custom_lyrclr,      // 2
    id_custom_l0_off,      // 3
    id_encoder_resolution, // 4
    id_firmware_button = 99
};

enum via_id_firmware_button {
    id_buton_ignore = 0,
    id_button_bootloader,   // 1
    id_button_reboot,       // 2
    id_button_debug_toggle, // 3
    id_button_clear_eeprom  // 4
};

enum custom_keycodes {
    B9_CAFFEINE_TOGGLE = QK_KB_0,
    B9_MUTE_PLAY_DOUBLE,    // 1
    B9_LAYER_JUMP,          // 2
    B9_LAYER_UP,            // 3
    B9_LAYER_DOWN,          // 4
    B9_LAYER_PRINT,         // 5
    B9_CAFFEINE_ON,         // 6
    B9_CAFFEINE_OFF,        // 7
    B9__SPARE__8,           // 8
    // USER_SET_KEYCODE_SEND_VERSION
};

// clang-format on

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
} hs_t;

typedef union {
    uint8_t raw[36]; // 36
    struct {
        hs_t color[9];
        hs_t lyrclr[9];
    };
    union {
        uint8_t flags; // 1
        struct {
            bool l0_off : 1;
        };
    };
    uint8_t enc_res; // 1
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
