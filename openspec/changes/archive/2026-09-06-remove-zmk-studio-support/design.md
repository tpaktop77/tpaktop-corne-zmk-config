## Context

The dongle is the split central and currently receives `studio-rpc-usb-uart`, explicitly enables `CONFIG_ZMK_STUDIO`, and exposes three reserved keymap nodes after `SYSTEM_BT`. The merged and hardware-tested `add-sym-num-layer` change established the functional order through `SYM_NUM=11` and `SYSTEM_BT=12`; it has been synchronized into the main specs and archived before this change.

Current documentation also describes Studio as a runtime feature. Archived migration artifacts are immutable historical records and can continue to mention the feature that existed at that revision.

## Goals / Non-Goals

**Goals:**

- Remove the Studio RPC and explicit Studio Kconfig settings from the dongle.
- Remove only the three Studio-reserved keymap nodes and constants.
- Preserve the tested 13 functional layers in exact index and node order.
- Make current operating documentation describe the configuration without Studio.
- Prove that all four firmware targets still build.

**Non-Goals:**

- Changing any functional binding, timing, behavior implementation, display setting, split role, radio setting, USB keyboard HID setting, or BLE setting.
- Removing generic custom-behavior metadata code, because behavior implementation is explicitly outside this task and the code is harmless when Studio metadata support is not selected.
- Rewriting archived OpenSpec history.

## Decisions

### 1. Remove Studio at its two explicit activation points

The dongle build loses the `studio-rpc-usb-uart` snippet, and `config/tpaktop_corne_dongle.conf` loses `CONFIG_ZMK_STUDIO=y` and `CONFIG_ZMK_STUDIO_LOCKING=n`. This removes the endpoint without changing USB keyboard HID or the dongle's central role. Disabling Studio indirectly while retaining those declarations was rejected because it would leave misleading and potentially version-sensitive configuration.

### 2. Delete reserved nodes instead of replacing them

`STUDIO_EXTRA_1..3` and their `status = "reserved"` nodes are Studio-only capacity. They are deleted outright. The existing functional indices already end at `SYSTEM_BT=12`, so compaction means preserving indices 0–12 and ensuring no trailing nodes remain; no functional reference needs renumbering.

### 3. Preserve all behavior code and functional configuration

The requested boundary forbids unrelated behavior changes. Custom OS behavior parameter metadata is not removed even though it was originally added for Studio: changing behavior sources would expand risk and it does not enable Studio by itself. A protected-scope diff check will cover dongle topology, display, BLE/split configuration, macros, combos, and behavior sources.

### 4. Update maintained documentation, preserve historical archives

Current files under `docs/` will no longer advertise Studio builds, connection tests, or reserved layers. Archived OpenSpec changes record what was true when they were implemented and will not be rewritten. The new change artifacts explicitly document removal, so repository searches can distinguish current configuration from history.

### 5. Validate the complete build matrix

Static checks will verify exact layer constants/node order, 42 bindings for every functional layer, absence of live Studio activation settings, and an otherwise narrow diff. GitHub Actions will build the dongle, left peripheral, right peripheral, and settings-reset targets because local dependency installation or container workflows are not introduced by this task.

## Risks / Trade-offs

- [Stale documentation continues to imply Studio support] -> Search all current source and docs using the supplied Studio terms and remove or rewrite each live claim.
- [A broad text cleanup damages historical provenance] -> Exclude `openspec/changes/archive/` from modification and treat its Studio references as historical evidence.
- [Layer deletion shifts a functional index] -> Assert constants and node order structurally and verify `SYSTEM_BT` remains index 12.
- [Removing the RPC snippet accidentally affects keyboard USB] -> Leave all USB HID and dongle configuration untouched and build every target in CI.
- [Historical requirements are mistaken for current behavior] -> Keep completed changes under `openspec/changes/archive/` and use the main specs plus this active delta as the current contract.

## Migration Plan

1. Remove the Studio snippet and explicit Studio Kconfig lines.
2. Remove Studio-only constants and reserved nodes while retaining functional indices 0–12.
3. Clean current documentation of Studio availability and update the layout table to 13 layers.
4. Run static validation and all firmware builds.
5. Flash only the dongle for hardware validation; peripheral firmware is functionally unchanged.
6. Roll back by reflashing the previous dongle artifact if Studio access is needed again.
