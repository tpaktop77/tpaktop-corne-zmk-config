# Proposal

## Why

Prospector cannot show the two Corne battery levels while fetching is disabled on the dongle. The owner has authorized a reversible hardware experiment, not production enablement or a claim that ZMK v0.3 is reliable with fetching enabled.

## What Changes

- Publish the isolated test branch from checked master and enable fetching only in that branch's dongle config; retain the separate fragment.
- Use the unchanged four-target GitHub pipeline and artifact names; identify test firmware by branch, commit, and run. Record the earlier hardware reliability test as FAILED despite visible battery values.
- Keep fetching disabled on master and battery proxy disabled in every variant. Reconcile the old blanket restriction with a narrowly scoped, unvalidated experiment.
- Record the already implemented Prospector identity/topology requirements without claiming to fix the separate `Unknown` defect.

## Capabilities

### New Capabilities

- `prospector-status-advertisements`: Central-only observer advertisements with the existing TPAK/AUX/two-peripheral identity, plus an opt-in battery experiment.

### Modified Capabilities

- `dongle-split-topology`: Retain the production fetching/proxy restriction while permitting a separately selected and named test of fetching alone.

## Impact

Only the keyboard configuration repository changes. ZMK stays at v0.3 (`edf5c0814fd3ea202e43aad2d68fd32e882a518c`) and Prospector module v2.2.3 (`72a71aeea816eb0f86ffc5b108b267076ce5f0af`). The halves, Scanner repository, keymap, OS behavior, normal build matrix, host profiles, and bond/settings design remain untouched.

Non-goals: fixing `Unknown`, backporting an unvalidated upstream PR, upgrading dependencies, automatically flashing hardware, resetting settings, changing the pipeline or matrix, or opening a PR. Commit/push of this test branch is explicitly authorized.
