# Copyright 2024 binepad (@binepad)
# SPDX-License-Identifier: GPL-2.0-or-later

NKRO_ENABLE = no  # too few keys for NKRO to make sense
VIA_ENABLE = yes

VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += binepad_common.c
