# Tasks

## 1. Module fix

- [x] 1.1 Fork `t-ogura/prospector-zmk-module` to `tpaktop77`, branch `20261018__fix_scanner_name_tpak` from `v2.2.3`, and commit the advertiser fix (af1c531849ddb9ec253944dee91f799a6c932aa7).
- [x] 1.2 Syntax-check the patched file against the pinned Zephyr/ZMK headers and the dongle config.

## 2. Keyboard configuration

- [x] 2.1 Point `config/west.yml` at the fork, pinned by full commit hash.
- [x] 2.2 Push the branch and confirm all four GitHub Actions targets pass. Inspect the dongle log for the fork checkout and for new warnings. Commit 466c76d passed all four targets in run 39099818090 (artifact `corne-dongle-firmware_20261018_0513`). The log shows the module checked out at af1c531. The only warning in the patched file is the pre-existing unused `wpm_start_time`.

## 3. Owner hardware validation

- [ ] 3.1 Flash only the dongle. The Scanner shows `TPAK` while the dongle is connected to a BLE host.
- [ ] 3.2 `TPAK` persists after a dongle reboot and after power-cycling each half. nRF Connect shows a single device entry across reboots.
- [ ] 3.3 Typing on both halves, layers, both batteries, zmk-battery-center, and host reconnection to bonded profiles still work.
