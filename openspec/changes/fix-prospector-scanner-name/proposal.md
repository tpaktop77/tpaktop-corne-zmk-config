# Proposal

## Why

Prospector Scanner has never shown the configured keyboard name `TPAK`; it always shows `Unknown`. Source review of Prospector module v2.2.3 against pinned Zephyr 3.5 found the cause in the dongle-side advertiser (`src/status_advertisement.c`), not in this repository's configuration.

## What Changes

- Use a fork of the module, `tpaktop77/prospector-zmk-module`, with one fix commit on top of `v2.2.3`. Pin it by full commit hash in `config/west.yml`.
- The fix makes own advertising carry the name in a way Zephyr accepts, keeps a stable identity address, and leaves the non-scannable burst advertisement once the split is fully connected.

## Capabilities

### Modified Capabilities

- `prospector-status-advertisements`: Scanner can learn and keep `TPAK` while the dongle is connected to a BLE host.

## Impact

Only the dongle firmware changes. The halves and Scanner firmware, keymap, build matrix, workflow, and bonds are unchanged. ZMK stays at v0.3 and the module stays at v2.2.3 plus one fix commit.

Non-goals: Scanner-side changes (such as a larger name cache), upgrading dependencies, settings reset, or automatic flashing.
