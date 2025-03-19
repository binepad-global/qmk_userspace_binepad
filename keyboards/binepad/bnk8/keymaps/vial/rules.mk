# Copyright 2025 Binepad (@binpad)
# SPDX-License-Identifier: GPL-2.0-or-later

VIA_ENABLE = yes
VIAL_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
VIALRGB_ENABLE = yes
MIDI_ENABLE = yes

# CONSOLE_ENABLE = yes  ## for debugging!
# COMMAND_ENABLE = yes

# VPATH += $(QMK_USERSPACE)/keyboards/binepad/common ## !! deprecated

### Community Modules are not supported in VIAL yet (as of March 2025)
### These lines help hack that.

VPATH += $(QMK_USERSPACE)/modules/binepad/common
SRC += common.c

VPATH += $(QMK_USERSPACE)/modules/silvinor/version
SRC += version.c

VPATH += $(QMK_USERSPACE)/modules/silvinor/caffeine
SRC += caffeine.c

VPATH += $(QMK_USERSPACE)/modules/tzarc/globe_key
SRC += globe_key.c

### / Community Modules (, end of)
