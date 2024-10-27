// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef VIA_ENABLE // Only works if VIA is enabled
#    define EECONFIG_USER_DATA_SIZE 16 // 16 ??  or sizeof(g_user_config)
#endif
