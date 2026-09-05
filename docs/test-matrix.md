# Test matrix

Statuses:

- `manual pending` means the physical-keyboard owner must run the test; Codex does not mark it complete.
- `pass` or `fail` records a confirmed result with evidence.

## Static and OpenSpec

| Check | Method | Expected result | Status | Evidence |
|---|---|---|---|---|
| OpenSpec planning | `openspec status --change migrate-layout-to-dongle` | 4/4 artifacts complete | pass | proposal, design, six specs, and tasks exist |
| OpenSpec strict | `openspec validate migrate-layout-to-dongle --strict` | valid, zero issues | pass | `Change 'migrate-layout-to-dongle' is valid` |
| Source provenance | `git rev-parse` in the source clone | source is `e7d7c10a2b5193f777c4907fc70111ddc94d18b8` | pass | source master checked before migration |
| Baseline behavior parity | source checksum plus focused diff | keymap/module bindings and timings match the source commit; only comments differ | pass | pre-translation `corne.keymap` SHA-256 `5f91722b4c530fb4bf88bbd86a0fb42feda272a2181468412d3f3504c5b9ff8c`; final keymap diff is comment-only |
| English-only tracked text | full-tree Unicode Cyrillic-range `rg` search | no matches | pass | zero matching tracked files after translation |
| Whitespace | `git diff --check` | no output, exit 0 | pass | exit 0, no output |
| Layer sizes | structural script | 42 bindings on every active layer | pass | Graphite through System: 12 x 42 |
| Named layer references | `rg` audit | no unexplained numeric layer references | pass | named references preserved from the source baseline |
| Layer priority | structural audit | `GRAPHITE 0`, `QWERTY 1`, `RUSSIAN 2`; overlays above bases; node order matches defines | pass | 15 named defines and the tested node order are preserved |
| Dongle transform | token comparison with in-tree ZMK v0.3 Corne | the same 42 `RC(row,col)` tokens in the same order | pass | 42/42 token exact match |
| Peripheral physical layout | compiled Devicetree for both halves | `5 Column` disabled; `6 Column` uses the 42-position `default_transform`; no left offset and right `col-offset = 6` | pass | [left job 101220172228](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172228), [right job 101220172360](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172360) |
| YAML syntax | Node `yaml` parser | `build.yaml` and the workflow parse without errors | pass | both YAML structures parsed |
| Exclusions | `rg` audit | no battery proxy/fetching, layout behavior changes, or Studio snippet on peripherals | pass | fetching/proxy explicitly `n`; one Studio snippet only on the dongle |
| Display queue | Kconfig audit | built-in nice!view updates use the dedicated queue | pass | `CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y`; system queue not selected |

## Build matrix

