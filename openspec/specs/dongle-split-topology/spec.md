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

### Requirement: Central retrieves peripheral battery levels
Master ZMK v0.3 dongle firmware SHALL enable battery-level fetching and host battery proxy for both peripherals. The owner accepted this on hardware on 2026-10-18. The halves SHALL NOT enable either option.

#### Scenario: Audit central configuration
- **WHEN** the master dongle configuration is inspected
- **THEN** fetching and proxy for split-peripheral battery levels are enabled only on the dongle

#### Scenario: Regression after a dependency change
- **WHEN** ZMK, Zephyr, or the Prospector module is upgraded
- **THEN** both halves must still type individually and simultaneously after cold starts and reconnects before the upgrade is accepted

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

### Requirement: Host receives peripheral batteries through the dongle
The dongle SHALL expose a readable and notifiable BLE Battery Level for each of its two peripherals through battery proxy. A host app SHALL access them through the existing dongle BLE connection, not by connecting to the halves. USB-only HID SHALL NOT be represented as transporting this BLE service.

#### Scenario: Computer battery monitoring
- **WHEN** the computer is connected to the proxy-enabled dongle over Bluetooth
- **THEN** a compatible app can discover the two Battery Levels labelled Peripheral 0 and Peripheral 1
- **AND** the halves and Scanner do not require reflashing or changed roles

#### Scenario: Preserve pairing while adding BAS
- **WHEN** the dongle firmware is updated to add the proxy service
- **THEN** split and host bonds are not intentionally cleared and settings_reset is not required
- **AND** any stale host service discovery is investigated without automatically deleting bonds
