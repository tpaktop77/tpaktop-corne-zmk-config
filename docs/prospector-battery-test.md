# Prospector peripheral-battery experiment

## Source and scope

This test branch is `20261014__test_prospector_peripheral_batteries`, created from checked `master` commit `35ba98055905792a91f3e29ff203691781f8da2f`. The previous branch's committed tree matches that master tree exactly; moving to master is not itself a keymap or reliability fix.

The existing `build.yaml` and GitHub workflow are unchanged. This branch enables fetching and host-side battery proxy directly in `config/tpaktop_corne_dongle.conf` so the normal pipeline actually builds the requested experiment. Master keeps both disabled. The separately selectable fragment in `config/experiments/` reproduces these settings; it is not automatically loaded.

Keymap, OS behaviors, split topology, host profiles, half firmware configuration, Scanner repository, and dependencies are unchanged from master. Only the dedicated central advertises Prospector status; Scanner remains an independent observer, never a split member.

## Current hardware evidence

The owner tested the previous local candidate and reported:

- Battery values began appearing on Prospector.
- Firmware was glitchy and did not behave like the expected layers/settings.

That local candidate FAILED reliability acceptance. The subsequent GitHub-built fetching-only commit `6c01bea6d9c4d8112d42b2ab301f9f353b829262` passed all four targets in [run 38519017685](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/38519017685), and the owner reported it installed and working. Complete mapping/update/cold-boot acceptance is still pending; that report does not establish the cause of the earlier symptoms or validate the newly requested proxy yet.

The separate `Unknown` problem is unresolved. Before changes, `TPAK` was present in the generated dongle configuration and ELF. That does not prove which image was physically installed or which name packets Scanner received.

## Configuration

Effective dongle settings in this test branch:

```conf
CONFIG_ZMK_STATUS_ADVERTISEMENT=y
CONFIG_ZMK_STATUS_ADV_KEYBOARD_NAME="TPAK"
CONFIG_ZMK_STATUS_ADV_CENTRAL_SIDE="AUX"
CONFIG_PROSPECTOR_EXPECTED_PERIPHERAL_COUNT=2
CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING=y
CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY=y
```

AUX works without fetching; fetching supplies the half battery percentages. Data path: peripheral Battery Service -> central fetching -> `zmk_peripheral_battery_state_changed` -> Prospector cache -> status advertisement -> Scanner. Default AUX mapping uses peripheral slot 0 for Left and slot 1 for Right. Proxy separately consumes the same events for a host-facing BLE Battery Service, not for Prospector.

