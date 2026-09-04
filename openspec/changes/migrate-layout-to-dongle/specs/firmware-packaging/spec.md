## Purpose

Создаёт воспроизводимый комплект прошивок для трёх устройств и reset-процедуры с автоматически датированным, легко различимым архивом GitHub Actions.

## ADDED Requirements

### Requirement: Workflow собирает полный firmware-комплект
Каждый workflow run SHALL собирать dongle central, `corne_left` peripheral, `corne_right` peripheral и один совместимый `settings_reset` image для `nice_nano_v2`.

#### Scenario: Успешная сборка
- **WHEN** push, pull request или manual dispatch запускает workflow
- **THEN** все четыре targets успешно проходят West/Kconfig/Devicetree build и попадают в один artifact

#### Scenario: Ошибка одного target
- **WHEN** любой обязательный target не собирается
- **THEN** workflow завершается неуспешно и change не считается готовым к прошивке

### Requirement: UF2 имеют стабильные имена
Внутри объединённого архива UF2-файлы SHALL иметь постоянные имена, однозначно различающие dongle, left, right и settings reset.

#### Scenario: Содержимое архива
- **WHEN** пользователь распаковывает artifact
- **THEN** назначение каждого UF2 определяется из имени без переименования вручную

### Requirement: Имя архива содержит UTC timestamp
Имя объединённого artifact SHALL содержать время начала сборки в UTC в формате `YYYYMMDD_HHMM`.

#### Scenario: Загрузка двух сборок
- **WHEN** пользователь скачивает artifacts разных workflow runs
- **THEN** архивы имеют разные датированные имена вида `corne-dongle-firmware_YYYYMMDD_HHMM.zip`
