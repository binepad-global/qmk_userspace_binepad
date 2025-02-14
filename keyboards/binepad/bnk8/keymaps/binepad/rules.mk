# Copyright 2024 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

RGB_MATRIX_CUSTOM_KB = yes
SRC += bnk8_effect.c

# CONSOLE_ENABLE = yes  ## for debugging!
# COMMAND_ENABLE = yes

CAFFEINE_ENABLE = yes

VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += binepad_common.c
SRC += bug_workarounds.c

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif
