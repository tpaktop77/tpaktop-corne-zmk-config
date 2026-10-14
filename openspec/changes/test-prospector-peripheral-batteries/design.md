# Design

## Context

See proposal.md for motivation and scope. The test branch `20261014__test_prospector_peripheral_batteries` starts at checked master `35ba98055905792a91f3e29ff203691781f8da2f`. Its base tree matches the old branch at `da36472b66cde4bbc9cd7b50980472c9a467e031`; changing branches is not a keymap or runtime fix. The default branch is `master`; the separate Scanner worktree is not an implementation target.

Pinned sources are ZMK v0.3 `edf5c0814fd3ea202e43aad2d68fd32e882a518c`, Zephyr `dacab4875df72109b96cc8977547a0dc04875bcd`, and Prospector module v2.2.3 `72a71aeea816eb0f86ffc5b108b267076ce5f0af`.

### Evidence before behavioral changes

- The existing dongle was built successfully before edits. Its final `.config` has status advertising enabled, `TPAK`, `AUX`, two expected peripherals, and fetching disabled. `strings zephyr/zmk.elf` contains `TPAK`; this is build evidence, not an over-the-air capture or proof of physically installed firmware.
- Status path: peripheral BAS notifications/reads -> ZMK split transport battery event -> central's indexed battery cache -> `zmk_peripheral_battery_state_changed` -> Prospector's peripheral battery cache -> packed 26-byte manufacturer status payload -> Scanner.
- With fetching disabled, this peripheral event/data path is absent, explaining missing real half percentages. In AUX mode the module puts peripheral index 0 in the primary battery field (Left) and index 1 in the first peripheral battery field (Right). Physical mapping remains a hardware check.
- Proxy adds a host-facing Battery Service and is not consumed by the Prospector listener. It is unnecessary for Scanner, but the owner now explicitly requests it for zmk-battery-center. Pinned central_bas_proxy.c creates separate readable/notifiable Battery Levels with user descriptions Peripheral 0 and Peripheral 1. Existing halves already have BAS/local reporting enabled. The app requires a BLE host connection and enumerates all battery characteristics/descriptions; USB-only HID does not carry this service.
- Name path: the configured string initializes the module's separate complete-local-name advertising data (AD type 0x09). Scanner caches names by BLE address/type and looks up that name on a subsequent manufacturer status packet. Its cache miss returns `Unknown`. The current hardware's reason for missing association is unproven; this experiment does not alter that path.

### Exact v0.3 compatibility assessment

[Issue #3156](https://github.com/zmkfirmware/zmk/issues/3156) reports two connected peripherals with one silently missing key input after discovery ends before finding position state. Its reported test is ZMK main, not this pinned v0.3 commit.

[PR #3216](https://github.com/zmkfirmware/zmk/pull/3216), merged as [`9490391e1e4010c83291d437b7f9a71ace244581`](https://github.com/zmkfirmware/zmk/commit/9490391e1e4010c83291d437b7f9a71ace244581), changes the newer-Zephyr buffer setting to `BT_ATT_TX_COUNT`. Our Zephyr's `subsys/bluetooth/host/att.c` instead allocates its request slab with `CONFIG_BT_L2CAP_TX_BUF_COUNT`; pinned ZMK already raises that value to 5. Thus this particular wrong-symbol regression does not establish that our v0.3 is affected, and cherry-picking this Kconfig change is not a justified backport.

There is nevertheless concrete residual risk in pinned `app/src/split/bluetooth/central.c`: position and battery subscriptions share `sub_discover_params`, start CCC discovery during the characteristic walk, and battery discovery immediately starts a read. Discovery completion does not require a position-state handle. These overlapping asynchronous operations justify keeping default fetching disabled; they do not prove this physical Corne reproduces the failure.

[PR #3411](https://github.com/zmkfirmware/zmk/pull/3411) proposes deferred subscriptions and separate discovery state, but was open in the inspected upstream source and is not a validated v0.3 backport. No source patch or ZMK upgrade is included. The owner's later authorization permits a bounded experiment, not a declaration that the old reliability concern is fixed.

## Goals / Non-Goals

Goals: publish the isolated branch using the existing GitHub pipeline, preserve master keymap/settings, and record the earlier failed hardware test honestly.

Non-goals: production promotion, source backports, a Scanner/UI fix, repairing `Unknown`, new bonds, or changing host behavior beyond the explicitly requested BLE Battery Service.

## Decisions

1. Select the experiment by branch and enable fetching in that branch's dongle `.conf` so the existing pipeline actually builds it. Master stays fetching n. Retain the separate fragment for explicit reproduction; do not auto-load it or change the pipeline/matrix.
2. Fetching is already y in this branch. Now enable proxy y on the dongle and in the equivalent optional fragment for the owner's BLE host app; master stays unchanged. Retain peripheral mappings and all advertising options. Do not tune buffers, TX power, or timing. The app should read Peripheral 0/1; OS display support and stale GATT caches remain runtime checks, not reasons to clear bonds automatically.
3. Commit/push only the test branch and wait for all four existing GitHub matrix targets. Keep archive format and UF2 names; distinguish the experiment by branch/commit/run. Half/reset outputs are validation only, not reflash instructions.
4. Prior local and USB-log builds are historical evidence only. Initial local reliability FAILED. Fetching-only commit 6c01bea completed all four targets in GitHub run 38519017685; the owner subsequently reported it installed and working. Full acceptance is still pending and the proxy change requires its own four-target GitHub run. Do not build locally or hand out local UF2s.

## Risks / Trade-offs

- A half can connect without typing -> require input from both halves after every boot/reconnect; reject the test immediately on failure and offer the normal dongle rollback.
- Successful compilation can be mistaken for reliability -> record the failed earlier test, keep unresolved acceptance checks open, and keep master fetching disabled.
- Logging can mask a race or drop early messages -> test without logging first; use paired diagnostic variants only for investigation and identify missing logs as inconclusive.
- Battery labels can use an unexpected persisted peripheral-slot order -> compare with each half's local display; do not reset bonds or silently remap.
- Scanner can retain a last-known battery while a half is off -> record staleness instead of requiring a live value from an unpowered device.

## Migration Plan

Provide the successful GitHub run/archive with branch and commit provenance, not a recommendation to repeat the failed hardware test. Do not flash devices automatically. Keep an independent input device available. On any input regression, restore the owner's last verified working dongle firmware without settings reset; leave the halves and Scanner unchanged. Production promotion is outside this change.
