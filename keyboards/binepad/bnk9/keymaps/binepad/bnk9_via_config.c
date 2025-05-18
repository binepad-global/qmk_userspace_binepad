// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// Only works if VIA is enabled
#if defined(RGB_MATRIX_CUSTOM_KB) && defined(VIA_ENABLE)

#    include "via.h"
#    include "color.h"
#    include "progmem.h"
#    include "eeprom.h"
#    include "bnk9_user.h"

#    define BNK9_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

#    if VIA_EEPROM_CUSTOM_CONFIG_SIZE == 0
#        error VIA_EEPROM_CUSTOM_CONFIG_SIZE was not defined to store user_config struct
#    endif

// clang-format off
#define _H__(h)  ((uint8_t)((h) * 255 / 360))  // Convert hue (0-360) to (0-255)
#define _S__(s)  ((uint8_t)((s) * 255 / 100))  // Convert saturation (0-100) to (0-255))
// clang-format on

user_config_t g_user_config;

// *** Helpers ***

#    ifdef RGB_MATRIX_ENABLE
void __set_all_leds(uint8_t red, uint8_t green, uint8_t blue) {
    if (!rgb_matrix_is_enabled()) rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(red, green, blue);
    rgb_matrix_update_pwm_buffers();
    wait_ms(100); // 1/10 sec
}
#    endif

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

        case id_custom_lyrclr: {
            uint8_t i                 = value_data[0];
            g_user_config.lyrclr[i].h = value_data[1];
            g_user_config.lyrclr[i].s = value_data[2];
            break;
        }

        case id_custom_l0_off: {
            g_user_config.l0_off = value_data[0] != 0;
            break;
        }

        case id_encoder_resolution: {
            g_user_config.enc_res = value_data[0];
            break;
        }

        case id_firmware_button: {
            switch (value_data[0]) {
                case id_button_bootloader:
                    __set_all_leds(RGB_RED);
                    reset_keyboard();
                    break;
                case id_button_reboot:
                    __set_all_leds(RGB_BLUE);
                    soft_reset_keyboard();
                    break;
                case id_button_debug_toggle:
                    debug_enable ^= 1;
                    break;
                case id_button_clear_eeprom:
                    __set_all_leds(RGB_YELLOW);
                    eeconfig_disable();
                    wait_ms(400); // 1/2 sec, with the 100 in __set_all_leds
                    soft_reset_keyboard();
                    break;
            }
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

        case id_custom_lyrclr: {
            uint8_t i     = value_data[0];
            value_data[1] = g_user_config.lyrclr[i].h;
            value_data[2] = g_user_config.lyrclr[i].s;
            break;
        }

        case id_custom_l0_off: {
            value_data[0] = g_user_config.l0_off ? 1 : 0;
            break;
        }

        case id_encoder_resolution: {
            value_data[0] = g_user_config.enc_res;
            break;
        }

        case id_firmware_button: {
            value_data[0] = 0; // ignore
            break;
        }
    }
}

void bnk9_config_init(void) {
    for (uint8_t i = 0; i < 9; i++) {
        g_user_config.color[i].h  = _H__(i * 30);
        g_user_config.color[i].s  = _S__(100);
        g_user_config.lyrclr[i].h = _H__(i * 30);
        g_user_config.lyrclr[i].s = _S__(100);
    }
    g_user_config.l0_off  = false;
    g_user_config.enc_res = 0;
}

#    ifdef COMMUNITY_MODULE_BP_ENCODER_CONFIGURABLE_ENABLE

uint8_t get_encoder_resolution(void) {
    if (0 == g_user_config.enc_res) {
        return ENCODER_RESOLUTION; // give back default
    } else {
        return (g_user_config.enc_res * 2);
    }
}

bool get_encoder_default_pos(void) {
    if (0 == g_user_config.enc_res) {
        return (4 == ENCODER_RESOLUTION);
    } else {
        return (g_user_config.enc_res == 2);
    }
}

#    endif // COMMUNITY_MODULE_BP_ENCODER_CONFIGURABLE_ENABLE

void bnk9_config_load(void) {
    eeprom_read_block(&g_user_config, ((void *)BNK9_CONFIG_EEPROM_ADDR), sizeof(user_config_t));
}

void bnk9_config_save(void) {
    eeprom_update_block(&g_user_config, ((void *)BNK9_CONFIG_EEPROM_ADDR), sizeof(user_config_t));
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
    bnk9_config_init();

    // This checks both an EEPROM reset (from bootmagic lite, keycodes)
    // and also firmware build date (from via_eeprom_is_valid())
    if (eeconfig_is_enabled()) {
        bnk9_config_load();
    } else {
        bnk9_config_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

#endif // RGB_MATRIX_CUSTOM_KB
