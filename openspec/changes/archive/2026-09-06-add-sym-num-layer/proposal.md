## Why

Both language-specific Symbols layers need the same fast physical access to the shifted digit row without duplicating English and Russian implementations. A shared momentary layer keeps the physical chord and firmware behavior consistent while leaving host-layout interpretation to the host.

## What Changes

- Add a shared `SYM_NUM` (“Shift Digits”) layer at index 11 between `RUSSIAN_SMILES` and `SYSTEM_BT`.
- Move `SYSTEM_BT` and the three ZMK Studio reserved layers to indices 12–15, keeping Devicetree node order identical to the constants.
- Set position 39 on `SYMBOLS` and `RUSSIAN_SYMBOLS` to `&lt SYM_NUM TAB`: tap sends Tab and hold activates `SYM_NUM`.
- Place `Shift+1` through `Shift+0` on home-row positions 13–22; make all other body positions none and all six thumbs transparent.
- Document the new index, activation sequence, and physical mapping in `docs/layout.md`.
- Preserve all other bindings, macros, combos, behaviors, timings, ZMK Studio configuration, and build configuration.

## Capabilities

### New Capabilities

- `shift-digits-layer`: Defines the shared Shift Digits layer, its physical mapping, layer-tap activation, and compatibility with both host language layouts.

### Modified Capabilities

- `layout-migration`: Records `SYM_NUM` as an intentional post-migration extension to the pinned source layout while preserving all unrelated migrated behavior.
- `central-services`: Extends the dongle-owned keymap and Studio-visible layer set without moving Studio or keymap processing to a peripheral.

## Impact

Only `config/corne.keymap`, `docs/layout.md`, and OpenSpec artifacts are changed. The dongle remains the keymap central, ZMK Studio remains on the dongle with three reserved layers, and the four-entry firmware build matrix remains unchanged.