The owner explicitly requested computer reporting for [zmk-battery-center](https://github.com/kot149/zmk-battery-center). Its README requires fetching and proxy for split keyboards and a Bluetooth connection to the computer. Its BLE code iterates all Battery Services/levels and reads user descriptions. Pinned ZMK `app/src/split/bluetooth/central_bas_proxy.c` generates separate levels labelled `Peripheral 0` and `Peripheral 1`, not an average. Both existing half builds already enable `BT_BAS` and `ZMK_BATTERY_REPORTING`; no half configuration changes are needed. USB-only HID does not carry this BLE Battery Service, and OS built-in UI support for multiple levels is not guaranteed.

## ZMK v0.3 compatibility evidence

Pinned dependencies remain:

- ZMK v0.3: `edf5c0814fd3ea202e43aad2d68fd32e882a518c`.
- Zephyr 3.5.0: `dacab4875df72109b96cc8977547a0dc04875bcd`.
- Prospector module v2.2.3: `72a71aeea816eb0f86ffc5b108b267076ce5f0af`.

[ZMK #3156](https://github.com/zmkfirmware/zmk/issues/3156) reports a separate dongle and two peripherals where a connected half loses key input after incomplete GATT discovery. Its reported baseline was ZMK main, not this exact v0.3.

[PR #3216](https://github.com/zmkfirmware/zmk/pull/3216), merged as [9490391e1e4010c83291d437b7f9a71ace244581](https://github.com/zmkfirmware/zmk/commit/9490391e1e4010c83291d437b7f9a71ace244581), fixes the buffer setting for newer Zephyr. Our Zephyr still sizes ATT requests using `BT_L2CAP_TX_BUF_COUNT`, already raised to 5 by pinned ZMK. Blindly backporting that Kconfig change is unjustified.

Residual risk remains in pinned `app/src/split/bluetooth/central.c`: battery and position subscriptions share CCC discovery state, start during the characteristic walk, and battery discovery starts an immediate read; discovery completion does not require a position-state handle. [PR #3411](https://github.com/zmkfirmware/zmk/pull/3411) proposes deeper discovery changes but is not a validated v0.3 backport. No patch, buffer tuning, or upgrade is included. The owner's symptoms have not been attributed conclusively to this mechanism.

## GitHub build and firmware provenance

Use the existing [Build ZMK firmware workflow](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/workflows/build.yml) and select this branch. A push to the branch triggers the same four-target pipeline; no new target, workflow, or archive format is added.

| Existing target | Artifact | Device |
|---|---|---|
| Dongle | `tpaktop-corne-dongle.uf2` | Dedicated nice_nano_v2 central |
| Left | `corne-left-peripheral.uf2` | Left half; validation only, no reflash needed |
| Right | `corne-right-peripheral.uf2` | Right half; validation only, no reflash needed |
| Reset | `settings-reset-nice-nano-v2.uf2` | Compile only; DO NOT FLASH for this experiment |

The timestamped archive remains `corne-dongle-firmware_YYYYMMDD_HHMM.zip`. Identify a candidate by its GitHub branch, commit, and run, not just the stable dongle filename: a master build uses the same filename with fetching off. Download firmware only from the corresponding successful GitHub run; previous local UF2 files are not the handoff for this branch.

For rollback use the owner's last verified working dongle image, or an independently verified successful master build. A repository build was never proven to match the owner's previously installed image. No settings reset, host-profile clearing, or split-bond reset is required. No half or Scanner reflash is required. Do not install anything automatically.

## Validation status and warnings

The previous local phase compiled all four targets plus fetching/USB-log variants successfully. It verified `TPAK/AUX`, central-only module membership, peripheral Battery Services, and a control/candidate Kconfig difference limited to fetching plus its two-event queue. These are historical build results, NOT GitHub validation of the new branch and NOT a passed hardware test.

Fetching-only commit `6c01bea` completed all four GitHub jobs successfully. The subsequent proxy change requires its own exact pushed commit to complete all four build jobs; its host-side runtime check remains pending. Existing warnings from the earlier pinned build were not suppressed:

- Deprecated `config/boards` and `NRF_STORE_REBOOT_TYPE_GPREGRET`.
- Unknown `tpak` vendor prefix for existing OS behavior bindings.
- Prospector `SYS_INIT` signature mismatch with Zephyr 3.5 and unused `wpm_start_time`.
- Peripheral `ZMK_USB=y` defaults resolving to n because the halves are peripherals.
- Reset-image zero-size keymap initializer/array-bounds warnings.

The candidate added no warning messages compared with its local control. GitHub warnings must be checked independently. A passing compiler does not establish runtime safety.

## Hardware checklist

Initial local reliability result: FAILED; subsequent GitHub fetching-only candidate: owner-reported working. Do not promote battery changes into master without complete acceptance evidence.

- Both halves must type separately and simultaneously after every connection, not merely show connected.
- Cold-start all three together; halves first then dongle; dongle first then halves; alternate half order; repeat cold starts.
- Cycle each half separately and reboot dongle while halves stay powered; test existing USB and BLE host profiles without new pairing.
- Verify both battery values against local half displays, correct Left/Right mapping, and updates during genuine percentage changes.
- With the computer connected to the dongle over Bluetooth, verify `zmk-battery-center` discovers `Peripheral 0` and `Peripheral 1`, reads both values, and receives updates. Check USB-only behavior separately; do not expect BLE BAS through USB.
- Record stale/disconnected display behavior with one half off; verify fresh values and input after its return.
- Reboot Scanner with dongle powered and dongle with Scanner powered; verify battery recovery.
- Record `TPAK` versus `Unknown` after cold boots, independent reboots, and repeated active/idle advertisements.
- Reject any connected-but-not-typing half, missing expected layer/settings, lost/repeated keys, or other input regression; restore verified working firmware without resetting bonds.

OpenSpec change: `test-prospector-peripheral-batteries`. It remains open until reliability is resolved; no PR or automatic flashing is part of this work.
