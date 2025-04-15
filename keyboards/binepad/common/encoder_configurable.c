// Copyright 2018 Jack Humbert <jack.humb@gmail.com>
// Copyright 2018-2023 Nick Brassel (@tzarc)
// Copyright 2025 Silvino R. (@silvinor)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * ┌──────────────────────────────────────────────────────────────────────────┐
 * │  This file is mostly a direct copy of the                                │
 * │    `/qmk/qmk_firmware/blob/master/drivers/encoder/encoder_quadrature.c`  │
 * │    file.  Why this is duplicated is because we needed a variable         │
 * │    `ENCODER_RESOLUTION` and the existing file had this hardcoded as a C  │
 * │    `#define`, and not a manipulable variable :( .                        │
 * └──────────────────────────────────────────────────────────────────────────┘
 */

#include "encoder_configurable.h"

/*
 * ┌──────────────────────────────────────────────────────────────┐
 * │  This part is the "copy" of the `encoder_quadrature.c` file  │
 * └──────────────────────────────────────────────────────────────┘
 */

#include "quantum.h"
#include "encoder.h"
#include "gpio.h"
#include "keyboard.h"
#include "action.h"
#include "keycodes.h"
#include "wait.h"

// for memcpy
#include <string.h>

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif

#undef ENCODER_DEFAULT_PIN_API_IMPL
#if defined(ENCODER_A_PINS) && defined(ENCODER_B_PINS)
// Inform the quadrature driver that it needs to implement pin init/read functions
#    define ENCODER_DEFAULT_PIN_API_IMPL
#endif

// !! ENCODER_RESOLUTION as a global variable !!
#ifndef OS_DETECTION_ENABLE
static volatile uint8_t encoder_resolution = 4; // same as ENCODER_RESOLUTION 4, as default
#endif

__attribute__((weak)) uint8_t get_encoder_resolution(void) {
#ifdef OS_DETECTION_ENABLE
    switch (detected_host_os()) {
        case OS_LINUX:
            return ENCODER_RESOLUTION_LINUX;
            break;
        case OS_WINDOWS:
            return ENCODER_RESOLUTION_WINDOWS;
            break;
        case OS_MACOS:
            return ENCODER_RESOLUTION_MACOS;
            break;
        case OS_IOS:
            return ENCODER_RESOLUTION_IOS;
            break;
        default:
            break;
    }
    return ENCODER_RESOLUTION;
#else
    return encoder_resolution;
#endif // OS_DETECTION_ENABLE
}

__attribute__((weak)) void encoder_quadrature_init_pin(uint8_t index, bool pad_b);

__attribute__((weak)) uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b);

#ifdef ENCODER_DEFAULT_PIN_API_IMPL

static pin_t encoders_pad_a[NUM_ENCODERS_MAX_PER_SIDE] = ENCODER_A_PINS;
static pin_t encoders_pad_b[NUM_ENCODERS_MAX_PER_SIDE] = ENCODER_B_PINS;

__attribute__((weak)) void encoder_wait_pullup_charge(void) {
    wait_us(100);
}

__attribute__((weak)) void encoder_quadrature_init_pin(uint8_t index, bool pad_b) {
    pin_t pin = pad_b ? encoders_pad_b[index] : encoders_pad_a[index];
    if (pin != NO_PIN) {
        gpio_set_pin_input_high(pin);
    }
}

__attribute__((weak)) uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {
    pin_t pin = pad_b ? encoders_pad_b[index] : encoders_pad_a[index];
    if (pin != NO_PIN) {
        return gpio_read_pin(pin) ? 1 : 0;
    }
    return 0;
}

#endif // ENCODER_DEFAULT_PIN_API_IMPL

#ifndef ENCODER_DIRECTION_FLIP
#    define ENCODER_CLOCKWISE true
#    define ENCODER_COUNTER_CLOCKWISE false
#else
#    define ENCODER_CLOCKWISE false
#    define ENCODER_COUNTER_CLOCKWISE true
#endif
static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state[NUM_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUM_ENCODERS] = {0};

// encoder counts
static uint8_t thisCount;

__attribute__((weak)) void encoder_quadrature_post_init_kb(void) {
    extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);
    // Unused normally, but can be used for things like setting up pin-change interrupts in keyboard code.
    // During the interrupt, read the pins then call `encoder_handle_read()` with the pin states and it'll queue up an encoder event if needed.
}

void encoder_quadrature_post_init(void) {
#ifdef ENCODER_DEFAULT_PIN_API_IMPL
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_quadrature_init_pin(i, false);
        encoder_quadrature_init_pin(i, true);
    }
    encoder_wait_pullup_charge();
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_state[i] = (encoder_quadrature_read_pin(i, false) << 0) | (encoder_quadrature_read_pin(i, true) << 1);
    }
#else
    memset(encoder_state, 0, sizeof(encoder_state));
#endif
    encoder_quadrature_post_init_kb();
}

void encoder_driver_init(void) {
    thisCount = NUM_ENCODERS;
#if defined(ENCODER_RESOLUTION) && !defined(OS_DETECTION_ENABLE)
    encoder_resolution = ENCODER_RESOLUTION; // just for init
#endif
    encoder_quadrature_post_init();
}

static void encoder_handle_state_change(uint8_t index, uint8_t state) {
    uint8_t i = index;

    const uint8_t resolution = get_encoder_resolution();
    encoder_pulses[i] += encoder_LUT[state & 0xF];

#ifdef ENCODER_DEFAULT_POS
    if ((encoder_pulses[i] >= resolution) || (encoder_pulses[i] <= -resolution) || ((state & 0x3) == ENCODER_DEFAULT_POS)) {
        if (encoder_pulses[i] >= 1) {
            encoder_queue_event(index, ENCODER_COUNTER_CLOCKWISE);
        }
        if (encoder_pulses[i] <= -1) {
            encoder_queue_event(index, ENCODER_CLOCKWISE);
        }
        encoder_pulses[i] %= resolution;
        encoder_pulses[i] = 0;
    }
#else
    if (encoder_pulses[i] >= resolution) {
        encoder_queue_event(index, ENCODER_COUNTER_CLOCKWISE);
    }
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
        encoder_queue_event(index, ENCODER_CLOCKWISE);
    }
    encoder_pulses[i] %= resolution;
#endif
}

void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state) {
    uint8_t state = pin_a_state | (pin_b_state << 1);
    if ((encoder_state[index] & 0x3) != state) {
        encoder_state[index] <<= 2;
        encoder_state[index] |= state;
        encoder_handle_state_change(index, encoder_state[index]);
    }
}

__attribute__((weak)) void encoder_driver_task(void) {
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_quadrature_handle_read(i, encoder_quadrature_read_pin(i, false), encoder_quadrature_read_pin(i, true));
    }
}

/*
 * ┌──────────────────────────────────────────────┐
 * │  This part overrides the default driver and  │
 * │    replaces weak functions in `encoder.c`    │
 * └──────────────────────────────────────────────┘
 */

/* __attribute__((weak)) */
// bool should_process_encoder(void) {
//     return true;
// }
