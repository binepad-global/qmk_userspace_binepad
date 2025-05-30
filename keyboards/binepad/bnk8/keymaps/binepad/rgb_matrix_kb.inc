// Copyright 2024 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RGB_MATRIX_CUSTOM_KB
#    error "This does not work without RGB_MATRIX_CUSTOM_KB"
#endif

// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(bnk8_per_key_effect)
RGB_MATRIX_EFFECT(bnk8_per_layer_effect)

#if defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS) && defined(VIA_ENABLE)

#    include "bnk8_user.h"

/**
 * Per-key color effect
 */
static bool bnk8_per_key_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv;
    RGB rgb;

    // Assuming `g_user_config` is set prior

    hsv.v = rgb_matrix_get_val();
    for (uint8_t i = led_min; i < led_max; i++) {
        if (i < 8) {
            hsv.h = g_user_config.color[i].h;
            hsv.s = g_user_config.color[i].s;
            rgb   = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

/*
 * Per-layer effect
 */
static bool bnk8_per_layer_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv;
    RGB rgb;

    // Assuming `g_user_config` is set prior

    uint8_t i = get_highest_layer(layer_state) % 8; // 8 = how many colors stored in g_user_config
    if ((0 == i) && !g_user_config.l0_off) {
        rgb_matrix_set_color_all(0, 0, 0); // off / no color
    } else {
        hsv.h     = g_user_config.lyrclr[i].h;
        hsv.s     = g_user_config.lyrclr[i].s;
        hsv.v     = rgb_matrix_get_val();
        rgb       = hsv_to_rgb(hsv);
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif
