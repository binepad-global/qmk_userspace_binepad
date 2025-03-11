// Copyright 2023 Silvino Rodrigues (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"

RGB adjust_to_brightness(uint8_t r, uint8_t g, uint8_t b, uint8_t min, uint8_t max);

// uint16_t find_key_index(uint16_t target_keycode);

bool process_record_binepad(uint16_t keycode, keyrecord_t *record);
