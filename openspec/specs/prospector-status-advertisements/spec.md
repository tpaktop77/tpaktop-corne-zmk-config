# prospector-status-advertisements Specification

## Purpose
Defines the dedicated dongle's status broadcasts for an independent Prospector Scanner and the peripheral battery levels they carry.

## Requirements

### Requirement: Only the dedicated central advertises keyboard status
The dedicated dongle SHALL broadcast Prospector status with keyboard name `TPAK`, central side `AUX`, and two expected BLE keyboard peripherals. Prospector SHALL remain an independent observer, not a member of the split.

#### Scenario: Inspect the normal firmware matrix
- **WHEN** the four existing targets are built
- **THEN** status advertising is enabled only in `tpaktop-corne-dongle`
- **AND** neither peripheral nor settings-reset firmware enables Prospector status advertising

#### Scenario: Receive the configured keyboard name
- **WHEN** Scanner receives and associates a name advertisement with this dongle's status advertisements
- **THEN** it displays `TPAK`, not `Unknown`
- **AND** successful compilation alone is not evidence that the physical Scanner received the name

### Requirement: Status advertisements carry both half batteries
The dongle SHALL fetch peripheral battery levels so Prospector shows the left and right half batteries. Host proxy SHALL be independent of Scanner advertisements. Visible batteries SHALL NOT establish input reliability.

#### Scenario: Build the master matrix
- **WHEN** the master build matrix is used
- **THEN** fetching and proxy are enabled only on the dongle, with the existing artifact filenames
- **AND** the halves and Scanner require no firmware changes

#### Scenario: Verify after a firmware change
- **WHEN** the owner tests cold starts and reconnections
- **THEN** both halves must send keys individually and simultaneously after every connection
- **AND** the owner verifies battery values and left/right mapping separately from connection indicators
- **AND** any connected-but-not-typing half rejects the candidate

### Requirement: Battery reporting preserves persistent pairings and normal behavior
Battery reporting SHALL preserve the keymap, OS profiles, split roles, host profiles, and persistent-settings design. Installation and rollback SHALL use only operational dongle firmware and SHALL NOT require settings reset or bond clearing.

#### Scenario: Roll back a failed dongle image
- **WHEN** a dongle image loses input or otherwise fails acceptance
- **THEN** the owner can reinstall the previous working dongle UF2 without intentionally clearing split or host bonds
