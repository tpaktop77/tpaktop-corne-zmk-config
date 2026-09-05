## 1. Migrate the tested baseline

- [x] 1.1 Migrate the keymap, west manifest, and root out-of-tree OS-profile module from `tpaktop-corne-wireless-view-zmk-config@e7d7c10`; verify exact source parity with `sha256sum` and `diff`.
- [x] 1.2 Migrate user-facing layout and test documentation, add target repository provenance, and verify that no text incorrectly describes the old central-left topology as current.

## 2. Dongle topology and device configuration

- [x] 2.1 Add a `tpaktop_corne_dongle` shield for `nice_nano_v2` with mock kscan, a 42-key Corne transform, physical layout, two peripherals, and 7/7 limits; verify the overlay and Kconfig structure against ZMK v0.3.
- [x] 2.2 Connect the shared `corne.keymap` and central-only configuration to the dongle target; verify that Studio and custom OS behaviors belong to the central.
- [x] 2.3 Configure `corne_left` and `corne_right` as BLE peripherals with the built-in nice!view status screen and an explicit dedicated display work queue; verify battery percentage/charging/connection, absence of custom artwork, and absence of the system display queue.
- [x] 2.4 Explicitly keep battery fetching/proxy disabled on the central and inspect final configuration sources for the corresponding Kconfig symbols.
- [x] 2.5 Disable the alternative Corne 5-column physical layout on both peripherals based on hardware evidence; verify compiled Devicetree has only the 6-column layout enabled, no offset on the left, and `col-offset = 6` on the right.

## 3. Build and package firmware

- [x] 3.1 Update `build.yaml` for dongle, left peripheral, right peripheral, and settings reset with unambiguous `artifact-name` values; validate YAML and CMake role arguments.
- [x] 3.2 Move the Studio RPC snippet from the left half to the dongle and verify that peripheral entries have no Studio snippet.
- [x] 3.3 Add a metadata job with a UTC `YYYYMMDD_HHMM` timestamp and pass the timestamped name through the official reusable workflow's `archive_name`; validate GitHub Actions YAML and the expected naming pattern.

## 4. Operational documentation

- [x] 4.1 Update layout, migration, and OS-profile documentation for the dongle central while preserving all migrated layers and behavior descriptions; verify target names and topology are consistent.
- [x] 4.2 Add settings reset, first-flash, host pairing, and rollback instructions with exact mapping for all four UF2 files; verify the sequence against the official ZMK v0.3 dongle guide.
- [x] 4.3 Extend the test matrix for three devices, cold boot/reconnect, both peripheral screens, cross-half combos, Studio on the dongle, USB/BLE, and the timestamped archive; leave hardware rows as `manual pending`.

## 5. Verification and delivery

- [x] 5.1 Run `git diff --check`, structural checks for 42 bindings/15 layers/positional combos, YAML parsing, and `openspec validate migrate-layout-to-dongle --strict`; resolve all errors.
- [x] 5.2 Commit and push the working branch, wait for all four GitHub Actions targets to succeed, and inspect the timestamped artifact contents.
- [x] 5.3 Record run/job identifiers and automated results in the test matrix, repeat static/OpenSpec validation, and check off every completed task.
- [x] 5.4 Open pull request #1 against `master` with a summary, OpenSpec links, source commit, build evidence, provisioning warning, and a list of hardware tests left `manual pending`.
- [x] 5.5 Push the 6-column fix to PR #1, wait for all targets to build successfully, inspect the new timestamped artifact, and leave the repeated hardware layout/combo test as `manual pending`.
- [x] 5.6 Translate all tracked prose, documentation, OpenSpec artifacts, and source comments to English without changing firmware behavior; verify a repository-wide Cyrillic-range search returns no matches, then repeat strict OpenSpec validation and the four-target CI build.
- [x] 5.7 Reconcile the design and delta specs with the approved ZMK v0.3 review fixes for overlapping combos, concurrent combo capacity, Studio behavior metadata, and position-keyed OS-action state.
- [x] 5.8 Set the five overlapping four-key combos to 80 ms and configure eight concurrently pressed combos on the dongle; verify shorter and unrelated combo timeouts remain 50 ms.
- [x] 5.9 Add Studio parameter metadata to `&os_set` and `&os_action`, and track active OS-action keycodes independently by event position; verify duplicate actions cannot interfere with one another and release uses the press-time keycode.
- [x] 5.10 Run static checks, strict OpenSpec validation, and all four GitHub Actions targets; inspect the timestamped artifact and leave hardware timing/Studio/concurrency checks as manual pending.
