## 1. Перенос проверенного baseline

- [x] 1.1 Перенести keymap, west manifest и корневой out-of-tree OS-profile module из `tpaktop-corne-wireless-view-zmk-config@e7d7c10`; проверить точное совпадение переносимых исходников через `sha256sum`/`diff`.
- [x] 1.2 Перенести пользовательскую документацию раскладки и тестов, добавить provenance целевого репозитория и проверить отсутствие ссылок, ошибочно объявляющих старую central-left topology актуальной.

## 2. Dongle topology и конфигурация устройств

- [x] 2.1 Добавить shield `tpaktop_corne_dongle` для `nice_nano_v2` с mock kscan, 42-key Corne transform, physical layout, двумя peripherals и лимитами 7/7; проверить структуру overlay и Kconfig по ZMK v0.3.
- [x] 2.2 Подключить общий `corne.keymap` и central-only config к dongle target; проверить, что Studio и пользовательские OS behaviors принадлежат central.
- [x] 2.3 Настроить `corne_left` и `corne_right` как BLE peripherals с nice!view built-in status screen и явным dedicated display work queue; проверить battery percentage/charging/connection, отсутствие custom art widget и системной display queue.
- [x] 2.4 Явно оставить battery fetching/proxy выключенными на central и проверить итоговые config sources поиском соответствующих Kconfig symbols.
- [x] 2.5 По аппаратному evidence отключить альтернативный Corne 5-column physical layout для обеих peripherals и проверить compiled Devicetree: единственный enabled 6-column layout, left без offset, right с `col-offset = 6`.

## 3. Сборка и упаковка firmware

- [x] 3.1 Обновить `build.yaml` для dongle, left peripheral, right peripheral и settings reset с однозначными `artifact-name`; проверить YAML и CMake role arguments.
- [x] 3.2 Перенести Studio RPC snippet с левой половины на dongle и проверить, что у peripheral entries snippet отсутствует.
- [x] 3.3 Добавить metadata job с UTC timestamp `YYYYMMDD_HHMM` и передать датированное имя через официальный `archive_name` reusable workflow; проверить GitHub Actions YAML и ожидаемый шаблон имени.

## 4. Эксплуатационная документация

- [x] 4.1 Обновить layout/migration/os-profile docs для dongle central, сохранив описание всех перенесённых слоёв и поведения; проверить согласованность имён targets и topology.
- [x] 4.2 Добавить руководство по settings reset, первой прошивке, host pairing и rollback с точным соответствием четырёх UF2; проверить последовательность по официальному ZMK v0.3 dongle guide.
- [x] 4.3 Расширить test matrix проверками трёх устройств, cold boot/reconnect, обоих peripheral screens, cross-half combo, Studio на dongle, USB/BLE и датированного архива; аппаратные строки оставить `manual pending`.

## 5. Верификация и доставка

- [x] 5.1 Выполнить `git diff --check`, структурные проверки 42 bindings/15 layers/positional combo, YAML parse и `openspec validate migrate-layout-to-dongle --strict`; устранить все ошибки.
- [x] 5.2 Закоммитить и отправить рабочую ветку, дождаться успешной GitHub Actions сборки всех четырёх targets и проверить содержимое датированного artifact.
- [x] 5.3 Зафиксировать номера run/jobs и автоматические результаты в test matrix, повторить статические/OpenSpec проверки и отметить все реально завершённые tasks.
- [x] 5.4 Создать pull request в `master` с summary, ссылками на OpenSpec artifacts, source commit, build evidence, provisioning warning и списком аппаратных `manual pending` тестов: PR #1.
- [x] 5.5 Отправить 6-column fix в PR #1, дождаться успешной сборки всех targets, проверить новый датированный artifact и оставить повторный аппаратный тест layout/combo как `manual pending`.
