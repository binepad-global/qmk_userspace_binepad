// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Community modules */

#define USER_SET_KEYCODE_SEND_VERSION QK_KB_9

#define DOUBLE_TAP_KEY_COUNT 1

#if defined(ENCODER_RESOLUTION) && defined(OS_DETECTION_ENABLE)
#    define ENCODER_RESOLUTION_MACOS 4 // Used by BP_Encoder_Config community module
#endif
