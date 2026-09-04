## Purpose

Сохраняет проверенную раскладку и пользовательские behaviors при переносе в отдельный репозиторий донгловой конфигурации с однозначной привязкой к исходной ревизии.

## ADDED Requirements

### Requirement: Проверенная раскладка переносится из зафиксированной ревизии
Целевая конфигурация SHALL воспроизводить version-controlled keymap и пользовательский ZMK-модуль из `tpaktop-corne-wireless-view-zmk-config` commit `e7d7c10` без функционального упрощения.

#### Scenario: Состав раскладки после переноса
- **WHEN** сравниваются исходная ревизия и донгловая конфигурация
- **THEN** Graphite, QWERTY, Russian, функциональные слои, русские слои, positional combo, Auto Shift, macros и OS-aware actions присутствуют с теми же bindings и таймингами

#### Scenario: Начальное состояние
- **WHEN** донгл перезагружается
- **THEN** базовым слоем является Graphite с индексом 0, а volatile OS profile равен Windows

### Requirement: Перенос не изменяет исходные репозитории
Работа SHALL изменять только `tpaktop-corne-zmk-config`; view-конфигурация, конфигурация `nat` и QMK/Oryx reference MUST оставаться read-only.

#### Scenario: Проверка границ изменений
- **WHEN** change готов к review
- **THEN** все коммиты и рабочая ветка находятся только в `tpaktop-corne-zmk-config`

### Requirement: Источник переноса документирован
Документация SHALL указывать исходный репозиторий, commit и намеренные отличия донгловой конфигурации.

#### Scenario: Аудит происхождения
- **WHEN** владелец открывает документацию миграции
- **THEN** он видит `tpaktop-corne-wireless-view-zmk-config@e7d7c10` и список отличий, связанных только с topology, display, Studio, build и provisioning
