// Copyright 2025 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

// Community Modules are not supported in VIAL yet (as of March 2025)
// This file helps fake that :(

#pragma once

#include "community_modules.h"
#include <stdint.h>
#include <stdbool.h>
#include <action.h>
#include <keycodes.h>

#ifdef COMMUNITY_MODULE_VERSION_ENABLE
// From module: silvinor/version
bool process_record_version(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef COMMUNITY_MODULE_CAFFEINE_ENABLE
// From module: silvinor/caffeine
bool process_record_caffeine(uint16_t keycode, keyrecord_t *record);
void housekeeping_task_caffeine(void);
#endif

#ifdef COMMUNITY_MODULE_GLOBE_KEY_ENABLE
// From module: tzarc/globe_key
bool process_record_globe_key(uint16_t keycode, keyrecord_t *record);
#endif
