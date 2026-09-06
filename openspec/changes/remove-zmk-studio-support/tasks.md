## 1. Remove Studio Runtime Support

- [x] 1.1 Remove the dongle's `studio-rpc-usb-uart` snippet and explicit Studio Kconfig settings; verify no current build or config file enables `studio-rpc` or `ZMK_STUDIO`.
- [x] 1.2 Remove `STUDIO_EXTRA_1..3` constants and reserved nodes; structurally verify exactly 13 ordered functional layers remain at indices 0–12 with 42 bindings each.

## 2. Update Maintained Documentation

- [x] 2.1 Update `docs/layout.md` for the final 13-layer layout and remove Studio/reserved-layer claims; verify `SYM_NUM=11` and `SYSTEM_BT=12` remain documented.
- [x] 2.2 Remove or rewrite Studio-only claims in other current documentation while preserving archived OpenSpec history; verify current operating instructions no longer request Studio builds or tests.

## 3. Validate and Deliver

- [x] 3.1 Run focused repository searches, structural assertions, `git diff --check`, English-only validation, and strict OpenSpec validation; verify unrelated keymap behavior, dongle, BLE, USB, display, split, macro, combo, timing, and custom behavior files remain unchanged.
- [ ] 3.2 Build the dongle, left peripheral, right peripheral, and settings-reset targets; verify all four jobs and the merged firmware artifact succeed.
- [ ] 3.3 Record validation evidence, review the final diff, commit the completed change, push the branch, and create a pull request with remaining hardware checks identified.
