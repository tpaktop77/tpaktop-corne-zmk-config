# Corne layout

The layout was migrated without functional changes from read-only `tpaktop-corne-wireless-view-zmk-config@e7d7c10`. The dongle change affects only split topology, nice!view contents, the Studio endpoint, and firmware packaging. `.` represents `&none`, and `▽` represents `&trans`. `AS(X)` means Auto Shift: tap sends `X`; holding longer than 300 ms sends `Shift+X`.

## Device architecture

```text
Corne Left  (peripheral + nice!view) --BLE--\
                                                >-- nice_nano_v2 dongle (central) --USB/BLE--> host
Corne Right (peripheral + nice!view) --BLE--/
```

The dongle has no keys or screen. It processes the shared 42-key keymap, combos, macros, OS profile, five host Bluetooth profiles, and ZMK Studio. The halves forward physical positions only. They do not generate keyboard HID without the dongle.

The built-in status screen on each half's nice!view shows that half's battery percentage, USB charging state, and dongle connection state. Layer name, OS/host profile, and decorative artwork are not displayed. Display updates explicitly use a dedicated ZMK work queue.

## Position numbering

ZMK combos use physical `key-positions`, numbered left to right across each row and then across the thumbs:

```text
 0  1  2  3  4  5   |   6  7  8  9 10 11
12 13 14 15 16 17   |  18 19 20 21 22 23
24 25 26 27 28 29   |  30 31 32 33 34 35
          36 37 38   |  39 40 41
```

Positions `32`, `33`, and `34`, which held `F22/F23/F24` on Oryx Graphite, contain `&none` on the base layer. Combos continue to reference these physical indices directly.

## Layer structure

| Index | Constant | Display name | Purpose |
|---:|---|---|---|
| 0 | `GRAPHITE` | Graphite | only boot-time base |
| 1 | `QWERTY` | QWERTY | minimal alternative layout |
| 2 | `RUSSIAN` | Russian | Russian-PC layout |
| 3 | `NUMBERS` | Numbers | digits, brackets, and arithmetic |
| 4 | `NAVIGATION` | Navigation | navigation and media; OS adaptation deferred |
| 5 | `FUNCTION` | Function | F1-F20 and modifiers |
| 6 | `VIM` | Vim | Vim macros |
| 7 | `SYMBOLS` | Symbols | English symbols and path macros |
| 8 | `SMILES` | Smiles | English ASCII emoticons |
| 9 | `RUSSIAN_SYMBOLS` | Russian Symbols | symbols produced under Russian-PC |
| 10 | `RUSSIAN_SMILES` | Russian Smiles | emoticons produced under Russian-PC |
| 11 | `SYSTEM_BT` | System | Bluetooth and OS profile |
| 12 | `STUDIO_EXTRA_1` | reserved | ZMK Studio reserve |
| 13 | `STUDIO_EXTRA_2` | reserved | ZMK Studio reserve |
| 14 | `STUDIO_EXTRA_3` | reserved | ZMK Studio reserve |

ZMK resolves a binding from the active layer with the highest index. All three base layers therefore come first, shared thumb overlays come after them, and each child layer (`VIM`, `SMILES`, `RUSSIAN_SMILES`) comes after its parent. This gives Graphite, QWERTY, and Russian an effectively identical thumb cluster.

## Shared base-layer thumb keys

```text
Left outer       Left inner          Left center
SYSTEM (hold)    BSPC / SYMBOLS      DEL / NUMBERS

Right center     Right inner         Right outer
TAB / FUNCTION   SPACE / NAVIGATION  .
```

In keymap position order `36..41`:

```text
&mo SYSTEM_BT | &lt SYMBOLS BSPC | &lt NUMBERS DEL
&lt FUNCTION TAB | &lt NAVIGATION SPACE | &none
```

`&lt.quick-tap-ms = 250` preserves rapid repetition of a layer-tap's tap keycode and is independent of Auto Shift. Auto Shift has its own 300 ms threshold to reduce false uppercase letters during normal typing.

On `RUSSIAN`, the only language-specific difference is position 37, which opens `RUSSIAN_SYMBOLS` instead of `SYMBOLS`; positions 36 and 38-41 have the same semantics. Every target overlay layer has a higher index than `RUSSIAN`, so holding a thumb actually overrides the Russian base.

## 0 - Graphite

The Voyager top row is omitted. The bottom-right body key selects QWERTY.

