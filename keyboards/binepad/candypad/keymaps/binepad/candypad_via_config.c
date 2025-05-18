// Copyright 2024 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "candypad_user.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// Only works if VIA is enabled
#ifdef VIA_ENABLE

void candypad_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rtc_date:
            // not implemented yet
            break;

        case id_rtc_time:
            // not implemented yet
            break;

        case id_rtc_posix_time:
            // not implemented yet
            break;

        case id_firmware_button: {
            switch (value_data[0]) {
                case id_button_bootloader:
                    // TODO : OLED message
                    reset_keyboard();
                    break;
                case id_button_reboot:
                    // TODO : OLED message
                    soft_reset_keyboard();
                    break;
                case id_button_debug_toggle:
                    debug_enable ^= 1;
                    break;
                case id_button_clear_eeprom:
                    // TODO : OLED message
                    eeconfig_disable();
                    wait_ms(500); // 1/2 sec
                    soft_reset_keyboard();
                    break;
            }
            break;
        }
    }
}

void candypad_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rtc_date:
            // not implemented yet
            break;

        case id_rtc_time:
            // not implemented yet
            break;

        case id_rtc_posix_time:
            // not implemented yet
            break;

        case id_firmware_button:
            value_data[0] = 0; // ignore
            break;
    }
}

// void bnk8_config_init(void) {
//     g_user_config.{fill in here} = 0;
// }

// void candypad_config_load(void) {
//     eeprom_read_block(&g_user_config, ((void *)CANDYPAD_CONFIG_EEPROM_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
// }

// void candypad_config_save(void) {
//     eeprom_update_block(&g_user_config, ((void *)CANDYPAD_CONFIG_EEPROM_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
// }

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                candypad_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                candypad_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                // candypad_config_save();
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

// void via_init_kb(void) {
//     candypad_config_init();
//
//     // This checks both an EEPROM reset (from bootmagic lite, keycodes)
//     // and also firmware build date (from via_eeprom_is_valid())
//     if (via_eeprom_is_valid()) {
//         candypad_config_load();
//     } else {
//         candypad_config_save();
//         // DO NOT set EEPROM valid here, let caller do this
//     }
// }

#endif // VIA_ENABLE
