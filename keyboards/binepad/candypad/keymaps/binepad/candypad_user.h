// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#ifdef VIA_ENABLE // Only works if VIA is enabled

enum via_per_key_value {
    id_rtc_date = 8,
    id_rtc_time = 9,
    id_rtc_posix_time = 10,
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
