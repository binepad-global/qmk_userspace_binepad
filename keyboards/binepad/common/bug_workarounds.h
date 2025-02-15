// Copyright 2023 Silvino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

uint16_t find_legacy_keycode(uint16_t old_val);
bool process_record_bugfixes(uint16_t keycode, keyrecord_t *record);
