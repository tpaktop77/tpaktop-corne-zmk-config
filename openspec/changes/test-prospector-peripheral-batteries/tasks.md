# Tasks

## 1. Opt-in dongle experiment

- [x] 1.1 Save all nine original files in a recovery stash and create the approved branch from checked master 35ba98055905792a91f3e29ff203691781f8da2f; verify keymap/settings and pipeline have no diff from master.
- [x] 1.2 Enable fetching only in the test branch's dongle configuration with proxy n; document GitHub provenance and the earlier FAILED reliability test despite visible battery values.

## 2. Integration validation and handoff

- [ ] 2.1 Commit/push only the test branch and wait for all four unchanged GitHub Actions matrix targets; record actual results for the exact pushed commit.
- [ ] 2.2 Inspect GitHub source/config selection, all warnings, and existing artifact filenames, then provide the exact run and commit instead of local UF2 files.
- [x] 2.3 Run strict OpenSpec and whitespace checks and inspect the staged scope before committing; leave unresolved hardware acceptance open.

## 3. Owner hardware validation

- [ ] 3.1 Resolve the earlier FAILED input/settings test before acceptance; then owner verifies individual/simultaneous input after repeated cold starts, staggered starts, half power cycles, and dongle restarts over USB and the existing BLE host profile, recording zero connected-but-not-typing halves.
- [ ] 3.2 Owner verifies both battery values, physical left/right mapping, updates, and off/on/reboot behavior against each half's local display; records acceptance or rollback.
- [ ] 3.3 Owner records TPAK/Unknown behavior across Scanner/dongle cold boots, independent reboots, and repeated advertisements without treating this battery experiment as a name fix.

## Workflow follow-up

- Do not archive or promote production fetching until the owner's hardware evidence is reviewed.
- Any actual v0.3 discovery backport or Unknown fix requires its own evidence-backed scope; neither is implemented here.
