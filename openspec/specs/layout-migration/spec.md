## Purpose

Preserves the tested layout and custom behaviors while moving them to a separate dongle configuration repository with unambiguous source-revision provenance.

## Requirements

### Requirement: The tested layout is migrated from a pinned revision
The target configuration SHALL reproduce the version-controlled keymap and custom ZMK module from `tpaktop-corne-wireless-view-zmk-config` commit `e7d7c10` without functional simplification, except for documented review-driven combo and custom-behavior hardening.

#### Scenario: Layout contents after migration
- **WHEN** the source revision and dongle configuration are compared
- **THEN** Graphite, QWERTY, Russian, functional layers, Russian auxiliary layers, positional combos, Auto Shift, macros, and OS-aware actions are present with the same bindings, with timing differences limited to the documented five overlapping four-key combos

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
The documentation SHALL identify the source repository, source commit, and intentional differences in the dongle configuration.

#### Scenario: Audit provenance
- **WHEN** the owner opens the migration documentation
- **THEN** it identifies `tpaktop-corne-wireless-view-zmk-config@e7d7c10` and lists differences limited to topology, display, Studio, build, provisioning, documentation language, and review-driven combo/custom-behavior hardening

### Requirement: Repository text is English-only
All tracked prose, documentation, OpenSpec artifacts, and source comments SHALL be written in English and MUST NOT contain Cyrillic code points. Russian layout behavior SHALL remain unchanged and SHALL be described using Russian-PC aliases or Latin key names.

#### Scenario: Search the repository before merge
- **WHEN** the working tree is searched across the full Unicode Cyrillic range
- **THEN** no tracked file matches and all Russian-layer bindings remain structurally unchanged
