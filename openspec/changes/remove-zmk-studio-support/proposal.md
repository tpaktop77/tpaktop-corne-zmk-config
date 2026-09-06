## Why

ZMK Studio is no longer needed for this dongle configuration because the version-controlled keymap is the source of truth. Removing the Studio endpoint and its reserved layers reduces the central build surface while preserving the tested `SYM_NUM` layout and every unrelated keyboard feature.

## What Changes

- **BREAKING** Remove the ZMK Studio USB RPC endpoint from the dongle firmware and remove its explicit Kconfig enablement.
- Remove the three Studio-only reserved layer constants and nodes.
- Compact the keymap to the explicit 13-layer order ending with `SYM_NUM=11` and `SYSTEM_BT=12`.
- Remove current documentation and test-plan references that describe Studio as an available feature, while retaining immutable archived migration records.
- Preserve dongle topology, USB keyboard HID, BLE, split transport, displays, key bindings, macros, combos, custom behaviors, and all existing timings.
- Build and validate every firmware target after the removal.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `central-services`: The dongle continues to own keymap and host-facing processing but no longer exposes ZMK Studio or Studio-only reserved layers.
- `layout-migration`: The maintained configuration now has exactly 13 ordered layers and no current Studio support or documentation claims.
- `shift-digits-layer`: The working shared `SYM_NUM` layer remains at index 11 while its ordering contract no longer requires Studio reserved layers.

## Impact

Affected files include `build.yaml`, `config/tpaktop_corne_dongle.conf`, `config/corne.keymap`, current documentation that advertises Studio, current OpenSpec requirements, and validation evidence. Archived OpenSpec changes remain unchanged as historical records. No custom behavior implementation, display configuration, peripheral firmware role, radio setting, or key behavior is redesigned.
