## MODIFIED Requirements

### Requirement: The tested layout is migrated from a pinned revision
The target configuration SHALL preserve the version-controlled keymap and custom ZMK module migrated from `tpaktop-corne-wireless-view-zmk-config` commit `e7d7c10`, except for documented review-driven hardening and subsequent version-controlled extensions. The shared `SYM_NUM` layer SHALL be treated as such an extension and MUST NOT alter unrelated migrated bindings or behaviors.

#### Scenario: Layout contents after migration
- **WHEN** the source revision and current dongle configuration are compared
- **THEN** Graphite, QWERTY, Russian, functional layers, Russian auxiliary layers, positional combos, Auto Shift, macros, and OS-aware actions remain present, while `SYM_NUM` is documented as an additional shared layer

#### Scenario: Unrelated behavior remains stable
- **WHEN** the `SYM_NUM` implementation diff is reviewed
- **THEN** existing bindings differ only at position 39 on `SYMBOLS` and `RUSSIAN_SYMBOLS`, and macros, combos, custom behaviors, timings, Studio configuration, and build configuration are unchanged

### Requirement: Migration provenance is documented
The documentation SHALL identify the source repository, source commit, migration differences, and later intentional keymap extensions.

#### Scenario: Audit provenance
- **WHEN** the owner opens the migration and layout documentation
- **THEN** it identifies `tpaktop-corne-wireless-view-zmk-config@e7d7c10`, preserves the documented migration differences, and describes the shared `SYM_NUM` layer as a later version-controlled extension
