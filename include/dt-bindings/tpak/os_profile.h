/*
 * Copyright (c) 2026 tpak
 * SPDX-License-Identifier: MIT
 */

#pragma once

// Volatile host OS profiles.
#define OS_WINDOWS 0
#define OS_MACOS 1
#define OS_LINUX 2
#define OS_PROFILE_COUNT 3

// OS-aware actions accepted by &os_action.
#define OS_ACTION_COPY 0
#define OS_ACTION_PASTE 1
#define OS_ACTION_CUT 2
#define OS_ACTION_UNDO 3
#define OS_ACTION_REDO 4
#define OS_ACTION_SELECT_ALL 5
#define OS_ACTION_WORD_PREVIOUS 6
#define OS_ACTION_WORD_NEXT 7
#define OS_ACTION_WORD_BACKSPACE 8
#define OS_ACTION_WORD_DELETE 9
#define OS_ACTION_APP_SWITCH 10
#define OS_ACTION_TASK_VIEW 11
#define OS_ACTION_VOICE 12
#define OS_ACTION_COUNT 13
