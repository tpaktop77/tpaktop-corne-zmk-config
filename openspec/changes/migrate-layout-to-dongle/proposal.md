## Why

Текущая рабочая раскладка живёт в отдельном репозитории для Corne с nice!view и использует левую половину как central. Нужна независимая донгловая конфигурация, которая сохранит протестированную раскладку, перенесёт central-функции на отдельный `nice_nano_v2` и не изменит стабильный исходный репозиторий.

## What Changes

- Перенести version-controlled keymap, positional combo, русские слои, Auto Shift, OS profile и пользовательский ZMK-модуль из `tpaktop-corne-wireless-view-zmk-config` на зафиксированном исходном commit `e7d7c10`.
- Добавить headless shield донгла на `nice_nano_v2`: он становится единственным split central и владельцем keymap/HID, пяти host Bluetooth profiles, volatile OS profile и ZMK Studio.
- Собирать обе половины Corne как BLE peripherals с `nice_view_adapter nice_view`.
- Переключить nice!view половин на встроенный peripheral status screen: собственный заряд/зарядка и состояние связи с донглом, без layer status и декоративной картинки.
- Не включать получение или proxy заряда половин на донгле в ZMK v0.3.
- Добавить отдельную сборку `settings_reset` и документировать обязательный reset/re-pair всех трёх устройств при переходе.
- Добавить UTC timestamp формата `YYYYMMDD_HHMM` в имя объединённого firmware artifact; имена UF2 внутри архива оставить стабильными и однозначными.
- Сохранить три reserved layer для Studio и перенести Studio RPC с левой половины на донгл.
- **BREAKING**: донгловая прошивка не работает без донгла и требует очистки старых split/host bonds перед первым использованием.
- Не изменять репозитории `tpaktop-corne-wireless-view-zmk-config`, `nat-corne-zmk-config` и `oryx-with-custom-qmk`.

## Capabilities

### New Capabilities

- `layout-migration`: точный перенос текущей раскладки и пользовательского OS-модуля из стабильного view-репозитория с проверяемым source commit.
- `dongle-split-topology`: донгл `nice_nano_v2` как central и две Corne-половины как BLE peripherals.
- `peripheral-status-display`: минимальный nice!view status каждой половины только с локальным питанием и split-соединением.
- `central-services`: выполнение keymap, Bluetooth host profiles, OS profile и ZMK Studio на донгле.
- `firmware-packaging`: сборка трёх рабочих UF2, reset UF2 и объединённого архива с датой/временем.
- `dongle-provisioning`: безопасная последовательность settings reset, прошивки и повторного pairing.

### Modified Capabilities

Нет: целевой репозиторий пока не содержит OpenSpec baseline capabilities.

## Impact

- Целевой репозиторий: `tpaktop-corne-zmk-config`.
- Исходная конфигурация read-only: `tpaktop-corne-wireless-view-zmk-config@e7d7c10`.
- Затрагиваются `build.yaml`, GitHub Actions workflow, `config/`, корневой out-of-tree ZMK module, новый shield в `config/boards/shields/`, документация и OpenSpec artifacts.
- Используется закреплённый ZMK v0.3 и стандартный BLE dongle mechanism; новых внешних репозиториев и runtime-зависимостей не появляется.
- Аппаратная проверка потребует один `nice_nano_v2` для донгла, две Corne-половины с nice!view и проверки по USB/BLE.
