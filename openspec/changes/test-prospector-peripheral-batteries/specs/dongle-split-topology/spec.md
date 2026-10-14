# Spec Delta

## MODIFIED Requirements

### Requirement: Peripheral battery retrieval on the central is deferred
Master ZMK v0.3 dongle firmware MUST keep fetching disabled pending reliability evidence. An explicitly selected test branch SHALL be permitted to enable fetching using the existing pipeline. Proxy MUST remain disabled everywhere; branch, commit, and run SHALL distinguish test firmware despite preserved filenames.

#### Scenario: Audit central configuration
- **WHEN** the master dongle configuration is inspected
- **THEN** fetching and proxy for split-peripheral battery levels are disabled

#### Scenario: Audit the experimental central configuration
- **WHEN** the owner explicitly selects the battery-fetching test branch
- **THEN** only the dongle enables fetching and battery proxy remains disabled
- **AND** this does not promote fetching into master or claim an upstream compatibility fix

#### Scenario: Gate production enablement
- **WHEN** production battery reporting is considered
- **THEN** it requires a separate evidence-backed decision after source review and successful two-peripheral cold-start/reconnection/input testing
