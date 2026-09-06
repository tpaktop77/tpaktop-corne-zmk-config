## 1. Keymap

- [x] 1.1 Insert `SYM_NUM=11`, move `SYSTEM_BT` and `STUDIO_EXTRA_1..3` to 12–15, and verify that every node inside `keymap {}` matches the constant order.
- [x] 1.2 Change only position 39 on `symbols_layer` and `russian_symbols_layer` to `&lt SYM_NUM TAB`; verify the global `&lt` settings and every other existing binding remain unchanged.
- [x] 1.3 Add a 42-binding `sym_num_layer` with shifted digits only at positions 13–22, none on all other body positions, and transparent thumbs; verify the exact positions structurally.

## 2. Documentation

- [x] 2.1 Update the layer index table and priority explanation in `docs/layout.md`; verify `SYM_NUM=11`, `SYSTEM_BT=12`, and Studio reserved layers 13–15 are documented.
- [x] 2.2 Add the `SYM_NUM` diagram and hold-37 then hold-39 activation sequence; verify Tab-on-tap and home-row Shift+1…Shift+0 are documented.

## 3. Validation

- [x] 3.1 Verify 16 layers, 42 bindings per keymap node, exact node order, the requested `SYM_NUM` mapping, and no changes to Studio or build configuration.
- [x] 3.2 Run `git diff --check`, a repository-wide Cyrillic search, and `openspec validate add-sym-num-layer --strict`; resolve every error.
- [ ] 3.3 Build all four entries from `build.yaml`, confirm dongle, left, right, and settings-reset jobs succeed, and record the validation evidence.