```text
ESC     AS(B) AS(L) AS(D) AS(W) AS(Z) | NUMLOCK AS(F) AS(O) AS(U) AS(J) .
.       AS(N) AS(R) AS(T) AS(S) AS(G) | AS(Y)   AS(H) AS(A) AS(E) AS(I) .
->RU    AS(Q) AS(X) AS(M) AS(C) AS(V) | AS(K)   AS(P) .     .     .     ->QWERTY
              SYSTEM  BSP/SYMB  DEL/NUM | TAB/FN  SPC/NAV  .
```

This is the active layer after reboot.

`->RU` at position 24 sends `Ctrl+Shift+2` and then directly activates `RUSSIAN`. The same action is available through combo positions `7+8+9` (Graphite `F+O+U`).

## 1 - QWERTY

The body contains only English letters, empty positions, and the return key.

```text
.       AS(Q) AS(W) AS(E) AS(R) AS(T) | AS(Y) AS(U) AS(I) AS(O) AS(P) .
.       AS(A) AS(S) AS(D) AS(F) AS(G) | AS(H) AS(J) AS(K) AS(L) .     .
.       AS(Z) AS(X) AS(C) AS(V) AS(B) | AS(N) AS(M) .     .     .     ->GRAPHITE
              SYSTEM  BSP/SYMB  DEL/NUM | TAB/FN  SPC/NAV  .
```

## 2 - Russian

This layer uses standard HID usages and requires Russian-PC to be active on the host. It does not use Unicode. Position 0 is transparent and inherits Graphite Escape; position 12 is transparent and inherits Graphite `&none`.

The diagram uses QMK Russian alias names to keep repository text ASCII while preserving an exact, auditable mapping.

```text
▽       AS(RU_SHTI) AS(RU_TSE) AS(RU_U)  AS(RU_KA) AS(RU_IE) | AS(RU_EN) AS(RU_GHE) AS(RU_SHA)  AS(RU_SHCH) AS(RU_ZE) AS(RU_HA)
▽       AS(RU_EF)   AS(RU_YERU)AS(RU_VE) AS(RU_A)  AS(RU_PE) | AS(RU_ER) AS(RU_O)   AS(RU_EL)   AS(RU_DE)   AS(RU_ZHE)AS(RU_E)
->ENG   AS(RU_YA)   AS(RU_CHE) AS(RU_ES) AS(RU_EM) AS(RU_I)  | AS(RU_TE) AS(RU_SOFT)AS(RU_BE)   AS(RU_YU)   AS(RU_YO) AS(RU_HARD)
                         SYSTEM BSP/RU-SYMB DEL/NUM | TAB/FN SPC/NAV .
```

Thumb positions `36..41`:

```text
&mo SYSTEM_BT | &lt RUSSIAN_SYMBOLS BSPC | &lt NUMBERS DEL
&lt FUNCTION TAB | &lt NAVIGATION SPACE | &none
```

All hold layers have higher indices than `RUSSIAN`, so System, Russian Symbols, Numbers, Function, and Navigation override the Russian base until the thumb is released.

`->ENG` at position 24 sends `Ctrl+Shift+1` and then directly activates `GRAPHITE`. The same action is available through combo positions `7+8+9` (Russian aliases `RU_GHE+RU_SHA+RU_SHCH`). QWERTY is not part of the language cycle.

## 3 - Numbers

This is the preserved Oryx Numbers layer. `ESC/VIM` uses the named `VIM` layer reference.

```text
ENTER <    >    (    )    . | =    7    8    9    .    -
TAB   LALT LGUI LSFT LCTL . | .    4    5    6    .    /
.     {    }    [    ]    . | .    1    2    3    =    *
              ▽    ▽    ▽   | ESC/VIM 0 ▽
```

Arithmetic combos are active only on this layer.

## 4 - Navigation

This layer was migrated without OS-aware adaptation: `migrated, OS adaptation deferred`.

```text
ENTER PREV NEXT STOP PLAY VOICE | PGUP HOME UP   END  . CTRL-W
TAB   LALT LGUI LSFT LCTL MUTE  | PGDN LEFT DOWN RIGHT . CTRL-T
.     VOLD VOLU .    .    .     | .    P-TAB N-TAB P-DESK N-DESK INS
                  ▽  ▽  ▽        | ▽  ▽  ▽
```

## 5 - Function

```text
ENTER F1   F2   F3   F4   F5 | F6   F7   F8   F9   F10  .
TAB   LALT LGUI LSFT LCTL .  | .    RCTL RSFT RGUI RALT .
.     F11  F12  F13  F14  F15| F16  F17  F18  F19  F20  .
                 ▽  ▽ DEL/VIM | ▽  ▽  ▽
```

