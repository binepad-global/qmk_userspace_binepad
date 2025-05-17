// Copyright 2024 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

#ifdef VIA_ENABLE // Only works if VIA is enabled

#    if !defined(VIA_EEPROM_CUSTOM_CONFIG_SIZE) || VIA_EEPROM_CUSTOM_CONFIG_SIZE != 34
#        error "Please set VIA_EEPROM_CUSTOM_CONFIG_SIZE to 34 in config.h"
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
    B8_CAFFEINE_TOGGLE = QK_KB_0,
    B8_MUTE_PLAY_DOUBLE,    // 1
    B8_LAYER_JUMP,          // 2
    B8_LAYER_UP,            // 3
    B8_LAYER_DOWN,          // 4
    B8_LAYER_PRINT,         // 5
    B8_CAFFEINE_ON,         // 6
    B8_CAFFEINE_OFF,        // 7
    B8__SPARE__8,           // 8
    // USER_SET_KEYCODE_SEND_VERSION
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
            bool l0_off : 1;
        };
    };
    uint8_t enc_res;
} user_config_t;

extern user_config_t g_user_config;

#endif // VIA_ENABLE
