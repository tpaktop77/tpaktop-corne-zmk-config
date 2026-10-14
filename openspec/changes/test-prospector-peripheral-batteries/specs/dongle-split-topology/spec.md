# Spec Delta

## MODIFIED Requirements

### Requirement: Peripheral battery retrieval on the central is deferred
Master ZMK v0.3 dongle firmware MUST keep fetching and proxy disabled pending acceptance. An explicitly selected test branch SHALL be permitted to enable fetching and owner-requested host battery proxy on the dongle using the existing pipeline. Branch, commit, and run SHALL identify test firmware.

#### Scenario: Audit central configuration
- **WHEN** the master dongle configuration is inspected
- **THEN** fetching and proxy for split-peripheral battery levels are disabled

#### Scenario: Audit the experimental central configuration
- **WHEN** the owner explicitly selects the battery-fetching test branch
- **THEN** only the dongle enables fetching and host battery proxy
- **AND** this does not promote fetching into master or claim an upstream compatibility fix

#### Scenario: Gate production enablement
- **WHEN** production battery reporting is considered
- **THEN** it requires a separate evidence-backed decision after source review and successful two-peripheral cold-start/reconnection/input testing

## ADDED Requirements

### Requirement: Host receives peripheral batteries through the dongle
The test dongle SHALL expose a readable and notifiable BLE Battery Level for each of its two peripherals through battery proxy. A host app SHALL access them through the existing dongle BLE connection, not by connecting to the halves. USB-only HID SHALL NOT be represented as transporting this BLE service.

#### Scenario: Computer battery monitoring
- **WHEN** the computer is connected to the proxy-enabled dongle over Bluetooth
- **THEN** a compatible app can discover the two Battery Levels labelled Peripheral 0 and Peripheral 1
- **AND** the halves and Scanner do not require reflashing or changed roles

#### Scenario: Preserve pairing while adding BAS
- **WHEN** the dongle firmware is updated to add the proxy service
- **THEN** split and host bonds are not intentionally cleared and settings_reset is not required
- **AND** any stale host service discovery is investigated without automatically deleting bonds
