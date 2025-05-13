// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// Only works if VIA is enabled
#if defined(VIA_ENABLE)

#    include "via.h"
#    include "knobx1_user.h"

void knobx1_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_firmware_button: {
            switch (value_data[0]) {
                case id_button_bootloader:
                    reset_keyboard();
                    break;
                case id_button_reboot:
                    soft_reset_keyboard();
                    break;
                case id_button_debug_toggle:
                    debug_enable ^= 1;
                    break;
                case id_button_clear_eeprom:
                    eeconfig_disable();
                    wait_ms(500); // 1/2 sec
                    soft_reset_keyboard();
                    break;
            }
            break;
        }
    }
}

// void knobx1_config_get_value(uint8_t *data) {
//     uint8_t *value_id   = &(data[0]);
//     uint8_t *value_data = &(data[1]);
//     switch (*value_id) {
//     }
// }

// void bnk8_config_init(void) {
// }

// void bnk8_config_load(void) {
//     eeprom_read_block(&g_user_config, ((void *)KNOBX1_CONFIG_EEPROM_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
// }

// void bnk8_config_save(void) {
//     eeprom_update_block(&g_user_config, ((void *)KNOBX1_CONFIG_EEPROM_ADDR), VIA_EEPROM_CUSTOM_CONFIG_SIZE);
// }

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

#    ifdef CONSOLE_ENABLE
    print_buff(&(data[0]), 4);
#    endif

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                knobx1_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                // knobx1_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                // knobx1_config_save();
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

#endif // VIA_ENABLE
