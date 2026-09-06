## Purpose

Assigns all keymap-dependent and host-facing services to the dongle so the peripheral halves remain simple sources of physical position events.

## Requirements

### Requirement: The central executes the keymap and custom behaviors
The dongle SHALL own keymap processing, positional combos, macros, Auto Shift, layer-tap processing including the shared `SYM_NUM` layer, Bluetooth behaviors, and custom `&os_set`/`&os_action` behaviors; peripherals SHALL forward physical events to the central.

#### Scenario: Cross-half combo
- **WHEN** a chord contains positions from the left and right halves
- **THEN** the central recognizes the positional combo using the shared 42-key transform

#### Scenario: OS-aware action
- **WHEN** a combo invokes `&os_action`
- **THEN** the dongle generates HID press/release events for the current volatile OS profile without stuck modifiers

#### Scenario: Concurrent duplicate OS actions
- **WHEN** the same `&os_action` value is assigned at two positions and both positions overlap in time
- **THEN** each position retains and releases its own encoded keycode independently

#### Scenario: Nested Shift Digits activation
- **WHEN** a peripheral reports the hold sequence for positions 37 and 39
- **THEN** the dongle resolves the corresponding Symbols layer and then activates `SYM_NUM`

### Requirement: The central safely tracks concurrent combos
The dongle SHALL support eight concurrently pressed combos so modifier and momentary-layer combos do not overflow the ZMK v0.3 default active-combo storage.

#### Scenario: Activate a fifth held combo
- **WHEN** four modifier combos remain held and the user activates a Smiles layer combo
- **THEN** the fifth combo activates instead of re-emitting its source positions as ordinary keys

### Requirement: The OS profile remains independent and volatile
Changing topology MUST NOT alter the OS-profile model: Windows SHALL be the default after reboot, the profile MUST NOT be stored in flash, and it MUST NOT be linked to a host Bluetooth profile.

#### Scenario: Reboot after selecting macOS
- **WHEN** the user selects macOS and reboots the dongle
- **THEN** the OS profile returns to Windows and the active keymap base returns to Graphite

#### Scenario: Change Bluetooth profile
- **WHEN** the user selects a different `BT0`-`BT4` profile
- **THEN** the current OS profile remains unchanged

### Requirement: Central services remain available without Studio
The dongle SHALL continue to provide keyboard HID, BLE host selection, positional keymap processing, macros, combos, Auto Shift, layer taps, and custom OS behaviors without enabling ZMK Studio. Removing Studio MUST NOT change the roles or firmware behavior of either peripheral half.

#### Scenario: Use the keyboard after Studio removal
- **WHEN** the updated dongle is flashed and either peripheral reports a key position
- **THEN** the dongle processes the existing version-controlled keymap and sends the same keyboard HID behavior without exposing a Studio RPC endpoint
