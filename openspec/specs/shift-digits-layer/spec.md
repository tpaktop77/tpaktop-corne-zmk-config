# shift-digits-layer Specification

## Purpose
Defines one shared Shift Digits layer that exposes the shifted digit row from either English or Russian Symbols without duplicating host-layout-specific layers.

## Requirements

### Requirement: Shared Shift Digits layer
The keymap SHALL define one `SYM_NUM` layer at index 11 with display name `Shift Digits`. The same layer SHALL be reached from both `SYMBOLS` and `RUSSIAN_SYMBOLS`; separate language-specific Shift Digits layers MUST NOT be created.

#### Scenario: Activate from English Symbols
- **WHEN** the user holds position 37 to activate `SYMBOLS`, keeps it held, and then holds position 39
- **THEN** the shared `SYM_NUM` layer becomes active

#### Scenario: Activate from Russian Symbols
- **WHEN** the user holds position 37 to activate `RUSSIAN_SYMBOLS`, keeps it held, and then holds position 39
- **THEN** the same shared `SYM_NUM` layer becomes active

### Requirement: Position 39 retains Tab on tap
Position 39 on `SYMBOLS` and `RUSSIAN_SYMBOLS` SHALL send `TAB` on tap and activate `SYM_NUM` on hold. The existing global `&lt` timing and settings MUST remain unchanged.

#### Scenario: Tap position 39
- **WHEN** `SYMBOLS` or `RUSSIAN_SYMBOLS` is active and the user taps position 39
- **THEN** the host receives Tab and `SYM_NUM` does not remain active

#### Scenario: Hold position 39
- **WHEN** `SYMBOLS` or `RUSSIAN_SYMBOLS` is active and the user holds position 39 according to the existing layer-tap behavior
- **THEN** `SYM_NUM` remains active until position 39 is released

### Requirement: Home row contains shifted digits
On `SYM_NUM`, positions 13–17 SHALL send `LS(N1)` through `LS(N5)`, and positions 18–22 SHALL send `LS(N6)` through `LS(N0)`. Positions 12 and 23 and every other body position 0–35 MUST be `&none`; only thumb positions 36–41 SHALL be `&trans`.

#### Scenario: Left home row
- **WHEN** `SYM_NUM` is active and the user presses positions 13, 14, 15, 16, and 17
- **THEN** the host receives Shift+1, Shift+2, Shift+3, Shift+4, and Shift+5 respectively

#### Scenario: Right home row
- **WHEN** `SYM_NUM` is active and the user presses positions 18, 19, 20, 21, and 22
- **THEN** the host receives Shift+6, Shift+7, Shift+8, Shift+9, and Shift+0 respectively

#### Scenario: All other positions
- **WHEN** `SYM_NUM` is active
- **THEN** body positions outside 13–22 send nothing and all six thumb positions resolve through lower active layers

### Requirement: Layer and Studio ordering remains explicit
The keymap constants and Devicetree node order SHALL be `RUSSIAN_SMILES=10`, `SYM_NUM=11`, `SYSTEM_BT=12`, and `STUDIO_EXTRA_1..3=13..15`. ZMK Studio support and the three reserved layers MUST remain present.

#### Scenario: Inspect layer definitions
- **WHEN** the constants and nodes inside `keymap {}` are compared
- **THEN** every node appears in ascending index order and the three reserved Studio nodes follow `SYSTEM_BT`
