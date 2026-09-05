# QMK/Oryx to ZMK migration matrix

Primary QMK reference: `tpaktop77/oryx-with-custom-qmk`, remote `main@5d674ed4d866b66e34389262092cc5347da90bc7`. The direct read-only source for this dongle migration is `tpaktop-corne-wireless-view-zmk-config@e7d7c10`. It already contains Graphite/QWERTY/Russian, corrected thumb-overlay priority, 300 ms Auto Shift, positional combos, and the OS-profile module.

The target `tpaktop-corne-zmk-config` repository preserves all keymap bindings and timings. Intentional differences are limited to dongle topology, peripheral display mode, Studio RPC placement, build matrix, settings reset, firmware artifact naming, the 6-column safeguard, and English-only documentation/comments. Source repositories remain unchanged. Hardware validation of the new topology remains with the owner according to `docs/test-matrix.md`.

## Dongle migration layer

| Source | Source behavior | Target | Target behavior | Status | Validation |
|---|---|---|---|---|---|
| view repo `e7d7c10` | `corne_left` central | `tpaktop_corne_dongle` | headless central on `nice_nano_v2` | implemented; CI pass | run 33934665598; USB/BLE manual |
| view repo `e7d7c10` | left/right split roles | `corne_left`, `corne_right` | two BLE peripherals; 5-column layout disabled, 6-column fixed | implemented; CI pass | run 33934665598: compiled Devicetree for both halves; hardware layout/combo retest manual |
| view repo `e7d7c10` | Studio snippet on left | dongle build | Studio USB RPC on central | implemented; CI pass | dongle Studio build pass; connection manual |
| view repo nice!view custom widget | layer/profile/art UI | peripheral built-in status | local battery/charging and split link; dedicated display queue | implemented; CI pass | both nice!view builds pass; displays manual |
| view repo workflow | two UF2 files in `firmware.zip` | four-target workflow | dongle/left/right/reset plus timestamped archive | implemented; CI pass | artifact `corne-dongle-firmware_20260905_0057`, four UF2 files audited |
| view repo keymap/module | complete working baseline | shared central keymap/module | bindings and timings unchanged; comments translated | implemented; functional parity pass | structural checksum/audit plus regression matrix |

## Layers and shared behaviors

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---|---|---|---|
| `6JP4n/keymap.c` plus follow-up | 0 | three lower Voyager rows | Graphite body plus Escape | `GRAPHITE` 0 | 0-35 | Graphite with `&kp ESC` at position 0; top row omitted | implemented; CI pass | layout audit plus hardware |
| none | new | Corne body | minimal QWERTY | `QWERTY` 1 | 0-35 | letters/none plus `&to GRAPHITE` | implemented; CI pass | layout audit plus hardware |
| `6JP4n/keymap.c` | 0 | Graphite bottom-right | QMK `TT(2)` | `GRAPHITE` | 35 | `&to QWERTY` | implemented; CI pass | manual switch |
| none | new | QWERTY bottom-right | return | `QWERTY` | 35 | `&to GRAPHITE` | implemented; CI pass | manual switch |
| `6JP4n/keymap.c` | 0/1 | thumbs | layer taps | `GRAPHITE`, `QWERTY`, `RUSSIAN` | 36-41 | System; BSP/language Symbols; DEL/Numbers; TAB/Function; Space/Navigation; none | priority fix implemented; CI pass | static priority audit plus manual USB/BLE |
| `6JP4n/keymap.c` | 1 | three lower rows | Russian-PC body | `RUSSIAN` 2 | 0-41 | Russian base below every reachable overlay | priority fix implemented; CI pass | node-order audit plus manual thumbs |
| `6JP4n/keymap.c` | 3 | three lower rows | Numbers | `NUMBERS` 3 | 0-41 | preserved with named layer references | implemented; CI pass | build plus manual |
| `6JP4n/keymap.c` | 4 | three lower rows | Navigation/media | `NAVIGATION` 4 | 0-41 | migrated, OS adaptation deferred | implemented; CI pass | build plus regression |
| `6JP4n/keymap.c` | 5 | three lower rows | Function | `FUNCTION` 5 | 0-41 | preserved; VIM reference fixed | implemented; CI pass | build plus manual |
| `6JP4n/keymap.c` | 6 | three lower rows | Vim/macros | `VIM` 6 | 0-41 | preserved | implemented; CI pass | build plus manual |
| `6JP4n/keymap.c` | 7 | three lower rows | English Symbols | `SYMBOLS` 7 | 0-41 | preserved; Smiles reference fixed | implemented; CI pass | build plus manual |
| `6JP4n/keymap.c` | 9 | three lower rows | English Smiles | `SMILES` 8 | 0-41 | preserved | implemented; CI pass | build plus manual |
| prior ZMK Lower plus new | none | left/right body | Bluetooth plus OS controls | `SYSTEM_BT` 11 | 0-35 | BT0-BT4, protected clear, OS selectors 19-21 | implemented; CI pass | build plus manual |
| target Studio | none | reserved nodes | editable capacity | 12-14 | n/a | three `status = "reserved"` nodes after Russian layers | implemented; CI pass | Studio connection plus build |
| `6JP4n/config.h` | global | English/Russian letters | QMK Auto Shift 200 ms | `GRAPHITE`, `QWERTY`, `RUSSIAN` | every letter position | ZMK hold-tap Auto Shift 300 ms; thumb `&lt.quick-tap-ms` remains 250 ms | tuned; CI pass | false-positive and intentional-hold USB/BLE |

