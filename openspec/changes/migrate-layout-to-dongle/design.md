## Context

Целевой `tpaktop-corne-zmk-config` имеет единственный initial commit `d286351`: стандартный трёхслойный keymap, ZMK v0.3 и build matrix двух Corne-половин. Несмотря на название репозитория, matrix уже содержит `nice_view_adapter nice_view`; пользователь решил сохранить дисплеи, но оставить на них только локальный battery/charging и split connection status.

Проверенная конфигурация находится в read-only `tpaktop-corne-wireless-view-zmk-config` на `master` commit `e7d7c10`; открытых PR в исходном и целевом репозиториях перед началом change нет. Она содержит 15 слоёв, positional combo, русский блок, Auto Shift 300 ms, volatile OS profile и корневой out-of-tree module. Этот commit используется как baseline целиком, а не как набор выборочных фрагментов.

Официальный ZMK v0.3 dongle mechanism требует central shield с mock kscan, matrix transform и physical layout. Обе реальные половины становятся BLE peripherals. ZMK Studio и все keymap-dependent behaviors должны выполняться на central.

## Goals / Non-Goals

**Goals:**

- Изолировать донгловую архитектуру в отдельном репозитории и сохранить рабочий view-репозиторий как rollback.
- Получить четыре проверяемых UF2: dongle, left, right и settings reset.
- Сохранить функциональную идентичность keymap при смене split topology.
- Использовать штатные механизмы ZMK v0.3 для dongle, Studio и peripheral display.

**Non-Goals:**

- Проприетарный 2.4 GHz transport, работа половин без донгла или runtime-переключение topology.
- Экран на донгле, передача active layer/OS/host profile на половины и собственный display widget.
- Получение или proxy уровня батарей peripherals на central.
- Исправление перекрывающихся combo, Russian Caps Word или иное изменение текущей раскладки.
- Изменение исходного view-репозитория, `nat-corne-zmk-config` или QMK/Oryx.

## Decisions

### 1. `nice_nano_v2` используется и как dongle board

Создаётся shield `tpaktop_corne_dongle` в `config/boards/shields/tpaktop_corne`. Он включает `ZMK_SPLIT_ROLE_CENTRAL=y`, две peripherals и лимиты `BT_MAX_CONN=7`, `BT_MAX_PAIRED=7`: две служебные split-связи плюс пять host profiles. Имя клавиатуры укладывается в лимит 16 символов.

Альтернатива — отдельная XIAO/Prospector board — не выбрана, поскольку пользователь не указал другое устройство, а `nice_nano_v2` уже является аппаратной базой проекта и поддерживается ZMK v0.3.

### 2. Dongle shield повторяет Corne 6-column topology

Overlay использует mock kscan без клавиш, точную 12×4 `default_transform` карту на 42 позиции из in-tree Corne v0.3 и shared physical layout `foostan_corne_6col_layout`. Это сохраняет номера positional combo и даёт Studio полный physical layout.

Для выбора общего keymap добавляется `config/tpaktop_corne_dongle.keymap`, включающий version-controlled `corne.keymap`. Отдельная копия 818-строчного keymap не создаётся.

### 3. Keymap переносится как baseline, topology-настройки отделяются

Корневые `CMakeLists.txt`, `Kconfig`, `zephyr/module.yml`, `dts/`, `include/`, `src/`, `config/corne.keymap`, `config/west.yml` и пользовательская документация копируются из `e7d7c10`. Старые OpenSpec change directories не копируются как активная история нового репозитория; provenance и требования переноса фиксирует текущий change.

`config/corne.conf` становится конфигурацией peripherals: radio/debounce плюс built-in nice!view status. Studio удаляется из неё. `config/tpaktop_corne_dongle.conf` содержит radio и Studio settings для central. Существующий CMake guard уже компилирует OS behavior sources только на central.

### 4. Для nice!view используется built-in status screen

Shields `nice_view_adapter nice_view` остаются у left/right targets. Выбирается `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y` и процентный battery widget. На peripheral Kconfig-зависимости ZMK v0.3 исключают layer/output/WPM widgets и включают battery плюс peripheral connection widgets; custom nice!view art code не используется.

Shield nice!view в ZMK v0.3 уже выбирает `ZMK_DISPLAY_WORK_QUEUE_DEDICATED` по умолчанию. После проверки upstream Kconfig и display implementation настройка также задаётся явно в `config/corne.conf`, чтобы LVGL updates гарантированно шли через отдельную `k_work_q` и выбор не зависел от будущего изменения shield defaults.

Собственный widget отклонён: он дублировал бы штатный код и создавал обязательство сопровождения без дополнительной пользовательской ценности.

### 5. Studio переносится на headless central

Snippet `studio-rpc-usb-uart` назначается только dongle target. Physical layout из решения 2 обеспечивает Studio mapping; три reserved layer остаются в перенесённом keymap. Peripheral targets не получают Studio snippet и не являются USB Studio endpoints.

