## REMOVED Requirements

### Requirement: Layer and Studio ordering remains explicit
**Reason**: ZMK Studio and its three reserved layers are being removed, so the ordering contract must end at `SYSTEM_BT=12`.

**Migration**: Keep `SYM_NUM=11` and `SYSTEM_BT=12`, remove `STUDIO_EXTRA_1..3`, and retain the functional nodes in ascending index order.

## ADDED Requirements

### Requirement: Functional layer ordering remains explicit
The keymap constants and Devicetree node order SHALL contain exactly 13 functional layers from `GRAPHITE=0` through `RUSSIAN_SMILES=10`, `SYM_NUM=11`, and `SYSTEM_BT=12`. No Studio-only reserved layer constants or nodes SHALL remain.

#### Scenario: Inspect final layer definitions
- **WHEN** the constants and nodes inside `keymap {}` are compared
- **THEN** every functional node appears in ascending index order, `SYM_NUM` remains at index 11, and `SYSTEM_BT` is the final node at index 12