## Russian base layer

Every row below comes from `6JP4n/keymap.c`, QMK layer 1. QMK aliases were checked against `6JP4n/i18n.h`; the target sends the same physical keyboard HID usages when Russian-PC is active on the host. ZMK `LBKT/RBKT` correspond to QMK `KC_LBRC/KC_RBRC`; ZMK `LBRC/RBRC` mean curly braces and are not used here. Output is identified by alias rather than literal Cyrillic glyphs.

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---:|---|---|---|
| `keymap.c` plus `i18n.h` | 1 | row 1 col 1 | `RU_SHTI = KC_Q` | `RUSSIAN` 2 | 1 | `AS(Q)` -> `RU_SHTI` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 2 | `RU_TSE = KC_W` | `RUSSIAN` 2 | 2 | `AS(W)` -> `RU_TSE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 3 | `RU_U = KC_E` | `RUSSIAN` 2 | 3 | `AS(E)` -> `RU_U` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 4 | `RU_KA = KC_R` | `RUSSIAN` 2 | 4 | `AS(R)` -> `RU_KA` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 5 | `RU_IE = KC_T` | `RUSSIAN` 2 | 5 | `AS(T)` -> `RU_IE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 6 | `RU_EN = KC_Y` | `RUSSIAN` 2 | 6 | `AS(Y)` -> `RU_EN` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 7 | `RU_GHE = KC_U` | `RUSSIAN` 2 | 7 | `AS(U)` -> `RU_GHE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 8 | `RU_SHA = KC_I` | `RUSSIAN` 2 | 8 | `AS(I)` -> `RU_SHA` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 9 | `RU_SHCH = KC_O` | `RUSSIAN` 2 | 9 | `AS(O)` -> `RU_SHCH` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 10 | `RU_ZE = KC_P` | `RUSSIAN` 2 | 10 | `AS(P)` -> `RU_ZE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 1 col 11 | `RU_HA = KC_LBRC` | `RUSSIAN` 2 | 11 | `AS(LBKT)` -> `RU_HA` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 1 | `RU_EF = KC_A` | `RUSSIAN` 2 | 13 | `AS(A)` -> `RU_EF` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 2 | `RU_YERU = KC_S` | `RUSSIAN` 2 | 14 | `AS(S)` -> `RU_YERU` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 3 | `RU_VE = KC_D` | `RUSSIAN` 2 | 15 | `AS(D)` -> `RU_VE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 4 | `RU_A = KC_F` | `RUSSIAN` 2 | 16 | `AS(F)` -> `RU_A` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 5 | `RU_PE = KC_G` | `RUSSIAN` 2 | 17 | `AS(G)` -> `RU_PE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 6 | `RU_ER = KC_H` | `RUSSIAN` 2 | 18 | `AS(H)` -> `RU_ER` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 7 | `RU_O = KC_J` | `RUSSIAN` 2 | 19 | `AS(J)` -> `RU_O` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 8 | `RU_EL = KC_K` | `RUSSIAN` 2 | 20 | `AS(K)` -> `RU_EL` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 9 | `RU_DE = KC_L` | `RUSSIAN` 2 | 21 | `AS(L)` -> `RU_DE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 10 | `RU_ZHE = KC_SCLN` | `RUSSIAN` 2 | 22 | `AS(SEMI)` -> `RU_ZHE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 2 col 11 | `RU_E = KC_QUOT` | `RUSSIAN` 2 | 23 | `AS(SQT)` -> `RU_E` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 1 | `RU_YA = KC_Z` | `RUSSIAN` 2 | 25 | `AS(Z)` -> `RU_YA` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 2 | `RU_CHE = KC_X` | `RUSSIAN` 2 | 26 | `AS(X)` -> `RU_CHE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 3 | `RU_ES = KC_C` | `RUSSIAN` 2 | 27 | `AS(C)` -> `RU_ES` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 4 | `RU_EM = KC_V` | `RUSSIAN` 2 | 28 | `AS(V)` -> `RU_EM` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 5 | `RU_I = KC_B` | `RUSSIAN` 2 | 29 | `AS(B)` -> `RU_I` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 6 | `RU_TE = KC_N` | `RUSSIAN` 2 | 30 | `AS(N)` -> `RU_TE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 7 | `RU_SOFT = KC_M` | `RUSSIAN` 2 | 31 | `AS(M)` -> `RU_SOFT` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 8 | `RU_BE = KC_COMM` | `RUSSIAN` 2 | 32 | `AS(COMMA)` -> `RU_BE` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 9 | `RU_YU = KC_DOT` | `RUSSIAN` 2 | 33 | `AS(DOT)` -> `RU_YU` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 10 | `RU_YO = KC_GRV` | `RUSSIAN` 2 | 34 | `AS(GRAVE)` -> `RU_YO` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 1 | row 3 col 11 | `RU_HARD = KC_RBRC` | `RUSSIAN` 2 | 35 | `AS(RBKT)` -> `RU_HARD` | implemented; CI pass | Russian-PC USB/BLE |

