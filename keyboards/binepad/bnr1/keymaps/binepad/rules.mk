# Copyright 2022 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIAL_ENABLE = yes

ifneq ($(findstring v1,$(KEYBOARD)),)
    QMK_SETTINGS = no
    LTO_ENABLE = yes
endif
# ifneq ($(findstring v2,$(KEYBOARD)),)
#     QMK_SETTINGS = yes
# endif
ifneq ($(findstring v3,$(KEYBOARD)),)
    $(info Ψ Vial-QMK qmk_settings.c hack applied)
    QMK_SETTINGS = no
    AUTO_SHIFT_ENABLE := yes
    SRC += byo_settings.c
    OPT_DEFS += -DQMK_SETTINGS \
        -DAUTO_SHIFT_NO_SETUP -DAUTO_SHIFT_REPEAT_PER_KEY -DAUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY \
        -DPERMISSIVE_HOLD_PER_KEY -DHOLD_ON_OTHER_KEY_PRESS_PER_KEY -DQUICK_TAP_TERM_PER_KEY -DRETRO_TAPPING_PER_KEY \
        -DCOMBO_TERM_PER_COMBO
endif
