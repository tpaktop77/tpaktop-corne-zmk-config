/*
 * Copyright (c) 2026 tpak
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#include <dt-bindings/tpak/os_profile.h>

enum host_os_profile {
        HOST_OS_WINDOWS = OS_WINDOWS,
        HOST_OS_MACOS = OS_MACOS,
        HOST_OS_LINUX = OS_LINUX,
};

enum host_os_profile tpak_os_profile_get(void);
int tpak_os_profile_set(uint32_t profile);