## Russian service positions and thumbs

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---:|---|---|---|
| `keymap.c` | 1 | row 1 outer-left | transparent | `RUSSIAN` | 0 | `&trans` -> Graphite Escape | implemented; CI pass | fallback manual |
| `keymap.c` | 1 | row 2 outer-left | transparent | `RUSSIAN` | 12 | `&trans` -> Graphite none | implemented; CI pass | fallback manual |
| `keymap.c` plus `switch_cases.c` concept | 0/1 | row 3 outer-left | `TT(1)` plus language combo | `GRAPHITE`/`RUSSIAN` | 24 | directed host shortcut plus `&to` opposite language layer | implemented; CI pass | USB/BLE host synchronization |
| target plus `keymap.c` | 1 | added outer thumb | System access | `RUSSIAN` | 36 | `&mo SYSTEM_BT` | implemented; CI pass | thumb manual |
| `keymap.c` | 1 | left inner thumb | `LT(8, KC_BSPC)` | `RUSSIAN` | 37 | `&lt RUSSIAN_SYMBOLS BSPC` | implemented; CI pass | tap/hold manual |
| target | shared thumb | Delete/Numbers | `RUSSIAN` | 38 | `&lt NUMBERS DEL` | implemented; CI pass | tap/hold manual |
| target | shared thumb | Tab/Function | `RUSSIAN` | 39 | `&lt FUNCTION TAB` | implemented; CI pass | tap/hold manual |
| target | shared thumb | Space/Navigation | `RUSSIAN` | 40 | `&lt NAVIGATION SPACE` | implemented; CI pass | tap/hold manual |
| target | added outer thumb | unused | `RUSSIAN` | 41 | `&none` | implemented; CI pass | manual |

Priority after the fix: `RUSSIAN = 2`; shared thumb targets `NUMBERS = 3`, `NAVIGATION = 4`, `FUNCTION = 5`, and `SYSTEM_BT = 11`; language-specific targets `RUSSIAN_SYMBOLS = 9` and `RUSSIAN_SMILES = 10`. All five used hold transitions therefore override the Russian base, and child Smiles overrides Symbols.

## Russian Symbols and Smiles

