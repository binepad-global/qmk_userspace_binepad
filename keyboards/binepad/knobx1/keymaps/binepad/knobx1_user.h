// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#ifdef VIA_ENABLE // Only works if VIA is enabled

enum via_per_key_value {
    id__unused__1 = 1,
    id__unused__2,     // 2
    id__unused__3,     // 3
    id__unused__4,     // 4
    id_firmware_button // 5
};

enum via_id_firmware_button {
    id_buton_ignore = 0,
    id_button_bootloader,   // 1
    id_button_reboot,       // 2
    id_button_debug_toggle, // 3
    id_button_clear_eeprom  // 4
};

enum custom_keycodes {
    X1__SPARE__0 = QK_KB_0,
    X1__SPARE__1,  // 1
    X1__SPARE__2,  // 2
    X1__SPARE__3,  // 3
    X1__SPARE__4,  // 4
    X1__SPARE__5,  // 5
    X1_LAYER_UP,   // 6
    X1_LAYER_DOWN, // 7
    X1_LAYER_JUMP, // 8
    // USER_SET_KEYCODE_SEND_VERSION
};

#endif // VIA_ENABLE