## 6 - Vim

`M11-M21` are existing version-controlled macros documented by comments in the keymap.

```text
:  .  M11 M12 M13 M14 | M18 M19 K M20 . .
.  .  .   M15 M16 M17 | M21 H   J L   . .
.  .  .   .   .   .   | .   .   . .   . .
              ▽  ▽  ▽  | ▽  ▽  ▽
```

## 7 - Symbols

```text
`   <   >   (   )   . | #  _  -  /  \ -
M22 M23 M24 M25 /   | | @  .  ,  !  ?  /
M26 {   }   [   ]   . | '  "  :  ;  =  *
              ▽  ▽  ▽ | ▽  SPACE/SMILES  ▽
```

## 8 - Smiles

`M27-M34` are English ASCII emoticons.

```text
. . . . . . | M27 M28 M29 M30 . .
. . . . . . | M31 M32 M33 M34 . .
. . . . . . | .   .   .   .   . .
        ▽ ▽ ▽ | ▽ ▽ ▽
```

## 9 - Russian Symbols

Only the three lower Voyager rows are migrated. The diagram shows expected Russian-PC output by name; the keymap retains the original QMK physical HID usages.

```text
. . . LeftParen RightParen . | NumberSign Underscore Minus Slash Backslash Minus
. . . .         .          . | .          Dot        Comma Exclamation Question Slash
. . . .         .          . | .          DoubleQuote Colon Semicolon Equal Asterisk
                        ▽ ▽ ▽ | ▽ SPACE/RU-SMILES ▽
```

Holding position 40 opens `RUSSIAN_SMILES`; tapping sends Space. Other transparent thumbs first inherit from `RUSSIAN` and then, when needed, from `GRAPHITE`. Percent, Ruble Sign, and Plus from the omitted Voyager top row have not been relocated.

## 10 - Russian Smiles

```text
. . . . . . | . .  .  . . .
. . . . . . | . :) :( . . .
. . . . . . | . .  .  . . .
        ▽ ▽ ▽ | ▽ ▽ ▽
```

- Position 19: source `ST_MACRO_35`, `Shift+6` followed by `Shift+0`, produces `:)` under Russian-PC.
- Position 20: source `ST_MACRO_36`, `Shift+6` followed by `Shift+9`, produces `:(` under Russian-PC.
- Combo positions `5+17` (aliases `RU_PE+RU_IE`) hold this layer with `slow-release`; the English Smiles combo at the same positions has separate layer scope.

## 11 - System

This layer is active only while the left outer thumb at position 36 is held on any base layer, including Russian. The left hand controls five dongle host Bluetooth profiles; the right hand controls the independent OS profile, which also resides on the dongle.

```text
BT0  BT1  BT2  BT3  BT4  . | .       .       .      .      . .
.    .    .    .    .    . | .       WINDOWS MACOS  LINUX  . .
BTCLR.    .    .    .    . | .       .       .      .      . .
                 ▽  ▽  ▽    | ▽  ▽  ▽
```

- BT0-BT4: `&bt BT_SEL 0..4`.
- BT Clear: bottom outer-left corner, position 24. A short tap does nothing; an uninterrupted 1500 ms hold invokes `&bt BT_CLR`.
- OS selectors: positions 19-21 are Windows, macOS, and Linux. Position 18 remains empty, placing Windows under the index finger on the home row.
- Selecting an OS neither changes the layer nor selects a Bluetooth profile.

## Host-language setup and synchronization

Configure every host with:

- `Ctrl+Shift+1` to select the English layout directly;
- `Ctrl+Shift+2` to select Russian-PC directly.

Configure Windows, macOS, and Linux through their own OS facilities. On macOS, Hammerspoon can be used as in the source configuration. The firmware does not detect the language automatically or persist it to flash. If the language is changed with a mouse, another keyboard, or after a host reboot, invoking `->RU` or `->ENG` again restores the expected host-language and ZMK-layer pair.

## Temporary Russian Caps Word behavior

The HID usages represented by aliases `RU_HA`, `RU_HARD`, `RU_ZHE`, `RU_E`, `RU_BE`, `RU_YU`, and `RU_YO` are included in the built-in `&caps_word` `continue-list`, so those keys do not end Caps Word. ZMK v0.3 automatically applies Shift only to usages `A` through `Z`, however, so a normal tap of those seven positions remains lowercase. The remaining Russian letters are capitalized, and Caps Lock can capitalize all 33 letters.

Complete support for all Russian letters is deferred to the next OpenSpec change, `implement-russian-caps-word`, after hardware validation of this migration.
