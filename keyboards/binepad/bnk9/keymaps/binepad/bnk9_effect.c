// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#if defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS) && defined(VIA_ENABLE) // Only works if VIA is enabled

#    include "color.h"
#    include "progmem.h"
#    include "eeprom.h"
#    include "via.h"
#    include "bnk9.h"

// clang-format off

#    define RGB_PER_KEY_DEFAULT_COLOR \
        { .h = RGB_MATRIX_DEFAULT_HUE, \
          .s = RGB_MATRIX_DEFAULT_SAT }

#    define BNK9_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

user_config_t g_user_config = {
    .color = {
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR,
        RGB_PER_KEY_DEFAULT_COLOR
    } };

enum via_per_key_value {
    id_custom_color = 1
};

// clang-format on

// *** Helpers ***

void bnk9_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_custom_color: {
            uint8_t i                = value_data[0];
            g_user_config.color[i].h = value_data[1];
            g_user_config.color[i].s = value_data[2];
            break;
        }
    }
}

void bnk9_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_custom_color: {
            uint8_t i     = value_data[0];
            value_data[1] = g_user_config.color[i].h;
            value_data[2] = g_user_config.color[i].s;
            break;
        }
    }
}

void bnk9_config_load(void) {
    // clang-format off
    eeprom_read_block( &g_user_config,
        ((void*)BNK9_CONFIG_EEPROM_ADDR),
        sizeof(user_config_t));
    // clang-format on
}

void bnk9_config_save(void) {
    // clang-format off
    eeprom_update_block( &g_user_config,
        ((void*)BNK9_CONFIG_EEPROM_ADDR),
        sizeof(user_config_t));
    // clang-format on
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                bnk9_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                bnk9_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                bnk9_config_save();
                break;
            default:
                // Unhandled message.
                *command_id = id_unhandled;
                break;
        }
        return;
    }

    *command_id = id_unhandled;
}

void via_init_kb(void) {
    // This checks both an EEPROM reset (from bootmagic lite, keycodes)
    // and also firmware build date (from via_eeprom_is_valid())
    if (eeconfig_is_enabled()) {
        bnk9_config_load();
    } else {
        bnk9_config_save();
    }
}

#else
#    error "This does not work without RGB_MATRIX_CUSTOM_KB & VIA_ENABLE"
#endif // VIA_ENABLE