Empty QMK `KC_NO` positions remain `&none`; this table lists migrated non-empty bindings. Symbols are rendered by the host only under Russian-PC.

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---:|---|---|---|
| `keymap.c` plus `i18n.h` | 8 | row 1 cols 3-4 | `RU_LPRN`, `RU_RPRN` | `RUSSIAN_SYMBOLS` 9 | 3, 4 | `LS(N9)`, `LS(N0)` -> LeftParen, RightParen | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 8 | row 1 right cols 0-5 | `RU_NUM/UNDS/MINS/SLSH/BSLS/MINS` | `RUSSIAN_SYMBOLS` 9 | 6-11 | `LS(N3)`, `LS(MINUS)`, `MINUS`, `LS(BSLH)`, `BSLH`, `MINUS` -> NumberSign, Underscore, Minus, Slash, Backslash, Minus | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 8 | row 2 right cols 1-5 | `RU_DOT/COMM/EXLM/QUES/SLSH` | `RUSSIAN_SYMBOLS` 9 | 19-23 | `FSLH`, `LS(FSLH)`, `LS(N1)`, `LS(N7)`, `LS(BSLH)` -> Dot, Comma, Exclamation, Question, Slash | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` plus `i18n.h` | 8 | row 3 right cols 1-5 | `RU_DQUO/COLN/SCLN/EQL/ASTR` | `RUSSIAN_SYMBOLS` 9 | 31-35 | `LS(N2)`, `LS(N6)`, `LS(N4)`, `EQUAL`, `LS(N8)` -> DoubleQuote, Colon, Semicolon, Equal, Asterisk | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` | 8 | four Voyager thumbs | transparent plus `LT(10, KC_SPACE)` | `RUSSIAN_SYMBOLS` 9 | 36-41 | transparent; position 40 is `&lt RUSSIAN_SMILES SPACE` | implemented; CI pass | fallback plus tap/hold |
| `keymap.c` | 10 | right home col 1 | `ST_MACRO_35` | `RUSSIAN_SMILES` 10 | 19 | named macro `LS(N6), LS(N0)` -> `:)` | implemented; CI pass | Russian-PC USB/BLE |
| `keymap.c` | 10 | right home col 2 | `ST_MACRO_36` | `RUSSIAN_SMILES` 10 | 20 | named macro `LS(N6), LS(N9)` -> `:(` | implemented; CI pass | Russian-PC USB/BLE |

## Language switching and temporary Caps Word

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---:|---|---|---|
| `modules/combos.c`, `modules/switch_cases.c` | 0 | F+O+U | toggle layer plus `Ctrl+Shift+2` | `GRAPHITE` | 7 8 9 | directed `to_russian`: `Ctrl+Shift+2`, `&to RUSSIAN` | implemented; CI pass | USB/BLE host synchronization |
| `modules/combos.c`, `modules/switch_cases.c` | 1 | `RU_GHE+RU_SHA+RU_SHCH` | toggle layer plus `Ctrl+Shift+1` | `RUSSIAN` | 7 8 9 | directed `to_english`: `Ctrl+Shift+1`, `&to GRAPHITE` | implemented; CI pass | USB/BLE host synchronization |
| `keymap.c` | 0/1 | lower outer-left | source-only `TT(1)` | `GRAPHITE`/`RUSSIAN` | 24 | reuse the corresponding directed action | implemented; CI pass | USB/BLE host synchronization |
| ZMK built-in | global | Caps Word state | Shift only HID A-Z | `GRAPHITE`/`QWERTY`/`RUSSIAN` | combo 13 16 | `continue-list` also retains `LBKT RBKT SEMI SQT COMMA DOT GRAVE`; seven letters remain lowercase | implemented workaround; CI pass | explicit manual limitation |
| future | none | none | complete Russian capitalization | future `implement-russian-caps-word` | none | custom behavior after hardware validation | deferred to next OpenSpec | separate proposal required |

