# Copyright 2022 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

NKRO_ENABLE = no  # too few keys for NKRO to make sense
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
QMK_SETTINGS = no  # don't need these

VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += binepad_common.c
