## Purpose

Creates a reproducible firmware set for three devices plus a reset image in an automatically timestamped and easily distinguishable GitHub Actions archive.

## Requirements

### Requirement: The workflow builds the complete firmware set
Every workflow run SHALL build the dongle central, `corne_left` peripheral, `corne_right` peripheral, and one compatible `settings_reset` image for `nice_nano_v2`.

#### Scenario: Successful build
- **WHEN** a push, pull request, or manual dispatch starts the workflow
- **THEN** all four targets complete West/Kconfig/Devicetree builds and are included in one artifact

#### Scenario: One target fails
- **WHEN** any required target fails to build
- **THEN** the workflow fails and the change is not considered ready to flash

### Requirement: UF2 files have stable names
UF2 files inside the merged archive SHALL have stable names that unambiguously distinguish dongle, left, right, and settings reset images.

#### Scenario: Inspect archive contents
- **WHEN** the user extracts the artifact
- **THEN** each UF2 destination can be determined from its filename without manual renaming

### Requirement: The archive name contains a UTC timestamp
The merged artifact name SHALL contain the build start time in UTC using `YYYYMMDD_HHMM` format.

#### Scenario: Download two builds
- **WHEN** the user downloads artifacts from different workflow runs
- **THEN** the archives have distinct timestamped names in the form `corne-dongle-firmware_YYYYMMDD_HHMM.zip`