## System/Bluetooth

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---:|---|---|---|
| prior target Lower | 1 | left top row | `BT_SEL 0` | `SYSTEM_BT` | 0 | `&bt BT_SEL 0` | implemented; CI pass | manual USB/BLE |
| prior target Lower | 1 | left top row | `BT_SEL 1` | `SYSTEM_BT` | 1 | `&bt BT_SEL 1` | implemented; CI pass | manual USB/BLE |
| prior target Lower | 1 | left top row | `BT_SEL 2` | `SYSTEM_BT` | 2 | `&bt BT_SEL 2` | implemented; CI pass | manual USB/BLE |
| prior target Lower | 1 | left top row | `BT_SEL 3` | `SYSTEM_BT` | 3 | `&bt BT_SEL 3` | implemented; CI pass | manual USB/BLE |
| prior target Lower | 1 | left top row | `BT_SEL 4` | `SYSTEM_BT` | 4 | `&bt BT_SEL 4` | implemented; CI pass | manual USB/BLE |
| prior target Lower | 1 | lower outer-left | unprotected `BT_CLR` | `SYSTEM_BT` | 24 | tap-preferred 1500 ms hold -> BT Clear | implemented; CI pass | short/long manual |
| `modules/switch_cases.c` concept | global | right home index | detected OS | `SYSTEM_BT` | 19 | `&os_set OS_WINDOWS` | implemented; CI pass | state/action test |
| `modules/switch_cases.c` concept | global | right home | detected OS | `SYSTEM_BT` | 20 | `&os_set OS_MACOS` | implemented; CI pass | state/action test |
| `modules/switch_cases.c` concept | global | right home | detected OS | `SYSTEM_BT` | 21 | `&os_set OS_LINUX` | implemented; CI pass | state/action test |

## Positional combos

