# Copyright 2022 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
VIAL_ENABLE = yes

ifneq ($(findstring r1,$(KEYBOARD)),)
    LTO_ENABLE = yes
endif
