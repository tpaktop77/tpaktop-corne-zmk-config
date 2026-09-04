## Purpose

Определяет BLE split topology с отдельным центральным донглом и двумя периферийными половинами Corne, сохраняя пять независимых host-профилей.

## ADDED Requirements

### Requirement: Донгл является единственным central
Прошивка SHALL использовать отдельный `nice_nano_v2` без клавиш как ZMK split central, а `corne_left` и `corne_right` SHALL работать как BLE peripherals.

#### Scenario: Нажатие на левой половине
- **WHEN** пользователь нажимает клавишу на `corne_left`
- **THEN** позиционное событие передаётся донглу, обрабатывается его keymap и отправляется хосту

#### Scenario: Нажатие на правой половине
- **WHEN** пользователь нажимает клавишу на `corne_right`
- **THEN** позиционное событие передаётся тому же донглу и обрабатывается тем же keymap

#### Scenario: Работа без донгла
- **WHEN** донгл выключен или отсутствует
- **THEN** половины не отправляют keyboard HID непосредственно хосту

### Requirement: Central принимает две периферии и пять host-профилей
Central SHALL поддерживать ровно две split peripherals и пять доступных пользователю Bluetooth host profiles `BT0`–`BT4`; connection и pairing limits MUST учитывать обе группы.

#### Scenario: Одновременная split-связь
- **WHEN** обе половины включены и ранее сопряжены с донглом
- **THEN** central может одновременно держать соединение с обеими половинами и выбранным хостом

#### Scenario: Выбор host profile
- **WHEN** пользователь выбирает `BT0`–`BT4` на System layer
- **THEN** меняется host profile донгла, а pairing половин с central не заменяется

### Requirement: Получение заряда peripherals на central отложено
ZMK v0.3 central MUST NOT включать battery-level fetching или battery proxy для двух peripherals в этом change.

#### Scenario: Аудит central-конфигурации
- **WHEN** проверяется итоговый Kconfig донгла
- **THEN** fetching и proxy заряда split peripherals отключены
