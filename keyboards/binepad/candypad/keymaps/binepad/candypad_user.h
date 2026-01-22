// Copyright 2023 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"


#ifdef OLED_ENABLE

#    ifndef OLED_SPLASH_TIMEOUT
#        define OLED_SPLASH_TIMEOUT 4500 // 4.5 seconds
#    endif
#    ifndef OLED_SPLASH_ANIMATION_TIME
#        define OLED_SPLASH_ANIMATION_TIME 25 // .025 seconds
#    endif

// clang-format off
enum oled_modes {
    OLED_SPLASH,
    OLED_ANIMATION,
    OLED_DEFAULT,
    OLED_OFF,
    __NUM_OLED_MODES
} oled_modes_t;
// clang-format on

bool candypad_render_logo_user(void);
bool candypad_render_default_user(void);

// OLED functions
extern uint8_t  oled_mode;
extern bool     oled_repaint_requested;
extern uint32_t oled_splash_timer;
extern uint8_t  oled_splash_animation_step;

#endif // OLED_ENABLE


#ifdef VIA_ENABLE // Only works if VIA is enabled

enum via_per_key_value {
    /*
    id_rtc_date = 8,
    id_rtc_time = 9,
    id_rtc_posix_time = 10,
    */
    id_firmware_button = 99
};

/**
 * A note on time setting:
 * (!! PLEASE NOTE THIS IS NOT IMPLEMENTED YET!!)
 *
 * `id_set_date` takes 4 bytes, 0 at any byte invalidates whole date
 *  data[0] = Century of the year, i.e. 2025 => 20
 *  data[1] = Cropped 2 digit year, i.e. 2025 => 25
 *  data[2] = Month, i.e. 1 = Jan, 12 = Dec
 *  data[3] = Calendar Day
 *
 * `id_set_time` takes 4 bytes
 *  data[0] = Hour portion, in 24 hour format, i.e. 1PM => 13, Midnight => 0
 *  data[1] = Minute portion
 *  data[2] = Seconds portion
 *  data[3] = Time flag, where
 *     0x07, where lower 3 bits (0-7) are day of week, i.e. 0 => Sun
 *     0x08, ignored/reserved
 *     0x10, use 24H format
 *     0x20, use DST, offset hour by -1
 *     0xC0, ignored/reserved
 */


enum via_id_firmware_button {
    id_buton_ignore = 0,
    id_button_bootloader,   // 1
    id_button_reboot,       // 2
    id_button_debug_toggle, // 3
    id_button_clear_eeprom  // 4
};

// enum custom_keycodes {
//     // USER_SET_KEYCODE_SEND_VERSION is QK_KB_9
// };

#endif // VIA_ENABLE
