<h1 align="center">
    <img
        width="300"
        alt="eOS"
        src="assets/eOS-logo.svg">
</h1>

<h3 align="center">
    a simple multitasking OS for ARM Cortex-M devices
</h3>

## Overview and features

* **From scratch.** Started from nothing. Even the linker script and is homemade.
* **Modern and open source.** Uses a modern, open source GNU GCC toolchain, and `meson`, a build system that isn't awful.
* **Minimal dependencies.** Only dependency is libopencm3, which is used as the hardware abstraction layer. Who writes their own HAL these days anyway...
* **No heap allocation.** No provision is made for heap allocation.
* **Multitasking.** Pre-emptive multitasking. No more `while (1)` loops.
* **Learning experience.** You're bound to learn lots debugging this thing.

## Requirements

1. A suitable toolchain: `gcc-arm-none-eabi`
2. Build tools: `meson`, `ninja`, and `st-link`
3. A ST-Link programmer

## Quick start

eOS is currently only tested on ST Nucleo STM32F303RE board.
However, it should work on other STM32 boards with minimal modifications.

To get a build of eOS running on a board, run the following commands.


```sh
# Configure the build directory, then enter it
meson build --cross-file cross_compiling_config.toml
cd build

# Make a binary
ninja -j4

# Flash device connected via ST-Link
ninja flash
```

## Extra build targets

There's some additional build targets to make the developer's life easier

```sh
ninja flash       # Flash an MCU connected via ST-Link
ninja erase       # Erase MCU connected via ST-Link
ninja gdb         # Launch a GDB server for debugging
ninja size        # Show the size of the text, data, bss sections
ninja sections    # Same as "size", but with more detail
ninja scan-build  # Run clang's static analyzer
```

## Directory structure

```
eOS
├── README.md                    # This file
├── cross_compiling_config.toml  # Meson cross-compilation configuration
├── meson.build                  # Meson build definition file
├── .dir-locals.el               # Emacs project-specific settings
├── .clang-format                # Style file for automatic code formatting
├── assets                       # Non-essential data, i.e. logos
├── src                          # Source files
│   ├── core                       # Core OS routines
│   ├── startup                    # Code used during startup phase
│   ├── main.c                     # Main entry point
│   └── config.h                   # Compile-time OS configurables
└── subprojects                  # Subprojects
    ├── cmsis                      # ARM's CMSIS
    └── libopencm3                 # libopencm3 hardware abstraction layer
```
