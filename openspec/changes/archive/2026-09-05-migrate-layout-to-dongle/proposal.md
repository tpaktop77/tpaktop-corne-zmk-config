## Why

The current working layout lives in a separate Corne repository with nice!view and uses the left half as the central. An independent dongle configuration is needed to preserve the tested layout, move central functions to a dedicated `nice_nano_v2`, and leave the stable source repository unchanged.

## What Changes

- Migrate the version-controlled keymap, positional combos, Russian layers, Auto Shift, OS profile, and custom ZMK module from `tpaktop-corne-wireless-view-zmk-config` at pinned source commit `e7d7c10`.
- Add a headless dongle shield for `nice_nano_v2`; it becomes the only split central and owns keymap/HID processing, five host Bluetooth profiles, the volatile OS profile, and ZMK Studio.
- Build both Corne halves as BLE peripherals with `nice_view_adapter nice_view`.
- Switch each half's nice!view to the built-in peripheral status screen: local battery/charging and dongle connection state, without layer status or decorative artwork.
- Keep peripheral battery fetching and proxy disabled on the ZMK v0.3 dongle.
- Add a separate `settings_reset` build and document the required reset and re-pair procedure for all three devices during initial migration.
- Add a UTC timestamp in `YYYYMMDD_HHMM` format to the merged firmware artifact name while keeping UF2 filenames stable and unambiguous.
- Preserve three Studio reserved layers and move Studio RPC from the left half to the dongle.
- Keep all repository prose, documentation, OpenSpec artifacts, and source comments in English without Cyrillic code points; Russian layout bindings remain functionally unchanged.
- **BREAKING**: the dongle firmware cannot operate without the dongle and requires clearing old split and host bonds before first use.
- Do not modify `tpaktop-corne-wireless-view-zmk-config`, `nat-corne-zmk-config`, or `oryx-with-custom-qmk`.

## Capabilities

### New Capabilities

- `layout-migration`: exact migration of the current layout and custom OS module from the stable view repository at a verifiable source commit, including an English-only repository text policy.
- `dongle-split-topology`: `nice_nano_v2` dongle as central with two Corne halves as BLE peripherals.
- `peripheral-status-display`: minimal nice!view status on each half with only local power and split connection state.
- `central-services`: keymap, Bluetooth host profiles, OS profile, and ZMK Studio execution on the dongle.
- `firmware-packaging`: three operational UF2 files, one reset UF2, and a merged timestamped archive.
- `dongle-provisioning`: safe settings reset, flashing, and re-pairing sequence.

### Modified Capabilities

None. The target repository does not yet contain baseline OpenSpec capabilities.

## Impact

- Target repository: `tpaktop-corne-zmk-config`.
- Read-only source configuration: `tpaktop-corne-wireless-view-zmk-config@e7d7c10`.
- Affected areas include `build.yaml`, the GitHub Actions workflow, `config/`, the root out-of-tree ZMK module, a new shield under `config/boards/shields/`, documentation, and OpenSpec artifacts.
- The implementation uses pinned ZMK v0.3 and its standard BLE dongle mechanism; it adds no external repositories or runtime dependencies.
- Hardware validation requires one `nice_nano_v2` dongle, two Corne halves with nice!view, and USB/BLE testing.
