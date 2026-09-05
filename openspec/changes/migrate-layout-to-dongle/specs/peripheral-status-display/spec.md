## Purpose

Preserves a useful minimal nice!view indicator on each wireless half without forwarding layer state or decorative UI from the central.

## ADDED Requirements

### Requirement: Both halves build with nice!view
The `corne_left` and `corne_right` firmware SHALL include the `nice_view_adapter` and `nice_view` shields, while the dongle SHALL build without a display shield.

#### Scenario: Inspect build matrix
- **WHEN** the firmware workflow starts
- **THEN** both peripheral targets include nice!view and the dongle target is headless

### Requirement: A peripheral uses the built-in minimal status screen
Each half SHALL show its own battery level, USB charging indicator, and split connection state using the built-in ZMK status screen. Display updates MUST explicitly use the dedicated ZMK work queue rather than the system work queue.

#### Scenario: Half is connected
- **WHEN** a peripheral establishes its split connection to the dongle
- **THEN** its nice!view shows local battery level and connected status

#### Scenario: Half is disconnected
- **WHEN** a peripheral loses its split connection to the dongle
- **THEN** its nice!view retains local battery information and shows disconnected status

#### Scenario: Half receives USB power
- **WHEN** a peripheral is connected to USB for charging
- **THEN** its nice!view shows the charging indicator

#### Scenario: Render the display
- **WHEN** nice!view updates battery or connection status
- **THEN** the LVGL update runs through the explicitly selected dedicated display work queue

### Requirement: Unnecessary state is not displayed
The peripheral status screen MUST NOT show the active keymap layer, OS profile, host Bluetooth profile, or decorative artwork from the standard nice!view custom widget.

#### Scenario: Change the layer on the central
- **WHEN** the user changes the active layer through the dongle
- **THEN** the peripheral status screen does not attempt to show the layer name
