## MODIFIED Requirements

### Requirement: The tested layout is migrated from a pinned revision
The target configuration SHALL preserve the version-controlled keymap and custom ZMK module migrated from `tpaktop-corne-wireless-view-zmk-config` commit `e7d7c10`, except for documented review-driven hardening and subsequent version-controlled extensions. The tested shared `SYM_NUM` layer SHALL remain at index 11, `SYSTEM_BT` SHALL remain at index 12, and the keymap SHALL contain exactly 13 active nodes after Studio-only reserved layers are removed.

#### Scenario: Layout contents after migration
- **WHEN** the keymap before and after this change is compared
- **THEN** all 13 functional layers, bindings, positional combos, Auto Shift, macros, custom behaviors, and timings remain unchanged while only the three Studio reserved nodes are absent

#### Scenario: Ordered layer definitions
- **WHEN** layer constants are compared with nodes inside `keymap {}`
- **THEN** both list `GRAPHITE=0` through `SYM_NUM=11` and `SYSTEM_BT=12` in the same ascending order with no indices above 12

#### Scenario: Unrelated behavior remains stable
- **WHEN** the Studio-removal implementation diff is reviewed
- **THEN** functional bindings, macros, combos, custom behaviors, timings, dongle topology, BLE, USB keyboard HID, display, and split configuration remain unchanged

### Requirement: Migration provenance is documented
The documentation SHALL identify the source repository, source commit, migration differences, later intentional keymap extensions, and the subsequent removal of ZMK Studio. Current operating instructions MUST NOT claim that a Studio endpoint or reserved Studio layers remain available.

#### Scenario: Audit provenance
- **WHEN** the owner reads the maintained layout, dongle, OS profile, migration, and test documentation
- **THEN** the documents describe the 13-layer version-controlled layout and do not instruct the owner to connect to or test ZMK Studio
