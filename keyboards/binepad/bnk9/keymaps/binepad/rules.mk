# Copyright 2023 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

MIDI_ENABLE = yes

# CONSOLE_ENABLE = yes  ## for debugging!
# COMMAND_ENABLE = yes

RGB_MATRIX_CUSTOM_KB = yes

# VPATH += $(QMK_USERSPACE)/keyboards/binepad/common
SRC += bnk9_effect.c
