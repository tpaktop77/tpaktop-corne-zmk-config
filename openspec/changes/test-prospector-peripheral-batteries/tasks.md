# Tasks

## 1. Opt-in dongle experiment

- [x] 1.1 Save all nine original files in a recovery stash and create the approved branch from checked master 35ba98055905792a91f3e29ff203691781f8da2f; verify keymap/settings and pipeline have no diff from master.
- [x] 1.2 Enable fetching and the now explicitly requested host proxy only in the test branch's dongle configuration/equivalent fragment; document BLE-only host reporting, unchanged halves/Scanner, and hardware evidence.

## 2. Integration validation and handoff

- [ ] 2.1 Commit/push only the test branch and wait for all four unchanged GitHub Actions matrix targets; record actual results for the exact pushed commit.
- [ ] 2.2 Inspect GitHub source/config selection, all warnings, and existing artifact filenames, then provide the exact run and commit instead of local UF2 files.
- [x] 2.3 Run strict OpenSpec and whitespace checks and inspect the staged scope before committing; leave unresolved hardware acceptance open.

## 3. Owner hardware validation

- [ ] 3.1 Following the owner's report that GitHub fetching-only firmware works, verify full individual/simultaneous input after cold starts, half power cycles, and reconnects; do not count initial local failure or a single working report as full acceptance.
- [ ] 3.2 Owner verifies both battery values, physical left/right mapping, updates, and off/on/reboot behavior against each half's local display; records acceptance or rollback.
- [ ] 3.3 Owner records TPAK/Unknown behavior across Scanner/dongle cold boots, independent reboots, and repeated advertisements without treating this battery experiment as a name fix.
- [ ] 3.4 Owner verifies zmk-battery-center discovers both proxy levels over the existing BLE host connection and receives updates, while input and Prospector status remain reliable.

## Workflow follow-up

- Do not archive or promote production fetching until the owner's hardware evidence is reviewed.
- Any actual v0.3 discovery backport or Unknown fix requires its own evidence-backed scope; neither is implemented here.
