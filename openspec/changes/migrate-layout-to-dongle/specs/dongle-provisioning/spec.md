## Purpose

Defines a safe and repeatable transition from old split bonds to the dongle topology, including recovery from pairing failures.

## ADDED Requirements

### Requirement: Clear bonds on all devices before first installation
The documentation SHALL require flashing `settings_reset` to the dongle, left half, and right half before installing the dongle firmware set.

#### Scenario: First migration to dongle topology
- **WHEN** the user migrates from the old central-left firmware
- **THEN** the user first boots reset firmware on all three `nice_nano_v2` devices and then flashes each corresponding operational UF2

### Requirement: The procedure distinguishes all three operational images
The documentation SHALL map each UF2 to its physical device and describe starting both halves after the dongle.

#### Scenario: Install the operational set
- **WHEN** reset is complete
- **THEN** the dongle UF2 is installed on the dongle, the left UF2 on the left half, and the right UF2 on the right half, after which both peripherals connect to the central

### Requirement: Host pairing uses the dongle
After migration, USB/BLE host connections and `BT0`-`BT4` SHALL belong to the dongle rather than either half.

#### Scenario: Pair a computer over BLE
- **WHEN** the user selects an unused profile and pairs the keyboard with a host
- **THEN** the host creates a bond with the dongle while both halves remain split peripherals

### Requirement: Rollback remains available
The documentation SHALL describe returning to stable firmware from the view repository through another settings reset.

#### Scenario: Stop using the dongle
- **WHEN** the user chooses to return to the central-left topology
- **THEN** the user clears bonds, flashes the previous left/right firmware from the unchanged view repository, and repeats host pairing
