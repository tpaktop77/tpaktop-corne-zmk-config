## Context

The dongle is the ZMK split central and owns the shared 42-position keymap. The current keymap has 15 layers with `RUSSIAN_SMILES=10`, `SYSTEM_BT=11`, and three Studio reserved layers at 12–14. Position 39 is transparent on both Symbols layers, and the global `&lt.quick-tap-ms = 250` must remain unchanged. See `proposal.md` for motivation and the delta specs for observable behavior.

## Goals / Non-Goals

**Goals:**

- add one shared 42-position `SYM_NUM` layer for both host language layouts;
- keep constants, keymap node order, display names, and Studio layer metadata aligned;
- support the nested hold-37 then hold-39 path using the existing `&lt` behavior;
- validate all four firmware entries from `build.yaml`.

**Non-Goals:**

- changing global or local tap-hold timing;
- redesigning Symbols, Russian Symbols, Smiles, combos, macros, or OS profiles;
- changing Studio, nice!view, dongle topology, or build configuration;
- adding separate English and Russian Shift Digits layers.

## Decisions

### 1. Place `SYM_NUM` immediately before `SYSTEM_BT`

`SYM_NUM=11` is above both parent layers (`SYMBOLS=7` and `RUSSIAN_SYMBOLS=9`), so its non-transparent home-row bindings win while it is held. `SYSTEM_BT=12` stays above all language layers. The three reserved nodes move to 13–15 without changing their count or status. Placing the layer near `NUMBERS` was rejected because its lower index could be masked by Russian Symbols.

### 2. Reuse the existing parameterized `&lt`

Position 39 on each Symbols layer uses exactly `&lt SYM_NUM TAB`. This preserves Tab on tap and inherits the existing global layer-tap settings. A new hold-tap behavior was rejected because it would introduce timing semantics outside the request.

### 3. Define all 42 bindings explicitly

The new node contains 36 body bindings and six thumbs. Only positions 13–22 use `&kp LS(N1)` through `&kp LS(N0)`; all other body positions are `&none`, and all thumbs are `&trans`. An explicit list makes position-count and accidental-fallthrough checks deterministic.

### 4. Keep Studio on the dongle

The `sym_num_layer` node receives `display-name = "Shift Digits"` and is placed at index 11 inside `keymap {}`. The existing three reserved nodes remain unchanged apart from their shifted indices. The Studio snippet and all build entries remain untouched.

### 5. Validate the existing build matrix

Static checks precede firmware builds. GitHub Actions will build the dongle with Studio RPC, both nice!view peripherals, and the settings-reset image using the unchanged four-entry `build.yaml`.

## Risks / Trade-offs

- [Node order differs from constants] → validate the complete 16-node sequence with a structural script.
- [A 42-binding row is shifted by one position] → verify exact body ranges 12–23 and thumb range 36–41.
- [Nested layer-tap feels different on particular switches] → preserve current timings and leave physical feel assessment to hardware testing.
- [Reserved-index movement affects Studio] → retain all three reserved nodes and build the dongle entry with its existing Studio snippet.

## Migration Plan

1. Update named indices and insert `sym_num_layer` at the matching keymap position.
2. Change only position 39 on `symbols_layer` and `russian_symbols_layer`.
3. Update `docs/layout.md`, then run structural and OpenSpec validation.
4. Build all four existing firmware targets. Rollback is a single commit revert because persistent state and pairing are unchanged.
