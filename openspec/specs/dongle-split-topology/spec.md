## Purpose

Defines a BLE split topology with a dedicated central dongle and two Corne peripheral halves while preserving five independent host profiles.

## Requirements

### Requirement: The dongle is the only central
The firmware SHALL use a keyless `nice_nano_v2` as the ZMK split central, while `corne_left` and `corne_right` SHALL operate as BLE peripherals.

#### Scenario: Press a key on the left half
- **WHEN** the user presses a key on `corne_left`
- **THEN** the positional event is forwarded to the dongle, processed by its keymap, and sent to the host

#### Scenario: Press a key on the right half
- **WHEN** the user presses a key on `corne_right`
- **THEN** the positional event is forwarded to the same dongle and processed by the same keymap

#### Scenario: Operate without the dongle
- **WHEN** the dongle is off or absent
- **THEN** the halves do not send keyboard HID directly to the host

### Requirement: The central accepts two peripherals and five host profiles
The central SHALL support exactly two split peripherals and five user-facing Bluetooth host profiles `BT0`-`BT4`; connection and pairing limits MUST account for both groups.

#### Scenario: Maintain simultaneous split links
- **WHEN** both previously paired halves are powered on
- **THEN** the central can simultaneously maintain connections to both halves and the selected host

#### Scenario: Select a host profile
- **WHEN** the user selects `BT0`-`BT4` on the System layer
- **THEN** the dongle host profile changes without replacing the halves' central pairing

### Requirement: Peripheral battery retrieval on the central is deferred
The ZMK v0.3 central MUST NOT enable battery-level fetching or battery proxy for the two peripherals in this change.

#### Scenario: Audit central configuration
- **WHEN** the final dongle Kconfig is inspected
- **THEN** fetching and proxy for split-peripheral battery levels are disabled

### Requirement: Both halves use only the Corne 6-column layout
Peripheral firmware SHALL disable the alternative `foostan_corne_5col_layout` and SHALL transform matrix events with the 42-position Corne `default_transform`; the right half SHALL retain `col-offset = 6`.

#### Scenario: Right home row
- **WHEN** the user presses the five right-home-row letter keys from inner to outer on Graphite
- **THEN** the central receives positions 18-22 and outputs `YHAEI`, not 5-column positions 15-19 (`TSGYH`)

#### Scenario: Positional combo after the fix
- **WHEN** the user presses physical positions 19+20+21 on the right home row
- **THEN** the central recognizes the Enter combo using the original 42-position indices

#### Scenario: Install the fix
- **WHEN** both halves are already paired with the same dongle central
- **THEN** the user can install the fix by reflashing left/right peripheral UF2 files without a settings reset or dongle reflash
