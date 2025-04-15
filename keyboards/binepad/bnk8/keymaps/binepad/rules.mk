# Copyright 2024 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# CONSOLE_ENABLE = yes  ## for debugging!
# COMMAND_ENABLE = yes

RGB_MATRIX_CUSTOM_KB = yes
CAFFEINE_ENABLE = yes

OS_DETECTION_ENABLE = yes
ENCODER_DRIVER ?= custom  # use custom encoder

VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += encoder_configurable.c  # our custom encoder
SRC += binepad_common.c
SRC += bnk8_effect.c

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif
