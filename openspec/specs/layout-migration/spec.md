## Purpose

Preserves the tested layout and custom behaviors while moving them to a separate dongle configuration repository with unambiguous source-revision provenance.

## Requirements

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

### Requirement: Longer overlapping combos remain distinguishable
The five four-key combos `cut_combo`, `app_switch_combo`, `task_view_combo`, `numbers_slash_combo`, and `numbers_asterisk_combo` SHALL use an 80 ms timeout while their shorter subsets and all unrelated combos SHALL retain 50 ms.

#### Scenario: Complete a four-key combo after 50 ms
- **WHEN** a shorter subset is fully pressed and the fourth key arrives after 50 ms but before 80 ms from the first press
- **THEN** the four-key combo activates instead of the shorter subset

#### Scenario: Release a shorter subset
- **WHEN** the user completes and releases only the shorter combo without pressing the fourth key
- **THEN** the shorter combo still activates

#### Scenario: Initial state
- **WHEN** the dongle reboots
- **THEN** Graphite is base layer 0 and the volatile OS profile is Windows

### Requirement: Migration does not modify source repositories
The work SHALL modify only `tpaktop-corne-zmk-config`; the view configuration, `nat` configuration, and QMK/Oryx reference MUST remain read-only.

#### Scenario: Audit change boundaries
- **WHEN** the change is ready for review
- **THEN** all commits and the working branch exist only in `tpaktop-corne-zmk-config`

### Requirement: Migration provenance is documented
The documentation SHALL identify the source repository, source commit, migration differences, later intentional keymap extensions, and the subsequent removal of ZMK Studio. Current operating instructions MUST NOT claim that a Studio endpoint or reserved Studio layers remain available.

#### Scenario: Audit provenance
- **WHEN** the owner reads the maintained layout, dongle, OS profile, migration, and test documentation
- **THEN** the documents describe the 13-layer version-controlled layout and do not instruct the owner to connect to or test ZMK Studio

### Requirement: Repository text is English-only
All tracked prose, documentation, OpenSpec artifacts, and source comments SHALL be written in English and MUST NOT contain Cyrillic code points. Russian layout behavior SHALL remain unchanged and SHALL be described using Russian-PC aliases or Latin key names.

#### Scenario: Search the repository before merge
- **WHEN** the working tree is searched across the full Unicode Cyrillic range
- **THEN** no tracked file matches and all Russian-layer bindings remain structurally unchanged
