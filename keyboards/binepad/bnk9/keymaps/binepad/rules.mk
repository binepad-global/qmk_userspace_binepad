# Copyright 2023 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# EEPROM_DRIVER = wear_leveling
# WEAR_LEVELING_DRIVER = rp2040_flash
# CONSOLE_ENABLE = yes  ## for debugging!
# COMMAND_ENABLE = yes

RGB_MATRIX_CUSTOM_KB = no  # temp. disable while VIA gets fixed
CAFFEINE_ENABLE = yes

VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += binepad_common.c
SRC += bug_workarounds.c
SRC += bnk9_effect.c

ifeq ($(strip $(CAFFEINE_ENABLE)), yes)
    SRC += caffeine.c
    OPT_DEFS += -DCAFFEINE_ENABLE
endif
