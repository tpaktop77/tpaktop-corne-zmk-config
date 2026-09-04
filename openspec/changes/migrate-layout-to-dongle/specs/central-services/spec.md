## Purpose

Закрепляет все зависящие от keymap и хоста службы за донглом, чтобы периферийные половины оставались простыми источниками физических позиций.

## ADDED Requirements

### Requirement: Keymap и пользовательские behaviors выполняются на central
Донгл SHALL владеть keymap processing, positional combo, macros, Auto Shift, Bluetooth behaviors и пользовательскими `&os_set`/`&os_action`; peripherals SHALL передавать физические события central.

#### Scenario: Combo между половинами
- **WHEN** chord содержит позиции с левой и правой половины
- **THEN** central распознаёт positional combo по общему 42-key transform

#### Scenario: OS-aware action
- **WHEN** combo вызывает `&os_action`
- **THEN** HID press/release формируется донглом согласно текущему volatile OS profile без stuck modifiers

### Requirement: ZMK Studio доступна через донгл
ZMK Studio SHALL быть включена на central и доступна через USB RPC донгла; Studio snippet MUST NOT назначаться левой или правой peripheral firmware.

#### Scenario: Подключение Studio
- **WHEN** донгл подключён к компьютеру по USB и открыт ZMK Studio
- **THEN** Studio видит полный Corne physical layout и все version-controlled layers, включая три reserved layer

### Requirement: OS profile остаётся независимым и volatile
Смена topology MUST NOT менять модель OS profile: Windows SHALL быть default после reboot, профиль MUST NOT храниться во flash и MUST NOT связываться с host Bluetooth profile.

#### Scenario: Перезапуск после выбора macOS
- **WHEN** пользователь выбирает macOS и перезапускает донгл
- **THEN** OS profile возвращается в Windows, а активный keymap base возвращается в Graphite

#### Scenario: Смена BT profile
- **WHEN** пользователь выбирает другой `BT0`–`BT4`
- **THEN** текущее состояние OS profile не меняется
