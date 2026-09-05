## Context

The target `tpaktop-corne-zmk-config` started at commit `d286351` with a standard three-layer keymap, ZMK v0.3, and a two-half Corne build matrix. Despite the repository name, the matrix already included `nice_view_adapter nice_view`; the displays are retained but limited to local battery/charging and split connection status.

The tested configuration is in read-only `tpaktop-corne-wireless-view-zmk-config` at `master` commit `e7d7c10`. Before this change, neither the source nor target repository had open pull requests. The source contains 15 layers, positional combos, Russian layers, 300 ms Auto Shift, a volatile OS profile, and a root out-of-tree module. That commit is used as a complete baseline rather than as selected fragments.

The official ZMK v0.3 dongle mechanism requires a central shield with mock kscan, a matrix transform, and a physical layout. Both physical halves become BLE peripherals. ZMK Studio and all keymap-dependent behaviors must execute on the central.

## Goals / Non-Goals

**Goals:**

- Isolate the dongle architecture in a separate repository while retaining the working view repository as a rollback path.
- Produce four verifiable UF2 files: dongle, left, right, and settings reset.
- Preserve keymap behavior while changing split topology.
- Use standard ZMK v0.3 mechanisms for the dongle, Studio, and peripheral display.

**Non-Goals:**

- Proprietary 2.4 GHz transport, operation without the dongle, or runtime topology switching.
- A dongle screen, forwarding active layer/OS/host profile to the halves, or a custom display widget.
- Peripheral battery fetching or proxy on the central.
- Fixing overlapping combos, Russian Caps Word, or otherwise changing the current layout.
- Modifying the source view repository, `nat-corne-zmk-config`, or QMK/Oryx.

## Decisions

### 1. Use `nice_nano_v2` as the dongle board

The `tpaktop_corne_dongle` shield is created under `config/boards/shields/tpaktop_corne`. It enables `ZMK_SPLIT_ROLE_CENTRAL=y`, two peripherals, and `BT_MAX_CONN=7`/`BT_MAX_PAIRED=7`: two split links plus five host profiles. The keyboard name remains within the 16-character limit.

A separate XIAO or Prospector board was not selected because no other dongle hardware was specified and `nice_nano_v2` is already the project's supported hardware base in ZMK v0.3.

### 2. Mirror the Corne 6-column topology in the dongle shield

The overlay uses a keyless mock kscan, the exact 12x4 `default_transform` map for 42 positions from the in-tree ZMK v0.3 Corne definition, and the shared `foostan_corne_6col_layout` physical layout. This preserves positional combo indices and gives Studio the complete physical layout.

`config/tpaktop_corne_dongle.keymap` includes the version-controlled `corne.keymap`. A second copy of the 818-line keymap is not created.

### 3. Migrate the keymap as a baseline and separate topology settings

Root `CMakeLists.txt`, `Kconfig`, `zephyr/module.yml`, `dts/`, `include/`, `src/`, `config/corne.keymap`, `config/west.yml`, and user documentation are copied from `e7d7c10`. Older OpenSpec change directories are not copied as active history; the current change records provenance and migration requirements.

`config/corne.conf` becomes peripheral configuration containing radio/debounce and built-in nice!view status settings. Studio is removed from it. `config/tpaktop_corne_dongle.conf` contains central radio and Studio settings. The existing CMake guard already compiles OS behavior sources only for the central.

### 4. Use the built-in nice!view status screen

The `nice_view_adapter nice_view` shields remain on left and right targets. `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y` and the percentage battery widget are selected. On a peripheral, ZMK v0.3 Kconfig dependencies omit layer/output/WPM widgets and include battery plus peripheral connection widgets; no custom nice!view artwork is used.

The ZMK v0.3 nice!view shield already selects `ZMK_DISPLAY_WORK_QUEUE_DEDICATED` by default. After checking upstream Kconfig and display implementation, the option is also set explicitly in `config/corne.conf` so LVGL updates always use a dedicated `k_work_q` and do not depend on future shield defaults.

A custom widget was rejected because it would duplicate upstream code and add maintenance without user value.

### 5. Move Studio to the headless central

The `studio-rpc-usb-uart` snippet is assigned only to the dongle target. The physical layout from decision 2 provides Studio mapping; the three reserved layers remain in the migrated keymap. Peripheral targets do not receive the Studio snippet and are not USB Studio endpoints.

### 6. Build a complete installation set

The matrix contains:

1. `nice_nano_v2 + tpaktop_corne_dongle + studio-rpc-usb-uart`;
2. `nice_nano_v2 + corne_left + nice_view_adapter + nice_view` with a forced peripheral role;
3. the equivalent `corne_right` target;
4. `nice_nano_v2 + settings_reset`.

