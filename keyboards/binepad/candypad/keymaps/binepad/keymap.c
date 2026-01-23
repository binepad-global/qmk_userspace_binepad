// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "sr_version.h"
#include "candypad_user.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_KB_9:
            return process_record_sr_version(COMMUNITY_MODULE_SEND_VERSION, record);
            break;
    }
    return true; // For all other keys, use default processing
}

#ifdef OLED_ENABLE

// OLED functions
uint8_t  oled_mode                  = OLED_SPLASH;
bool     oled_repaint_requested     = false;
uint32_t oled_splash_timer          = 0;
uint8_t  oled_splash_animation_step = 0;

/** CandyPad Logo */
__attribute__((weak)) bool candypad_render_logo_user(void) {
    // Generated from https://joric.github.io/qle/
    static const char PROGMEM raw_logo[] = {
          0,  0,  0,  0,128,192,224, 96,240,240,152, 24, 24, 24, 24, 24, 24, 24, 24, 56, 48, 96,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,
          0,192,248, 62,  7, 15, 28, 56,112,225,195,135, 14, 28, 56,112,224,192,128,  0,  0,  0,  0,  1,  7, 62,252,192,  0,128,192,224,112, 48, 48, 48,112, 96,  0,128,192,224, 96, 48, 48, 48,112,224,240,240,  0,  0,240,240, 96,112, 48, 48, 48,112,224,192,128,  0,  0,128,192,224,112, 48, 48, 48,112,224,255,255,  0, 48,112,224,128,  0,  0,  0,  0,128,224,112, 48,  0,240,240,224,112, 48, 48, 48,112,224,192,128,  0,  0,128,192,224, 96, 48, 48, 48,112,224,240,240,  0,  0,128,192,224,112, 48, 48, 48,112,224,255,255,  0,
          0,  3, 31,124,224,192,  0,  0,  0,  0,  1,  3,  7, 14, 28, 56,112,225,195,135, 14, 28, 56,240,224,124, 63,  3,  0, 15, 31, 56,112, 96, 96, 96,112, 48,  0, 15, 31, 56,112, 96, 96, 96,112, 56,127,127,  0,  0,127,127,  0,  0,  0,  0,  0,  0,  1,127,127,  0,  0, 15, 31, 56,112, 96, 96, 96,112, 56,127,127,  0,  0,  0,  3, 15, 62,240,248, 62, 15,  3,  0,  0,  0,255,255, 56,112, 96, 96, 96,112, 56, 31, 15,  0,  0, 15, 31, 56,112, 96, 96, 96,112, 56,127,127,  0,  0, 15, 63, 56,112, 96, 96, 96,112, 56,127,127,  0,
          0,  0,  0,  0,  1,  3,  7,  6, 14, 12, 24, 24, 24, 24, 24, 24, 24, 24, 25, 15, 15,  6,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28, 31,  7,  1,  0,  0,  0,  0,  0,  0, 31, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    uint8_t buff_logo[16 * 4 * 8];

    if (OLED_SPLASH == oled_mode || oled_splash_animation_step == 0) {
        memcpy_P(buff_logo, raw_logo, sizeof(buff_logo));
    } else {
        memset(buff_logo, 0, sizeof(buff_logo)); // fill with 0s
        const uint8_t shift = oled_splash_animation_step;
        for (uint8_t x = 0; x < 128; x++) {
            uint32_t col = 0;
            col |= (uint32_t)pgm_read_byte(raw_logo + (0 * 128) + x) << 0;
            col |= (uint32_t)pgm_read_byte(raw_logo + (1 * 128) + x) << 8;
            col |= (uint32_t)pgm_read_byte(raw_logo + (2 * 128) + x) << 16;
            col |= (uint32_t)pgm_read_byte(raw_logo + (3 * 128) + x) << 24;
            col >>= shift;
            buff_logo[(0 * 128) + x] = (uint8_t)(col & 0xFF);
            buff_logo[(1 * 128) + x] = (uint8_t)((col >> 8) & 0xFF);
            buff_logo[(2 * 128) + x] = (uint8_t)((col >> 16) & 0xFF);
            buff_logo[(3 * 128) + x] = (uint8_t)((col >> 24) & 0xFF);
        }
    }

    oled_write_raw_P((const char *)buff_logo, sizeof(buff_logo));

    return true;
}

/** called on OLED initialization */
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_mode         = OLED_SPLASH;
    oled_splash_timer = sync_timer_read32();
    return rotation;
}

bool candypad_render_default_user(void) {
    if (OLED_SPLASH == oled_mode || OLED_ANIMATION == oled_mode) {
        return candypad_render_logo_user();
    }
    return false;
}

/** runs once per loop */
void housekeeping_task_user(void) {
    if (0 != oled_splash_timer) {
        if (OLED_SPLASH == oled_mode) {
            if (timer_elapsed32(oled_splash_timer) > OLED_SPLASH_TIMEOUT) {
                oled_mode                  = OLED_ANIMATION;
                oled_splash_animation_step = 1;
                oled_repaint_requested     = true;
                oled_splash_timer          = sync_timer_read32(); // reset for recount
            }
        } else if (OLED_ANIMATION == oled_mode) {
            if (timer_elapsed32(oled_splash_timer) > OLED_SPLASH_ANIMATION_TIME) {
                if (oled_splash_animation_step < (OLED_DISPLAY_HEIGHT)) {
                    oled_splash_animation_step++;
                    oled_splash_timer      = sync_timer_read32(); // reset for recount
                } else {
                    oled_mode              = OLED_DEFAULT;
                    oled_splash_timer      = 0; // disable
                    oled_repaint_requested = true;
                }
            }
        }
    }
}

void suspend_wakeup_init_user(void) {
    oled_on(); // need this since OLED_TIMEOUT == 0
}

bool oled_task_user(void) {
    // if (!oled_task_needs_to_repaint()) { return false; }
    /* !! : oled_clear(); // Is broken !!! */
    if (oled_repaint_requested) {
        oled_repaint_requested = false;
        oled_clear();
        return false;
    }
    return true;
}

#endif // OLED_ENABLE