Source chords are shown using Oryx Graphite letters plus Russian-PC aliases, but every target combo is defined only by `key-positions`. The compatible base scope after Russian migration is `<GRAPHITE QWERTY RUSSIAN>`. English/Russian Smiles and language combos use separate scopes; Vim remains `<GRAPHITE QWERTY>`. Arithmetic scope is `<NUMBERS>`.

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---:|---|---|---|---|---|---|---|
| `modules/combos.c` | 0/1 | H+A+E / `RU_O+RU_EL+RU_DE` | Enter | Graphite/QWERTY/Russian | 19 20 21 | `&kp RET` | implemented; CI pass | USB/BLE plus overlap |
| `modules/combos.c` | 0/1 | R+T+S / `RU_YERU+RU_VE+RU_A` | Tab | Graphite/QWERTY/Russian | 14 15 16 | `&kp TAB` | implemented; CI pass | USB/BLE plus overlap |
| `modules/combos.c` | 0/1 | N+S / `RU_EF+RU_A` | Caps Word | Graphite/QWERTY/Russian | 13 16 | `&caps_word` | implemented; CI pass | manual plus seven exceptions |
| `modules/combos.c` | 0/1 | N+G / `RU_EF+RU_PE` | Caps Lock | Graphite/QWERTY/Russian | 13 17 | `&kp CAPSLOCK` | implemented; CI pass | all 33 letters manual |
| `modules/combos.c` | 3 | 7+8+9 | Minus | Numbers | 7 8 9 | `&kp MINUS` | implemented; CI pass | USB/BLE |
| `modules/combos.c` | 3 | 4+5+6 | Equal | Numbers | 19 20 21 | `&kp EQUAL` | implemented; CI pass | overlap USB/BLE |
| `modules/combos.c` | 3 | 1+2+3 | Plus | Numbers | 31 32 33 | `&kp PLUS` | implemented; CI pass | overlap USB/BLE |
| `modules/combos.c` | 3 | 4+5+6+Dot | Slash | Numbers | 19 20 21 22 | `&kp FSLH` | implemented; CI pass | overlap USB/BLE |
| `modules/combos.c` | 3 | 1+2+3+Equal | Asterisk | Numbers | 31 32 33 34 | `&kp ASTRK` | implemented; CI pass | overlap USB/BLE |
| `modules/combos.c` | 0 | G+Z | momentary Smiles | Graphite/QWERTY | 5 17 | `&mo SMILES`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 1 | `RU_PE+RU_IE` | momentary Russian Smiles | Russian | 5 17 | `&mo RUSSIAN_SMILES`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0 | H+I | one-shot Vim | Graphite/QWERTY | 19 22 | `&sl VIM` | implemented; CI pass | manual |
| `modules/combos.c` | 0/1 | Q+N / `RU_YA+RU_EF` | Left Alt | Graphite/QWERTY/Russian | 13 25 | `&kp LALT`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | X+R / `RU_CHE+RU_YERU` | Left GUI | Graphite/QWERTY/Russian | 14 26 | `&kp LGUI`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | M+T / `RU_ES+RU_VE` | Left Shift | Graphite/QWERTY/Russian | 15 27 | `&kp LSHIFT`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | C+S / `RU_EM+RU_A` | Left Ctrl | Graphite/QWERTY/Russian | 16 28 | `&kp LCTRL`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | P+H / `RU_SOFT+RU_O` | Right Ctrl | Graphite/QWERTY/Russian | 19 31 | `&kp RCTRL`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | F22+A / `RU_BE+RU_EL` | Right Shift | Graphite/QWERTY/Russian | 20 32 | `&kp RSHIFT`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | F23+E / `RU_YU+RU_DE` | Right GUI | Graphite/QWERTY/Russian | 21 33 | `&kp RGUI`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | F24+I / `RU_YO+RU_ZHE` | Right Alt | Graphite/QWERTY/Russian | 22 34 | `&kp RALT`, slow-release | implemented; CI pass | release manual |
| `modules/combos.c` | 0/1 | R+L / `RU_YERU+RU_TSE` | Copy | Graphite/QWERTY/Russian | 2 14 | `&os_action OS_ACTION_COPY` | implemented; CI pass | three OS profiles plus Copy/Cut overlap |
| `modules/combos.c` | 0/1 | T+D / `RU_VE+RU_U` | Paste | Graphite/QWERTY/Russian | 3 15 | `&os_action OS_ACTION_PASTE` | implemented; CI pass | three OS profiles |
| `modules/combos.c` | 0/1 | R+L+T+D / `RU_YERU+RU_TSE+RU_VE+RU_U` | Cut | Graphite/QWERTY/Russian | 2 3 14 15 | `&os_action OS_ACTION_CUT` | implemented; CI pass | three OS profiles plus Copy/Cut overlap |
| `modules/combos.c` | 0/1 | A+O / `RU_EL+RU_SHA` | Undo | Graphite/QWERTY/Russian | 8 20 | `&os_action OS_ACTION_UNDO` | implemented; CI pass | three OS profiles |
| `modules/combos.c` | 0/1 | E+U / `RU_DE+RU_SHCH` | Redo | Graphite/QWERTY/Russian | 9 21 | `&os_action OS_ACTION_REDO` | implemented; CI pass | three OS profiles |
| `modules/combos.c` | 0/1 | Y+H+A / `RU_ER+RU_O+RU_EL` | Voice | Graphite/QWERTY/Russian | 18 19 20 | `&os_action OS_ACTION_VOICE` | implemented; CI pass | three OS profiles; Mac consumer |
| `modules/combos.c` | 0/1 | N+R+T / `RU_EF+RU_YERU+RU_VE` | Word Backspace | Graphite/QWERTY/Russian | 13 14 15 | `&os_action OS_ACTION_WORD_BACKSPACE` | implemented; CI pass | three OS profiles plus overlap |
| `modules/combos.c` | 0/1 | A+E+I / `RU_EL+RU_DE+RU_ZHE` | Word Delete | Graphite/QWERTY/Russian | 20 21 22 | `&os_action OS_ACTION_WORD_DELETE` | implemented; CI pass | three OS profiles plus overlap |
| `modules/combos.c` | 0/1 | Q+X+M / `RU_YA+RU_CHE+RU_ES` | Word Previous | Graphite/QWERTY/Russian | 25 26 27 | `&os_action OS_ACTION_WORD_PREVIOUS` | implemented; CI pass | three OS profiles |
| `modules/combos.c` | 0/1 | F22+F23+F24 / `RU_BE+RU_YU+RU_YO` | Word Next | Graphite/QWERTY/Russian | 32 33 34 | `&os_action OS_ACTION_WORD_NEXT` | implemented; CI pass | positions plus three OS profiles |
| `modules/combos.c` | 0/1 | H+A+E+I / `RU_O+RU_EL+RU_DE+RU_ZHE` | App Switch | Graphite/QWERTY/Russian | 19 20 21 22 | `&os_action OS_ACTION_APP_SWITCH` | implemented; CI pass | three OS profiles plus Enter overlap |
| `modules/combos.c` | 0/1 | N+R+T+S / `RU_EF+RU_YERU+RU_VE+RU_A` | Task View | Graphite/QWERTY/Russian | 13 14 15 16 | `&os_action OS_ACTION_TASK_VIEW` | implemented; CI pass | three OS profiles plus Tab/word overlap |
| `modules/combos.c` | 0/1 | N+B / `RU_EF+RU_SHTI` | Select All | Graphite/QWERTY/Russian | 1 13 | `&os_action OS_ACTION_SELECT_ALL` | implemented; CI pass | three OS profiles |

