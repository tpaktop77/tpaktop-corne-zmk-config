# Spec Delta

## Purpose

Defines the dedicated dongle's status broadcasts for an independent Prospector Scanner and the boundaries of an optional peripheral-battery experiment.

## ADDED Requirements

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

### Requirement: Battery fetching is an explicitly selected experiment
An explicitly selected test branch SHALL fetch peripheral battery levels without host-side proxying using the existing pipeline and filenames. Branch, commit, and run SHALL identify test artifacts. Neither compilation nor visible batteries SHALL establish reliable keyboard input.

#### Scenario: Build without selecting the experiment
- **WHEN** the master build matrix is used
- **THEN** fetching and proxy remain disabled on the dongle

#### Scenario: Build the opt-in test
- **WHEN** the owner explicitly selects the experimental branch
- **THEN** fetching is enabled, proxy remains disabled, and existing filenames are preserved and branch/commit/run identify the test
- **AND** the halves and Scanner require no firmware changes for this experiment

#### Scenario: Evaluate the test
- **WHEN** the owner tests cold starts and reconnections
- **THEN** both halves must send keys individually and simultaneously after every connection
- **AND** the owner verifies battery values and left/right mapping separately from connection indicators
- **AND** any connected-but-not-typing half rejects the candidate

### Requirement: Testing preserves persistent pairings and normal behavior
The experiment SHALL preserve the keymap, OS profiles, split roles, host profiles, and persistent-settings design. Installation and rollback SHALL use only operational dongle firmware and SHALL NOT require settings reset or bond clearing.

#### Scenario: Roll back a failed experiment
- **WHEN** the battery test loses input or otherwise fails acceptance
- **THEN** the owner can reinstall the normal dongle UF2 without intentionally clearing split or host bonds
