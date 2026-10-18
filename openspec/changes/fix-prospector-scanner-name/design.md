# Design

## Context

Scanner (`status_scanner.c`) caches names by BLE address. It looks the name up when a Prospector status packet arrives, and shows `Unknown` on a miss. The dongle sends status in AD and the name either in SCAN_RSP or in a periodic name-only AD packet.

The owner observed with nRF Connect (iPhone) that the status advertisement is `Connectable: No`, and that a new device entry appears after rebooting the dongle and halves.

## Root causes (module v2.2.3, Zephyr 3.5)

1. **Name-in-AD never sent.** Own advertising used `BT_LE_ADV_OPT_USE_NAME`. In Zephyr `le_adv_update()` (`subsys/bluetooth/host/adv.c:798`), any AD/SD that already contains a name returns `-EINVAL` when USE_NAME is set. The module logs this only at debug level. The only remaining name path was SCAN_RSP, which the module author notes rarely reaches the scanner while the dongle radio serves its connections.
2. **Address changes.** Non-connectable advertising without `BT_LE_ADV_OPT_USE_IDENTITY` gets a fresh NRPA from `bt_id_set_adv_own_addr()` on every `bt_le_adv_start()`, because `BT_PRIVACY=n`. Upstream commit 1a38fb1 assumed that dropping `USE_NRPA` meant the identity address would be used. Every restart (reboot, peripheral reconnect, sleep, profile change) invalidates the scanner's per-address name.
3. **Stuck burst advertisement.** A burst advertisement started while the split was partial is non-scannable and was only ever updated, never restarted, after the split connected. In that state SCAN_RSP was unavailable.

## Decisions

- Own advertising drops USE_NAME and passes an explicit `name_sd` (complete name) as SCAN_RSP. Every own-ADV start and update passes it, because a NULL SD clears SCAN_RSP. The ZMK piggyback path is unchanged, since ZMK's own advertisement still uses USE_NAME.
- MODE 2 and burst advertising use `BT_LE_ADV_OPT_USE_IDENTITY`. This also avoids the controller random-address tainting that motivated 1a38fb1. Connectable proxy already used the identity address.
- Restart a running burst advertisement with the regular params once the split is fully connected.
- Pin the fork by commit hash, not branch name, so builds are reproducible.

## Verification

- The patched file passes a syntax-only compile against the pinned Zephyr/ZMK headers and the dongle's generated config. No local toolchain was available, so the full build runs in GitHub Actions.
- Hardware: the Scanner shows `TPAK` while the dongle is connected to a BLE host, and still does after rebooting the dongle and power-cycling a half. In nRF Connect, the dongle stays one device entry across reboots. Input, layers, batteries, and host reconnection to bonded profiles are unaffected.

## Risks

- Advertising with the identity address while connected could affect host reconnection. Mitigation: verify reconnection to bonded profiles, and roll back to the master dongle image if it regresses.
- If the name still does not arrive, the remaining suspect is the Scanner's 5-entry name cache. That would need a Scanner-side change in a separate scope.
