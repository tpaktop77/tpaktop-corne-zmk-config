# TPAK Corne ZMK config

Dongle configuration for a wireless Corne 3x6 on ZMK v0.3:

```text
Corne Left  --BLE--\
                     >-- nice_nano_v2 dongle --USB/BLE--> host
Corne Right --BLE--/
```

The layout and custom OS-profile module were migrated without functional changes from [`tpaktop-corne-wireless-view-zmk-config`](https://github.com/tpaktop77/tpaktop-corne-wireless-view-zmk-config) commit `e7d7c10`.

- [Layout and layers](docs/layout.md)
- [OS profile](docs/os-profile.md)
- [Dongle installation and rollback](docs/dongle.md)
- [Migration matrix](docs/migration-matrix.md)
- [Test matrix](docs/test-matrix.md)

Before the first migration to dongle topology, flash `settings-reset-nice-nano-v2.uf2` to the dongle and both halves. See [docs/dongle.md](docs/dongle.md) for the exact sequence.