| Configuration | Expected result | Status | Evidence |
|---|---|---|---|
| `nice_nano_v2 + tpaktop_corne_dongle + studio-rpc-usb-uart` | successful central UF2 build | pass | [job 101220172259](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172259) |
| `nice_nano_v2 + corne_left + tpaktop_corne_6col + nice_view_adapter + nice_view`, peripheral role | successful left UF2 build | pass | [job 101220172228](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172228) |
| `nice_nano_v2 + corne_right + tpaktop_corne_6col + nice_view_adapter + nice_view`, peripheral role | successful right UF2 build | pass | [job 101220172360](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172360) |
| `nice_nano_v2 + settings_reset` | successful reset UF2 build | pass | [job 101220172257](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598/job/101220172257) |
| merged artifact | four unambiguously named UF2 files in `corne-dongle-firmware_YYYYMMDD_HHMM.zip` | pass | [run 33934665598](https://github.com/tpaktop77/tpaktop-corne-zmk-config/actions/runs/33934665598), artifact `corne-dongle-firmware_20260905_0057`, SHA-256 `2024d0fbeb8b498e8dee1e5655a09e8d490e47e38834e2a548a1d33380853e9f` |

## Layout and switching

| Check | Transport | Expected result | Status |
|---|---|---|---|
| Reboot default | USB and BLE | Graphite active; QWERTY not selected | manual pending |
| Graphite 26 letters | USB and BLE | three rows match Oryx; Num Lock at position 6 | manual pending |
| Graphite Escape | USB and BLE | position 0 sends Escape | manual pending |
| Graphite empty positions | USB and BLE | positions 11, 12, 23, and 32-34 send no keycodes | manual pending |
| Graphite to Russian | USB and BLE | position 24 sends Ctrl+Shift+2 and directly selects Russian | manual pending |
| Graphite to QWERTY | USB and BLE | position 35 directly selects QWERTY | manual pending |
| QWERTY 26 letters | USB and BLE | only standard English letters | manual pending |
| QWERTY forbidden body keys | USB and BLE | no Tab, Escape, Ctrl, Shift, or punctuation | manual pending |
| QWERTY to Graphite | USB and BLE | position 35 directly returns to Graphite | manual pending |
| Reboot from QWERTY | USB and BLE | Graphite is active again after reboot | manual pending |

## Russian layout and host language

Precondition on each Windows, macOS, and Linux host: `Ctrl+Shift+1` directly selects English and `Ctrl+Shift+2` directly selects Russian-PC. Repeat functional rows over USB and BLE, and exercise keys from both halves separately.

| Check | Transport/OS | Expected result | Status |
|---|---|---|---|
| Russian 33 letters | USB/BLE, Windows | positions 1-11, 13-23, and 25-35 produce the lowercase alias sequence `RU_SHTI..RU_HA / RU_EF..RU_E / RU_YA..RU_HARD` under Russian-PC | manual pending |
| Russian 33 letters | USB/BLE, macOS | the same positional output under Russian-PC | manual pending |
| Russian 33 letters | USB/BLE, Linux | the same positional output under Russian-PC | manual pending |
| Russian position 0 fallback | USB/BLE | transparent key sends Graphite Escape | manual pending |
| Russian position 12 fallback | USB/BLE | transparent key falls through to Graphite none and sends nothing | manual pending |
| Graphite language combo | USB/BLE | positions 7+8+9 send Ctrl+Shift+2 and activate Russian | manual pending |
| Russian language combo | USB/BLE | positions 7+8+9 send Ctrl+Shift+1 and activate Graphite | manual pending |
| Russian to Graphite | USB/BLE | position 24 performs the same directed exit | manual pending |
| QWERTY independence | USB/BLE | language combo is not enabled on QWERTY; Russian exit always targets Graphite | manual pending |
| External host-language change | USB/BLE | after deliberate desynchronization, a directed enter/exit action restores the expected layer/language pair | manual pending |
| Reboot from Russian | USB/BLE | base layer returns to Graphite and OS profile returns to Windows; host language is not claimed synchronized until a macro runs | manual pending |

## Russian Symbols and Smiles

| Check | Transport | Expected result | Status |
|---|---|---|---|
| Russian Symbols row 0 | USB/BLE | positions 3, 4, and 6-11 produce LeftParen, RightParen, NumberSign, Underscore, Minus, Slash, Backslash, Minus under Russian-PC | manual pending |
| Russian Symbols row 1 | USB/BLE | positions 19-23 produce Dot, Comma, Exclamation, Question, Slash under Russian-PC | manual pending |
| Russian Symbols row 2 | USB/BLE | positions 31-35 produce DoubleQuote, Colon, Semicolon, Equal, Asterisk under Russian-PC | manual pending |
| Symbols top-row exclusions | USB/BLE | Percent, Ruble Sign, and Plus were not moved to new positions | manual pending |
| Symbols transparent thumbs | USB/BLE | positions 36-39 and 41 inherit Russian; tapping position 40 sends Space | manual pending |
| Russian Smiles thumb hold | USB/BLE | holding position 40 on Symbols opens Russian Smiles until release | manual pending |
| Russian smile happy | USB/BLE | Russian Smiles position 19 sends `:)` | manual pending |
| Russian smile sad | USB/BLE | Russian Smiles position 20 sends `:(` | manual pending |
| Russian Smiles combo | USB/BLE | Russian positions 5+17 hold Russian Smiles until the last key is released | manual pending |

## Thumb layer-tap

Test separately on Graphite, QWERTY, and Russian over USB and BLE. On Russian, position 37 opens Russian Symbols; all other assignments match.

| Position | Tap | Hold | Expected result | Status |
|---:|---|---|---|---|
| 36 | none | System | layer remains active only until release | manual pending |
| 37 | Backspace | Symbols | tap repeats through quick-tap; hold opens Symbols | manual pending |
| 38 | Delete | Numbers | tap deletes; hold opens Numbers | manual pending |
| 39 | Tab | Function | tap sends Tab; hold opens Function | manual pending |
| 40 | Space | Navigation | tap sends Space; hold opens Navigation | manual pending |
| 41 | none | none | nothing happens | manual pending |

### Russian thumb-cluster regression

PR #5 built successfully, but on hardware `RUSSIAN = 9` masked the lower `NAVIGATION = 3`. After the fix, repeat every row over USB and BLE. Graphite and QWERTY checks confirm that their previous behavior remains intact.

| Position | Hold target | Check on Russian | Before fix | USB after fix | BLE after fix |
|---:|---|---|---|---|---|
| 36 | System | BT0-BT4 and OS selectors are visible; release returns to Russian | not tested | manual pending | manual pending |
| 37 | Russian Symbols | Russian-PC symbols are visible; tap remains Backspace | worked | manual pending | manual pending |
| 38 | Numbers | digits are visible; tap remains Delete | not tested | manual pending | manual pending |
| 39 | Function | F-keys are visible; tap remains Tab | not tested | manual pending | manual pending |
| 40 | Navigation | arrows/navigation override Russian letters; tap remains Space | fail: remained on Russian | manual pending | manual pending |
| 41 | none | nothing happens | not tested | manual pending | manual pending |

Additionally, holding position 40 on `RUSSIAN_SYMBOLS` SHALL open `RUSSIAN_SMILES` and return to Symbols on release; verify over USB and BLE (`manual pending`).

## Auto Shift

| Check | Layout | Transport | Expected result | Status |
|---|---|---|---|---|
| tap each letter for less than 300 ms | Graphite | USB/BLE | lowercase/plain keycode | manual pending |
| hold each letter for more than 300 ms | Graphite | USB/BLE | Shift plus the same letter | manual pending |
| tap each letter for less than 300 ms | QWERTY | USB/BLE | lowercase/plain keycode | manual pending |
| hold each letter for more than 300 ms | QWERTY | USB/BLE | Shift plus the same letter | manual pending |
| normal fast typing | Graphite/QWERTY/Russian | USB/BLE | no false uppercase letters previously observed at 250 ms | manual pending |
| digits, Num Lock, thumbs, function keys, symbols | all | USB/BLE | Auto Shift does not apply | manual pending |
| quick-tap Backspace | Graphite/QWERTY/Russian | USB/BLE | `&lt.quick-tap-ms = 250` and deletion auto-repeat are unchanged | manual pending |
| tap each of 33 Russian positions for less than 300 ms | Russian | USB/BLE | lowercase Russian-PC output | manual pending |
| hold each of 33 Russian positions for more than 300 ms | Russian | USB/BLE | Shift plus the same usage produces uppercase output | manual pending |
| Russian symbols, smiles, thumbs, language actions | Russian | USB/BLE | Auto Shift does not apply | manual pending |

## Regular and layer-action combos

Test every compatible base row on Graphite, QWERTY, and Russian using the same physical positions; arithmetic combos are Numbers-only. Normal fast typing on all three layouts must not trigger false combos.

| Combo | Positions | Scope | Expected result | USB | BLE |
|---|---|---|---|---|---|
| Enter | 19 20 21 | Graphite/QWERTY/Russian | Enter | manual pending | manual pending |
| Tab | 14 15 16 | Graphite/QWERTY/Russian | Tab | manual pending | manual pending |
| Caps Word | 13 16 | Graphite/QWERTY/Russian | toggle Caps Word | manual pending | manual pending |
| Caps Lock | 13 17 | Graphite/QWERTY/Russian | Caps Lock | manual pending | manual pending |
| Smiles | 5 17 | Graphite/QWERTY | momentary Smiles until full release | manual pending | manual pending |
| Russian Smiles | 5 17 | Russian | momentary Russian Smiles until full release | manual pending | manual pending |
| Vim | 19 22 | Graphite/QWERTY | one-shot Vim | manual pending | manual pending |
| Vim positions | 19 22 | Russian | Vim does not activate | manual pending | manual pending |
| To Russian | 7 8 9 | Graphite | Ctrl+Shift+2, then Russian | manual pending | manual pending |
| To English | 7 8 9 | Russian | Ctrl+Shift+1, then Graphite | manual pending | manual pending |
| Minus | 7 8 9 | Numbers only | `-` | manual pending | manual pending |
| Equal | 19 20 21 | Numbers only | `=` | manual pending | manual pending |
| Plus | 31 32 33 | Numbers only | `+` | manual pending | manual pending |
| Slash | 19 20 21 22 | Numbers only | `/` | manual pending | manual pending |
| Asterisk | 31 32 33 34 | Numbers only | `*` | manual pending | manual pending |
| arithmetic positions outside Numbers | same | other layers | combo does not trigger | manual pending | manual pending |

## Slow-release modifier combos

For every row: the chord presses the modifier; releasing one source key retains it; releasing the last source key releases it; no modifier remains stuck afterward.

| Combo | Positions | Modifier | Graphite | QWERTY | Russian | USB/BLE |
|---|---|---|---|---|---|---|
| Left Alt | 13 25 | LALT | manual pending | manual pending | manual pending | manual pending |
| Left GUI | 14 26 | LGUI | manual pending | manual pending | manual pending | manual pending |
| Left Shift | 15 27 | LSHIFT | manual pending | manual pending | manual pending | manual pending |
| Left Ctrl | 16 28 | LCTRL | manual pending | manual pending | manual pending | manual pending |
| Right Ctrl | 19 31 | RCTRL | manual pending | manual pending | manual pending | manual pending |
| Right Shift | 20 32 | RSHIFT | manual pending | manual pending | manual pending | manual pending |
| Right GUI | 21 33 | RGUI | manual pending | manual pending | manual pending | manual pending |
| Right Alt | 22 34 | RALT | manual pending | manual pending | manual pending | manual pending |

Pay particular attention to Right Shift, GUI, and Alt: underlying Graphite positions 32-34 are `&none`, but the combos must still work.

## Overlapping combos

| Short | Long | Transport | Expected result | Status |
|---|---|---|---|---|
| Copy 2+14 | Cut 2+3+14+15 | USB | Cut does not invoke Copy/Paste | manual pending |
| Copy 2+14 | Cut 2+3+14+15 | BLE | Cut does not invoke Copy/Paste | manual pending |
| Equal 19+20+21 | Slash 19+20+21+22 | USB/BLE | Slash does not emit Equal | manual pending |
| Plus 31+32+33 | Asterisk 31+32+33+34 | USB/BLE | Asterisk does not emit Plus | manual pending |
| Enter 19+20+21 | App Switch 19+20+21+22 | USB/BLE | App Switch does not emit Enter | manual pending |
| Tab/Word Backspace/Caps Word | Task View 13+14+15+16 | USB/BLE | only Task View executes | manual pending |
| short chord only | any pair | USB/BLE | the short combo resolves after overlap handling | manual pending |
| normal fast text | Graphite/QWERTY | USB/BLE | no false combos | manual pending |
| normal fast text | Russian | USB/BLE | no false combos | manual pending |
| delayed fourth key | each four-key overlap | USB/BLE | a fourth key arriving 51-79 ms after the first invokes only the four-key combo | manual pending |

Concurrent active-combo capacity:

| Check | Transport | Expected result | Status |
|---|---|---|---|
| four held modifier combos, then Smiles combo | USB/BLE | Smiles activates as the fifth concurrent combo; source positions do not emit letters | manual pending |

## System/Bluetooth

| Check | Expected result | Status |
|---|---|---|
| hold left outer thumb | System opens momentarily | manual pending |
| BT0 | profile 0 selected; OS unchanged | manual pending |
| BT1 | profile 1 selected; OS unchanged | manual pending |
| BT2 | profile 2 selected; OS unchanged | manual pending |
| BT3 | profile 3 selected; OS unchanged | manual pending |
| BT4 | profile 4 selected; OS unchanged | manual pending |
| BT Clear tap shorter than 1500 ms | profile is not cleared | manual pending |
| BT Clear plus another key before 1500 ms | profile is not cleared | manual pending |
| BT Clear hold at least 1500 ms | `BT_CLR` executes | manual pending |
| release System thumb | layer closes | manual pending |
| OS selector positions | position 18 does nothing; positions 19/20/21 select Windows/macOS/Linux | manual pending |

## OS profile and actions

Select a profile on System, then invoke every positional combo on Graphite, QWERTY, and Russian. For the release-sensitive check, hold an action, artificially change profile, release the action, and confirm there are no stuck modifiers.

| Action | Windows | macOS | Linux | USB | BLE |
|---|---|---|---|---|---|
| COPY | Ctrl+C | GUI+C | Ctrl+Insert | manual pending | manual pending |
| PASTE | Ctrl+V | GUI+V | Shift+Insert | manual pending | manual pending |
| CUT | Ctrl+X | GUI+X | Shift+Delete | manual pending | manual pending |
| UNDO | Ctrl+Z | GUI+Z | Ctrl+Z | manual pending | manual pending |
| REDO | Ctrl+Shift+Z | GUI+Shift+Z | Ctrl+Shift+Z | manual pending | manual pending |
| SELECT_ALL | Ctrl+A | GUI+A | Ctrl+A | manual pending | manual pending |
| WORD_PREVIOUS | Ctrl+Left | Alt+Left | Ctrl+Left | manual pending | manual pending |
| WORD_NEXT | Ctrl+Right | Alt+Right | Ctrl+Right | manual pending | manual pending |
| WORD_BACKSPACE | Ctrl+Backspace | Alt+Backspace | Ctrl+Backspace | manual pending | manual pending |
| WORD_DELETE | Ctrl+Delete | Alt+Delete | Ctrl+Delete | manual pending | manual pending |
| APP_SWITCH | Alt+Tab | GUI+Tab | Alt+Tab | manual pending | manual pending |
| TASK_VIEW | GUI+Tab | Ctrl+Up | GUI+Tab | manual pending | manual pending |
| VOICE | GUI+H | `C_VOICE_COMMAND` | GUI+H | manual pending | manual pending |

Additional state tests:

| Check | Expected result | Status |
|---|---|---|
| reboot after macOS/Linux | profile returns to Windows | manual pending |
| select OS profile | active keymap layer does not change | manual pending |
| Graphite to/from QWERTY | OS profile does not change | manual pending |
| BT0-BT4 | OS profile does not change | manual pending |
| language macro | OS and Bluetooth profiles do not change | manual pending |
| OS selector while Russian is active | Russian layer and host language do not change | manual pending |
| action press, OS change, action release | original HID code is released; no stuck modifiers | manual pending |
| macOS Voice | consumer usage 0xCF invokes Siri/voice | manual pending |

## Split, nice!view, and Studio

| Check | Expected result | Status |
|---|---|---|
| dongle central cold boot | accepts both previously paired peripherals after startup | manual pending |
| left peripheral half | every position reaches the dongle central; no reset/disconnect | manual pending |
| right peripheral half | every position reaches the same central; no reset/disconnect | manual pending |
| initial peripheral mapping, 2026-09-05 | after a complete settings reset, right home row expected `YHAEI` but produced `TSGYH`; left showed the matching shift | fail: both halves used 5-column mapping |
| fixed 6-column mapping | left home row is `none NRTSG`, right home row is `YHAEI`; outer columns and thumbs are not shifted | manual pending after flashing new left/right UF2 files |
| cross-half combo | a chord containing positions from both hands is recognized once by the central | manual pending |
| operation without dongle | halves do not send keyboard HID directly to the host | manual pending |
| reconnect left | left reconnects to the central after a power cycle | manual pending |
| reconnect right | right reconnects to the central after a power cycle | manual pending |
| nice!view left | local percentage/charging/link; no layer/art/host profile; display updates do not delay input | manual pending |
| nice!view right | local percentage/charging/link; no layer/art/host profile; display updates do not delay input | manual pending |
| ZMK Studio USB | connects through the dongle central snippet | manual pending |
| Studio reserved layers | three reserved entries are available | manual pending |
| Studio Russian layers | display names Russian, Russian Symbols, and Russian Smiles are visible; three reserved entries remain | manual pending |
| Studio custom OS metadata | `Set OS Profile` offers Windows/macOS/Linux and `OS Action` offers all 13 named actions; valid assignments are accepted | manual pending |
| duplicate OS action positions | assign the same OS action to two positions and overlap their presses/releases; both invocations remain independent with no stuck modifier | manual pending |
| Studio source of truth | reboot restores version-controlled behaviors and combos | manual pending |

## Provisioning, endpoints, and packaging

| Check | Expected result | Status |
|---|---|---|
| settings reset dongle | reset UF2 clears previous bonds before operational firmware | manual pending |
| settings reset left | reset UF2 clears the previous central-left topology | manual pending |
| settings reset right | reset UF2 clears the previous peripheral bond | manual pending |
| firmware mapping | dongle/left/right UF2 files are flashed only to their corresponding devices | manual pending |
| USB endpoint | input from both halves arrives through the connected USB dongle | manual pending |
| BLE endpoint | host is paired with the dongle; input from both halves arrives through selected `BT0`-`BT4` | manual pending |
| five host profiles | BT0-BT4 select independently without displacing split bonds | manual pending |
| timestamp | downloaded archive name matches UTC `corne-dongle-firmware_YYYYMMDD_HHMM.zip` | pass: `corne-dongle-firmware_20260905_0057` |
| stable filenames | archive contains documented dongle, left, right, and settings-reset names | pass: `tpaktop-corne-dongle.uf2`, `corne-left-peripheral.uf2`, `corne-right-peripheral.uf2`, `settings-reset-nice-nano-v2.uf2` |
| rollback | after another reset, previous view firmware restores central-left topology | manual pending |

## Temporary Russian Caps Word

This is an intentionally limited test of the built-in ZMK v0.3 `continue-list`, not a test of complete custom behavior.

| Check | Transport | Expected result | Status |
|---|---|---|---|
| Caps Word plus ordinary HID A-Z-backed Russian positions | USB/BLE | corresponding Russian-PC output is automatically uppercase | manual pending |
| Caps Word plus `RU_HA` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_HARD` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_ZHE` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_E` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_BE` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_YU` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus `RU_YO` | USB/BLE | output remains lowercase, but mode continues | manual pending |
| Caps Word plus exception plus an A-Z-backed position | USB/BLE | the next supported Russian-PC output is still automatically uppercase | manual pending |
| Caps Lock plus all 33 letters | USB/BLE | host Caps Lock makes all positions produce uppercase output | manual pending |
| Custom Russian Caps Word | source audit | absent; next change is `implement-russian-caps-word` | deferred |
