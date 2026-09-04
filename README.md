# TPAK Corne ZMK config

Донгловая конфигурация беспроводной Corne 3×6 на ZMK v0.3:

```text
Corne Left  --BLE--\
                     >-- nice_nano_v2 dongle --USB/BLE--> host
Corne Right --BLE--/
```

Раскладка и custom OS-profile module перенесены без функциональных изменений из [`tpaktop-corne-wireless-view-zmk-config`](https://github.com/tpaktop77/tpaktop-corne-wireless-view-zmk-config) commit `e7d7c10`.

- [Раскладка и слои](docs/layout.md)
- [OS profile](docs/os-profile.md)
- [Установка донгла и rollback](docs/dongle.md)
- [Матрица миграции](docs/migration-matrix.md)
- [Матрица тестирования](docs/test-matrix.md)

Перед первым переходом на dongle topology обязательно прошей `settings-reset-nice-nano-v2.uf2` на донгл и обе половины. Точные шаги находятся в [docs/dongle.md](docs/dongle.md).
