## MODIFIED Requirements

### Requirement: Only the dedicated central advertises keyboard status
The dedicated dongle SHALL broadcast Prospector status with keyboard name `TPAK`, central side `AUX`, and two expected BLE keyboard peripherals. Prospector SHALL remain an independent observer, not a member of the split. While the dongle runs its own status advertising, it SHALL advertise from its stable identity address and SHALL deliver the name both in SCAN_RSP and in periodic name-only advertisements.

#### Scenario: Inspect the normal firmware matrix
- **WHEN** the four existing targets are built
- **THEN** status advertising is enabled only in `tpaktop-corne-dongle`
- **AND** neither peripheral nor settings-reset firmware enables Prospector status advertising

#### Scenario: Receive the configured keyboard name
- **WHEN** Scanner receives and associates a name advertisement with this dongle's status advertisements
- **THEN** it displays `TPAK`, not `Unknown`
- **AND** successful compilation alone is not evidence that the physical Scanner received the name

#### Scenario: Name while connected to a BLE host
- **WHEN** the dongle is connected to a BLE host and both halves are connected
- **THEN** Scanner displays `TPAK`

#### Scenario: Name survives restarts
- **WHEN** the dongle reboots or a half is power-cycled
- **THEN** the status advertisement keeps the same BLE address
- **AND** Scanner still displays `TPAK` afterwards