## OS-aware actions

| Source QMK file | Source QMK layer | Source physical position | Source behavior | Target ZMK layer | Target key-position | Target behavior | Status | Validation |
|---|---|---|---|---|---|---|---|---|
| `modules/switch_cases.c` | global | Copy combo | OS-aware copy | Graphite/QWERTY/Russian | 2 14 | `OS_ACTION_COPY` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Paste combo | OS-aware paste | Graphite/QWERTY/Russian | 3 15 | `OS_ACTION_PASTE` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Cut combo | OS-aware cut | Graphite/QWERTY/Russian | 2 3 14 15 | `OS_ACTION_CUT` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Undo combo | OS-aware undo | Graphite/QWERTY/Russian | 8 20 | `OS_ACTION_UNDO` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Redo combo | OS-aware redo | Graphite/QWERTY/Russian | 9 21 | `OS_ACTION_REDO` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Select All combo | OS-aware select | Graphite/QWERTY/Russian | 1 13 | `OS_ACTION_SELECT_ALL` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | word-left combo | Ctrl/Alt Left | Graphite/QWERTY/Russian | 25 26 27 | `OS_ACTION_WORD_PREVIOUS` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | word-right combo | Ctrl/Alt Right | Graphite/QWERTY/Russian | 32 33 34 | `OS_ACTION_WORD_NEXT` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | word-Backspace combo | Ctrl/Alt Backspace | Graphite/QWERTY/Russian | 13 14 15 | `OS_ACTION_WORD_BACKSPACE` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | word-Delete combo | Ctrl/Alt Delete | Graphite/QWERTY/Russian | 20 21 22 | `OS_ACTION_WORD_DELETE` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Alt-Tab combo | application switch | Graphite/QWERTY/Russian | 19 20 21 22 | `OS_ACTION_APP_SWITCH` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Alt-Win combo | task view | Graphite/QWERTY/Russian | 13 14 15 16 | `OS_ACTION_TASK_VIEW` | implemented; CI pass | Win/Mac/Linux |
| `modules/switch_cases.c` | global | Voice combo | OS voice | Graphite/QWERTY/Russian | 18 19 20 | `OS_ACTION_VOICE` | implemented; CI pass | Win/Mac/Linux |

## Explicit exclusions

| Source | Feature/layer | Status | Reason/validation |
|---|---|---|---|
| QMK Voyager top row, layer 1 | transparent Russian row | excluded | the complete top row is omitted |
| QMK Voyager top row, layer 8 | Percent, Ruble Sign, Plus, and duplicate Asterisk | deferred | do not redistribute in this change; the lower Asterisk is migrated |
| Alternative input | Unicode Russian | excluded | use the tested host Russian-PC model |
| QWERTY language cycling | return to the previous English layout | excluded | leaving Russian always goes directly to Graphite |
| ZMK custom behavior | complete Russian Caps Word | deferred | next OpenSpec `implement-russian-caps-word`; current stage uses only `continue-list` |
| Combo tuning | overlap timeout or policy changes | deferred | separate branch/change after new switches arrive |
| QMK layer 2 | old TB/numeric macro layer | excluded | explicitly omitted; do not create it |
| `ST_MACRO_0-10` | numeric text macros | excluded | belong to old layer 2 |
| QMK layer 11 | Mouse/Navigator | excluded | mouse, trackpad, and automouse are forbidden |
| QMK top row | `/findbynick`, `/birzha`, Auto Shift toggles, Ctrl+Alt+1-4, RGB, bootloader | excluded | complete Voyager top row omitted |
| Navigation OS mapping | OS-aware tabs/workspaces/voice | deferred | `migrated, OS adaptation deferred` |
| OS persistence/detection | flash or USB detection | excluded | the profile returns to Windows after reboot |
