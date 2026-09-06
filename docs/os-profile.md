# OS profile

The OS profile is independent internal state in the custom ZMK behavior module. In dongle topology, the module runs on the `nice_nano_v2` central; the halves forward only physical positions. It is neither a keymap layer nor a Bluetooth profile.

## State properties

- Allowed values: `OS_WINDOWS`, `OS_MACOS`, and `OS_LINUX`.
- Initial value after every reboot: `OS_WINDOWS`.
- State exists only in RAM and is not persisted to flash.
- There is no automatic OS detection.
- There are no separate Graphite or QWERTY variants for each OS.
- The OS profile is not linked to `BT0`-`BT4` or the current USB/BLE endpoint.
- Switching Graphite/QWERTY does not change the OS profile.
- Switching Graphite/Russian or changing the host language does not change the OS profile.

## Behavior API

Named values are exported by a repository-local devicetree binding header.

```dts
&os_set OS_WINDOWS
&os_set OS_MACOS
&os_set OS_LINUX

&os_action OS_ACTION_COPY
&os_action OS_ACTION_PASTE
```

`&os_set` changes the profile on press and generates no HID event. On press, `&os_action` selects a HID keycode from the centralized table and delegates the press to standard ZMK `&kp`; on release, it delegates release of the same keycode.

The selected keycode is retained by invocation position until release. Duplicate assignments of the same action therefore remain independent, and even an artificial OS-profile change between press and release cannot release a different modifier or leave the original modifier stuck.

## Action table

| Value | Windows | macOS | Linux |
|---|---|---|---|
| `OS_ACTION_COPY` | Ctrl+C | GUI+C | Ctrl+Insert |
| `OS_ACTION_PASTE` | Ctrl+V | GUI+V | Shift+Insert |
| `OS_ACTION_CUT` | Ctrl+X | GUI+X | Shift+Delete |
| `OS_ACTION_UNDO` | Ctrl+Z | GUI+Z | Ctrl+Z |
| `OS_ACTION_REDO` | Ctrl+Shift+Z | GUI+Shift+Z | Ctrl+Shift+Z |
| `OS_ACTION_SELECT_ALL` | Ctrl+A | GUI+A | Ctrl+A |
| `OS_ACTION_WORD_PREVIOUS` | Ctrl+Left | Alt+Left | Ctrl+Left |
| `OS_ACTION_WORD_NEXT` | Ctrl+Right | Alt+Right | Ctrl+Right |
| `OS_ACTION_WORD_BACKSPACE` | Ctrl+Backspace | Alt+Backspace | Ctrl+Backspace |
| `OS_ACTION_WORD_DELETE` | Ctrl+Delete | Alt+Delete | Ctrl+Delete |
| `OS_ACTION_APP_SWITCH` | Alt+Tab | GUI+Tab | Alt+Tab |
| `OS_ACTION_TASK_VIEW` | GUI+Tab | Ctrl+Up | GUI+Tab |
| `OS_ACTION_VOICE` | GUI+H | Voice Command consumer usage | GUI+H |

## macOS Voice

macOS uses the official ZMK keycode `C_VOICE_COMMAND`, corresponding to HID Consumer Voice Command usage `0xCF`. This matches the original QMK call `host_consumer_send(0xCF)`. ZMK's official compatibility table does not guarantee identical behavior across all macOS versions, so Siri or voice activation remains a required hardware test.

## System layer selectors

System positions `19`, `20`, and `21` contain:

```text
&os_set OS_WINDOWS
&os_set OS_MACOS
&os_set OS_LINUX
```

These are three adjacent keys on the right home row. Position `18` remains empty, placing Windows at position `19` under the index finger. The behavior runs on the dongle central and does not change the active keymap layer.

## Independent host-language switching

The OS profile, Bluetooth profile, and language are three independent mechanisms:

- `&os_set` changes only the internal Windows/macOS/Linux profile;
- `&bt BT_SEL` changes only the Bluetooth profile;
- `to_russian` and `to_english` send a host-language shortcut and change only the `RUSSIAN` or `GRAPHITE` base layer.

The language macro neither selects nor depends on the OS profile. On each Windows, macOS, or Linux host, the user must configure `Ctrl+Shift+1` as direct selection of English and `Ctrl+Shift+2` as direct selection of Russian-PC. On macOS this can use Hammerspoon as in the QMK/Oryx source; Windows and Linux can use available system settings or a direct-layout selection utility.

| Host | Required preparation | Check before keymap testing |
|---|---|---|
| Windows | retain the current setting or utility where `Ctrl+Shift+1` selects English and `Ctrl+Shift+2` selects Russian-PC | press both shortcuts on a regular keyboard and verify direct rather than cyclic selection |
| macOS | retain the Hammerspoon bindings from the working Voyager setup for U.S. and Russian-PC | verify direct selection of both input sources |
| Linux | assign two direct shortcuts through the desktop environment, window manager, or helper utility | verify that each shortcut selects a specific layout rather than the next layout in a cycle |

The firmware does not detect the active host language, persist it to flash, or link it to `BT0`-`BT4`. After reboot, the firmware starts with Graphite and the Windows OS profile, but the actual host language can differ until the first directed `to_russian` or `to_english` action.

## Current-stage limitations

- The profile does not survive reboot.
- The host does not automatically provide the profile.
- The profile is not selected together with a Bluetooth profile.
- The language and Russian layer are not selected with an OS or Bluetooth profile.
- There is no automatic resynchronization after the host language is changed externally.
- The Navigation layer does not yet use `&os_action`: `migrated, OS adaptation deferred`.
- Only the listed combos use the OS-aware API.
