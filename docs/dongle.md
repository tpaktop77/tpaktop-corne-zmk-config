# Донгл: прошивка, pairing и rollback

Конфигурация использует стандартный BLE dongle mode ZMK v0.3. Отдельный `nice_nano_v2` является central и подключается к компьютеру по USB или через один из пяти Bluetooth profiles. Обе половины Corne являются BLE peripherals и без донгла не отправляют клавиши хосту.

Официальные reference:

- [Keyboard Dongle](https://zmk.dev/docs/development/hardware-integration/dongle)
- [Split Keyboards](https://zmk.dev/docs/features/split-keyboards)
- [Connection Issues / settings reset](https://zmk.dev/docs/troubleshooting/connection-issues)

## Содержимое firmware artifact

GitHub Actions создаёт архив вида:

```text
corne-dongle-firmware_YYYYMMDD_HHMM.zip
```

Timestamp задаётся в UTC. Внутри находятся стабильные имена:

| Файл | Куда прошивать |
|---|---|
| `tpaktop-corne-dongle.uf2` | отдельный `nice_nano_v2`-донгл |
| `corne-left-peripheral.uf2` | контроллер левой Corne |
| `corne-right-peripheral.uf2` | контроллер правой Corne |
| `settings-reset-nice-nano-v2.uf2` | по очереди на все три контроллера перед первой установкой или восстановлением bonds |

Не прошивай dongle/left/right UF2 на другое устройство: split role является частью firmware.

## Первый переход на донгл

Старая прошивка хранит bonds для topology с левой central. Обычная прошивка их не стирает, поэтому reset всех трёх устройств обязателен.

1. Скачать и распаковать последний датированный artifact.
2. Перевести донгл в bootloader и скопировать на него `settings-reset-nice-nano-v2.uf2`; дождаться перезапуска.
3. Повторить settings reset отдельно для левой и правой половины.
4. Снова открыть bootloader донгла и прошить `tpaktop-corne-dongle.uf2`.
5. Прошить левую половину файлом `corne-left-peripheral.uf2`.
6. Прошить правую половину файлом `corne-right-peripheral.uf2`.
7. Подключить донгл к компьютеру по USB, затем включить обе половины.
8. Убедиться, что оба nice!view показывают connected status; первый split pairing может занять несколько секунд.
9. Проверить ввод с каждой половины, cross-half combo и ZMK Studio через USB-донгл.
10. Для BLE выбрать свободный `BT0`–`BT4` на System layer и выполнить pairing компьютера именно с донглом.

## Что показывают nice!view

Каждый экран относится только к своей половине и показывает:

- локальный процент заряда;
- индикатор USB-зарядки;
- connected/disconnected status связи с донглом.

На половины не передаются активный слой, OS profile, host Bluetooth profile или заряд второй половины. Декоративный nice!view custom widget отключён в пользу встроенного status screen ZMK. `CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED=y` задан явно, поэтому LVGL updates выполняются в отдельной display work queue, а не в системной очереди.

## Bluetooth и OS profile

- `BT0`–`BT4` выбирают host profiles центрального донгла.
- Split bonds обеих половин занимают отдельные central connections и не являются host profiles.
- Windows/macOS/Linux остаётся независимым RAM-состоянием донгла.
- После reboot OS profile снова Windows, base layer снова Graphite.
- Смена BT profile не меняет OS profile и наоборот.

## Если половина не подключается

1. Оставить донгл подключённым по USB и перезапустить проблемную половину.
2. Проверить, что на половине прошит правильный peripheral UF2.
3. Если связь не появилась, повторить полный settings reset на всех трёх устройствах, а не только на одной половине.
4. Повторить установку трёх рабочих UF2 в порядке dongle → left → right.

Battery-level fetching/proxy на central намеренно выключены: донгл не собирает заряд половин, а каждый nice!view читает локальную батарею.

## Rollback к конфигурации без донгла

Стабильный `tpaktop-corne-wireless-view-zmk-config` не изменяется этой миграцией.

1. Скачать последнюю успешную left/right firmware из view-репозитория.
2. Прошить `settings_reset` на обе половины и дать им загрузиться.
3. Прошить прежние central-left и peripheral-right UF2.
4. Повторно выполнить split/host pairing согласно прежней конфигурации.

Донгл после rollback можно выключить; его settings не влияют на восстановленные половины.
