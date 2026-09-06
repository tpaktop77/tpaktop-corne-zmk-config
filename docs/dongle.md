# Dongle flashing, pairing, and rollback

This configuration uses the standard ZMK v0.3 BLE dongle mode. A dedicated `nice_nano_v2` acts as the central and connects to a computer over USB or through one of five Bluetooth profiles. Both Corne halves are BLE peripherals and cannot send keys to a host without the dongle.

Official references:

- [Keyboard Dongle](https://zmk.dev/docs/development/hardware-integration/dongle)
- [Split Keyboards](https://zmk.dev/docs/features/split-keyboards)
- [Connection Issues / settings reset](https://zmk.dev/docs/troubleshooting/connection-issues)

## Firmware artifact contents

GitHub Actions creates an archive named like this:

```text
corne-dongle-firmware_YYYYMMDD_HHMM.zip
```

The timestamp is UTC. The archive contains stable filenames:

| File | Flash destination |
|---|---|
| `tpaktop-corne-dongle.uf2` | dedicated `nice_nano_v2` dongle |
| `corne-left-peripheral.uf2` | left Corne controller |
| `corne-right-peripheral.uf2` | right Corne controller |
| `settings-reset-nice-nano-v2.uf2` | each of the three controllers in turn before first installation or bond recovery |

Do not flash a dongle, left, or right UF2 to a different device: the split role is part of the firmware.

## First migration to the dongle

The old firmware stores bonds for a topology with the left half as central. A normal firmware update does not erase them, so all three devices require a reset.

1. Download and extract the latest timestamped artifact.
2. Put the dongle into its bootloader, copy `settings-reset-nice-nano-v2.uf2` to it, and allow it to reboot.
3. Repeat the settings reset separately on the left and right halves.
4. Open the dongle bootloader again and flash `tpaktop-corne-dongle.uf2`.
5. Flash `corne-left-peripheral.uf2` to the left half.
6. Flash `corne-right-peripheral.uf2` to the right half.
7. Connect the dongle to the computer over USB, then power on both halves.
8. Confirm that both nice!view displays show connected status; initial split pairing can take several seconds.
9. Test input from each half and a cross-half combo through the USB dongle.
10. For BLE, select an unused `BT0`-`BT4` profile on the System layer and pair the computer with the dongle itself.

## nice!view contents

Each display represents only its own half and shows:

- local battery percentage;
- USB charging status;
- connected or disconnected state for the dongle link.

The halves do not receive the active layer, OS profile, host Bluetooth profile, or the other half's battery level. The decorative nice!view custom widget is disabled in favor of ZMK's built-in status screen. `CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y` is set explicitly, so LVGL updates run on a dedicated display work queue rather than the system queue.

## Bluetooth and OS profile

- `BT0`-`BT4` select host profiles on the central dongle.
- The two split bonds occupy separate central connections and are not host profiles.
- Windows, macOS, or Linux is an independent in-memory dongle state.
- After reboot, the OS profile returns to Windows and the base layer returns to Graphite.
- Changing a Bluetooth profile does not change the OS profile, and vice versa.

## If a half does not connect

1. Leave the dongle connected over USB and restart the affected half.
2. Confirm that the correct peripheral UF2 is installed on that half.
3. If the link does not recover, repeat the complete settings reset on all three devices rather than on only one half.
4. Reinstall the three operational UF2 files in dongle, left, right order.

Battery-level fetching and proxy are intentionally disabled on the central: the dongle does not retrieve half battery levels, and each nice!view reads its own local battery.

## Updating the 6-column mapping fix

Both peripheral images explicitly disable the alternative in-tree `5 Column` layout, leaving only the full Corne `6 Column` layout enabled. If dongle topology is already installed and both halves connect, update by flashing new `corne-left-peripheral.uf2` and `corne-right-peripheral.uf2` files and restarting the halves. This update does not require another settings reset or dongle reflash.

## Rollback to the configuration without a dongle

This migration does not modify the stable `tpaktop-corne-wireless-view-zmk-config` repository.

1. Download the latest successful left/right firmware from the view repository.
2. Flash `settings_reset` to both halves and allow it to boot.
3. Flash the previous central-left and peripheral-right UF2 files.
4. Repeat split and host pairing for the previous configuration.

The dongle can be powered off after rollback; its settings do not affect the restored halves.