Each target has a stable `artifact-name`. Dongle battery fetching/proxy remains disabled because of known ZMK v0.3 risks with two peripherals.

### 7. Pass the timestamp to the official reusable workflow

A metadata job generates UTC `YYYYMMDD_HHMM` and exports it as an output. The official `build-user-config.yml@v0.3` reusable workflow receives `archive_name: corne-dongle-firmware_<timestamp>`. This avoids copying or forking the upstream workflow. UF2 filenames inside the archive remain stable.

### 8. Separate automated and hardware validation in documentation

The source layout documents gain explicit provenance and topology sections. A new dongle guide covers reset, UF2 mapping, first pairing, and rollback. The test matrix retains existing `manual pending` rows and adds the three devices, minimal screens, Studio on the dongle, cross-half combos, USB/BLE, and provisioning.

### 9. Force Corne 6 Column on peripheral firmware

Hardware testing on 2026-09-05 after a complete settings reset showed both halves consistently using `five_column_transform`: the right home row produced `TSGYH` instead of `YHAEI`, corresponding to positions 15-19 instead of 18-22; the left half showed the matching shift and mapped an outer key to a service position. The target repository's original `master` has 42 bindings per layer, so it is not a 5x3 template. A second complete reset did not change the result.

The `tpaktop_corne_6col` extension shield, applied after `corne_left` or `corne_right`, sets `foostan_corne_5col_layout` to `status = "disabled"`. A regular user-config overlay was rejected by an actual CI build because ZMK loads it before the in-tree Corne overlay, when that label is not yet defined. The extension shield supplies the required order, leaving `foostan_corne_6col_layout` as the only enabled peripheral physical layout with the existing `default_transform` and right-side `col-offset = 6`. The dongle overlay and version-controlled keymap are unchanged. Device roles and BLE bonds are unchanged, so installing the fix requires reflashing only the two halves without a settings reset.

### 10. Keep repository text in English

All tracked prose, documentation, OpenSpec artifacts, and source comments use English and contain no Cyrillic code points. Russian layout diagrams and expected outputs use Russian-PC alias names or Latin descriptions instead of literal Cyrillic glyphs. Firmware bindings and the host-layout-dependent Russian behavior are unchanged.

This repository-wide policy is preferred over leaving bilingual fragments because it makes review and future maintenance consistent. It is enforced with a full-tree Cyrillic-range search before merge.

## Risks / Trade-offs

- [The actual dongle board differs from `nice_nano_v2`] -> The board is isolated to one matrix entry and documented as the accepted hardware assumption; changing it does not affect keymap or topology specs.
- [Old bonds prevent discovery of both peripherals] -> `settings_reset` is included in the artifact and run on all three devices during initial installation.
- [One half fails to connect at startup] -> Battery fetching/proxy is disabled, the display queue is explicitly dedicated, and the test matrix covers cold boot, reconnection, and both sides.
- [Positional combos change during migration] -> The dongle transform exactly matches the ZMK v0.3 Corne 6-column transform, the keymap comes from a pinned commit, and every layer is structurally checked for 42 bindings.
- [A peripheral selects the alternative in-tree Corne 5-column layout] -> The `tpaktop_corne_6col` extension shield explicitly disables it; both compiled Devicetrees are checked for a single enabled 6-column layout.
- [A peripheral display unexpectedly shows artwork or layer state] -> Build configuration forces the built-in screen and final Kconfig is inspected in Actions.
- [The dongle is lost or fails] -> The halves intentionally do not work independently; the unchanged view repository and documented reset procedure provide rollback.
- [Rare concurrent runs share a minute-level timestamp] -> GitHub separates artifacts by run and the readable timestamp satisfies everyday identification; a run ID is not added to the name.
- [Literal Russian examples become less immediately readable] -> Stable Russian-PC aliases and Latin key names preserve exact mappings without violating the English-only text policy.

## Migration Plan

1. Build and download the timestamped artifact; verify all four UF2 files.
2. Flash `settings-reset-nice-nano-v2.uf2` to the dongle, left, and right devices in turn and allow each image to boot.
3. Flash `tpaktop-corne-dongle.uf2`, `corne-left-peripheral.uf2`, and `corne-right-peripheral.uf2` to their corresponding devices.
4. Start or connect the dongle first, then both halves; check connection indicators.
5. Run USB smoke tests and a ZMK Studio test, then pair BT0 and run BLE smoke tests; validate remaining host profiles independently.
6. For rollback, reset settings on both halves and flash left/right artifacts from the stable view repository.
