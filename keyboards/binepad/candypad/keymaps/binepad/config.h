// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef OLED_ENABLE
#    ifdef OLED_TIMEOUT
#        undef OLED_TIMEOUT
#    endif
#    define OLED_TIMEOUT 0
#endif