### 6. Build matrix формирует полный install set

Matrix содержит:

1. `nice_nano_v2 + tpaktop_corne_dongle + studio-rpc-usb-uart`;
2. `nice_nano_v2 + corne_left + nice_view_adapter + nice_view` с принудительным peripheral role;
3. аналогичный `corne_right` target;
4. `nice_nano_v2 + settings_reset`.

Каждому target задаётся стабильное `artifact-name`. Battery fetching/proxy на dongle намеренно не включается из-за известных рисков ZMK v0.3 с двумя peripherals.

### 7. Timestamp передаётся штатному reusable workflow

Отдельный metadata job формирует UTC `YYYYMMDD_HHMM` и экспортирует output. Reusable `build-user-config.yml@v0.3` вызывается с `archive_name: corne-dongle-firmware_<timestamp>`. Это использует официальный input workflow и не требует копировать или форкать upstream workflow. Внутренние UF2 сохраняют стабильные имена.

### 8. Документация разделяет автоматическую и аппаратную проверку

Документы исходной раскладки переносятся и получают явную provenance/topology секцию. Новый dongle guide описывает reset, mapping UF2, first pairing и rollback. Test matrix сохраняет прежние manual pending строки и добавляет три устройства, минимальные экраны, Studio на dongle, cross-half combo, USB/BLE и provisioning.

### 9. Peripheral firmware жёстко фиксирует Corne 6 Column

Аппаратный тест 2026-09-05 после полного settings reset выявил систематическое использование `five_column_transform` обеими половинами: правый home row выдал `TSGYH` вместо `YHAEI`, то есть позиции 15–19 вместо 18–22; левая половина показала соответствующее смещение и попадание внешней клавиши в служебную позицию. Исходный `master` целевого репозитория содержит 42 bindings на слой, поэтому это не 5×3 template. Повторный reset с полной загрузкой reset firmware результат не изменил.

Дополнительный shield `tpaktop_corne_6col`, включаемый после `corne_left`/`corne_right`, переводит `foostan_corne_5col_layout` в `status = "disabled"`. Обычный user-config overlay был отклонён фактической CI-проверкой: ZMK подключает его раньше in-tree Corne overlay, когда label ещё не определён. Extension shield обеспечивает правильный порядок, а единственным доступным peripheral physical layout остаётся `foostan_corne_6col_layout` с прежними `default_transform` и правым `col-offset = 6`. Dongle overlay и version-controlled keymap не меняются. Роли и BLE bonds также не меняются, поэтому для установки исправления достаточно перепрошить обе половины без settings reset.

## Risks / Trade-offs

- [Неизвестная фактическая плата донгла отличается от `nice_nano_v2`] → board выделен одной строкой matrix и документирован как принятое аппаратное предположение; смена board не затрагивает keymap/topology specs.
- [Старые bonds мешают обнаружению двух peripherals] → обязательный `settings_reset` включён в artifact и выполняется на всех трёх устройствах.
- [Одна из половин не подключается при старте] → battery fetching/proxy отключены, display queue явно выделена; test matrix отдельно проверяет cold boot, reconnection и обе стороны.
- [Positional combo меняются при переносе] → dongle transform дословно совпадает с Corne 6-column v0.3, keymap копируется из фиксированного commit, добавляется структурная проверка 42 bindings на слой.
- [Peripheral выбирает альтернативный in-tree Corne 5-column layout] → 5-column physical layout явно отключён extension shield `tpaktop_corne_6col`; compiled Devicetree обеих половин проверяется на единственный enabled 6-column layout.
- [Peripheral display неожиданно показывает art/layer] → сборочная конфигурация принудительно выбирает built-in screen; итоговый Kconfig проверяется в Actions.
- [Донгл потерян или неисправен] → половины намеренно не работают автономно; неизменённый view-репозиторий и документированный reset дают rollback.
- [Timestamp совпадает у редких параллельных запусков в одну минуту] → GitHub хранит artifacts по run, а имя удовлетворяет задаче различения повседневных сборок; run ID не добавляется ради читаемости.

## Migration Plan

1. Собрать и скачать датированный artifact, проверить наличие четырёх UF2.
2. По очереди прошить `settings-reset-nice-nano-v2.uf2` на dongle, left и right и дать каждому загрузиться.
3. Прошить `tpaktop-corne-dongle.uf2`, `corne-left-peripheral.uf2`, `corne-right-peripheral.uf2` на соответствующие устройства.
4. Сначала включить/подключить dongle, затем обе половины; проверить connection indicators.
5. Выполнить USB smoke tests, ZMK Studio test, затем pairing BT0 и BLE smoke tests; остальные host profiles проверять независимо.
6. При rollback повторить settings reset на половинах и прошить left/right artifacts из стабильного view-репозитория.
