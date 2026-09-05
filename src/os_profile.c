/*
 * Copyright (c) 2026 tpak
 * SPDX-License-Identifier: MIT
 */

#include <errno.h>
#include <stdint.h>

#include <tpak/os_profile.h>

// Intentionally volatile: every reboot starts in the Windows profile.
static enum host_os_profile current_os = HOST_OS_WINDOWS;

enum host_os_profile tpak_os_profile_get(void) { return current_os; }

int tpak_os_profile_set(uint32_t profile) {
        switch (profile) {
        case OS_WINDOWS:
        case OS_MACOS:
        case OS_LINUX:
                current_os = (enum host_os_profile)profile;
                return 0;
        default:
                return -EINVAL;
        }
}
