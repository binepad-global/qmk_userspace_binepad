// Copyright 2023 Vino R. (@silvinor)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>

#ifdef OS_DETECTION_ENABLE
#    if defined(ENCODER_RESOLUTION_LINUX) || defined(ENCODER_RESOLUTION_WINDOWS) || defined(ENCODER_RESOLUTION_MACOS) || defined(ENCODER_RESOLUTION_IOS)

#        ifndef ENCODER_RESOLUTION
#            define ENCODER_RESOLUTION 4
#        endif

#        ifndef ENCODER_RESOLUTION_LINUX
#            define ENCODER_RESOLUTION_LINUX ENCODER_RESOLUTION
#        endif
#        ifndef ENCODER_RESOLUTION_WINDOWS
#            define ENCODER_RESOLUTION_WINDOWS ENCODER_RESOLUTION
#        endif
#        ifndef ENCODER_RESOLUTION_MACOS
#            define ENCODER_RESOLUTION_MACOS ENCODER_RESOLUTION
#        endif
#        ifndef ENCODER_RESOLUTION_IOS
#            define ENCODER_RESOLUTION_IOS ENCODER_RESOLUTION_MACOS
#        endif

#    endif // ENCODER_RESOLUTION_x
#endif     // OS_DETECTION_ENABLE

uint8_t get_encoder_resolution(void);
