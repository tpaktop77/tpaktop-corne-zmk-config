## Purpose

Сохраняет полезный минимальный nice!view-индикатор на каждой беспроводной половине без передачи слоя или декоративного интерфейса с central.

## ADDED Requirements

### Requirement: Обе половины собираются с nice!view
Прошивки `corne_left` и `corne_right` SHALL включать shields `nice_view_adapter` и `nice_view`, а донгл SHALL собираться без display shield.

#### Scenario: Состав build matrix
- **WHEN** запускается firmware workflow
- **THEN** оба peripheral targets включают nice!view, а dongle target является headless

### Requirement: Peripheral использует встроенный минимальный status screen
Каждая половина SHALL показывать собственный уровень заряда, признак USB-зарядки и состояние split-соединения с донглом через built-in ZMK status screen. Display updates MUST явно использовать dedicated ZMK work queue, а не системную очередь обработки.

#### Scenario: Половина подключена
- **WHEN** peripheral установила split-соединение с донглом
- **THEN** её nice!view показывает локальный заряд и connected status

#### Scenario: Половина отключена
- **WHEN** peripheral потеряла split-соединение
- **THEN** nice!view сохраняет локальный заряд и показывает disconnected status

#### Scenario: Половина получает USB-питание
- **WHEN** peripheral подключена к USB для зарядки
- **THEN** nice!view показывает признак зарядки

#### Scenario: Отрисовка экрана
- **WHEN** nice!view обновляет battery или connection status
- **THEN** LVGL update выполняется через явно выбранный dedicated display work queue

### Requirement: Лишнее состояние не отображается
Peripheral status screen MUST NOT показывать активный keymap layer, OS profile, host Bluetooth profile или декоративную картинку стандартного nice!view custom widget.

#### Scenario: Смена слоя на central
- **WHEN** пользователь меняет активный слой через донгл
- **THEN** содержимое peripheral status screen не пытается отобразить название слоя
