# Copyright (c) 2026 tpak
# SPDX-License-Identifier: MIT

target_include_directories(app PRIVATE include)

# Keymap behaviors run on the central side of a split keyboard.
if(NOT CONFIG_ZMK_SPLIT OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  if(CONFIG_TPAK_OS_PROFILE)
    target_sources(app PRIVATE
      src/os_profile.c
      src/behaviors/behavior_os_set.c
      src/behaviors/behavior_os_action.c
    )
  endif()
endif()
