## Purpose

Assigns all keymap-dependent and host-facing services to the dongle so the peripheral halves remain simple sources of physical position events.

## ADDED Requirements

### Requirement: The central executes the keymap and custom behaviors
The dongle SHALL own keymap processing, positional combos, macros, Auto Shift, Bluetooth behaviors, and custom `&os_set`/`&os_action` behaviors; peripherals SHALL forward physical events to the central.

#### Scenario: Cross-half combo
- **WHEN** a chord contains positions from the left and right halves
- **THEN** the central recognizes the positional combo using the shared 42-key transform

#### Scenario: OS-aware action
- **WHEN** a combo invokes `&os_action`
- **THEN** the dongle generates HID press/release events for the current volatile OS profile without stuck modifiers

### Requirement: ZMK Studio is available through the dongle
ZMK Studio SHALL be enabled on the central and available through the dongle's USB RPC; the Studio snippet MUST NOT be assigned to left or right peripheral firmware.

#### Scenario: Connect Studio
- **WHEN** the dongle is connected to the computer over USB and ZMK Studio is opened
- **THEN** Studio sees the complete Corne physical layout and all version-controlled layers, including three reserved layers

### Requirement: The OS profile remains independent and volatile
Changing topology MUST NOT alter the OS-profile model: Windows SHALL be the default after reboot, the profile MUST NOT be stored in flash, and it MUST NOT be linked to a host Bluetooth profile.

#### Scenario: Reboot after selecting macOS
- **WHEN** the user selects macOS and reboots the dongle
- **THEN** the OS profile returns to Windows and the active keymap base returns to Graphite

#### Scenario: Change Bluetooth profile
- **WHEN** the user selects a different `BT0`-`BT4` profile
- **THEN** the current OS profile remains unchanged
