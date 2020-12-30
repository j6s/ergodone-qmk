# Ergodone keyboard layout & firmware

Setup for building and flashing the QMK firmware for ergodone
with my preferred keyboard layout.

I will not maintain another copy of the layout in the readme,
so to see the actual layout, check the ASCII-art comments in
[keymap.c](./keymap.c)

## Building

This repository contains everything that is needed for building &
flashing the firmware - it will grab the latest copy of qmk_firmware
automatically when building.

Use `$ make build` to build the firmware and use `$ make flash` to flash it.
Similarly, use `$ make rebuild` and `$ make reflash` to rebuild & reflash
the firmware
