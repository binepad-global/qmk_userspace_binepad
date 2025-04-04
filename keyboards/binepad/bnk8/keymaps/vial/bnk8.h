// Copyright 2025 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#ifdef VIA_ENABLE // Only works if VIA is enabled
#    include "color.h"
#endif

// clang-format off
enum bnk8_keyboard {
    #ifdef CAFFEINE_ENABLE
    KC_CAFFEINE_TOGGLE = QK_KB_0
    #endif // CAFFEINE_ENABLE
};
// clang-format on

#ifdef CAFFEINE_ENABLE
#    define KC_COFFEE KC_CAFFEINE_TOGGLE
#endif // CAFFEINE_ENABLE
