## REMOVED Requirements

### Requirement: ZMK Studio is available through the dongle
**Reason**: The maintained keymap is version-controlled and the owner no longer wants a Studio RPC endpoint or editable reserved layers in the dongle firmware.

**Migration**: Edit `config/corne.keymap` directly for future layout changes and build the dongle without the Studio RPC snippet or Studio Kconfig options.

## ADDED Requirements

### Requirement: Central services remain available without Studio
The dongle SHALL continue to provide keyboard HID, BLE host selection, positional keymap processing, macros, combos, Auto Shift, layer taps, and custom OS behaviors without enabling ZMK Studio. Removing Studio MUST NOT change the roles or firmware behavior of either peripheral half.

#### Scenario: Use the keyboard after Studio removal
- **WHEN** the updated dongle is flashed and either peripheral reports a key position
- **THEN** the dongle processes the existing version-controlled keymap and sends the same keyboard HID behavior without exposing a Studio RPC endpoint
