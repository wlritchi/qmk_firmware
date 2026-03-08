# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is **ZSA's fork** of QMK Firmware, stripped down to only ZSA keyboards: ErgoDox EZ, Planck EZ, Moonlander Mark I, and Voyager. All keyboard code lives under `keyboards/zsa/`. The repo also contains a user-specific Moonlander keymap at `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/`.

## Build Commands

```sh
# Compile firmware (two equivalent forms)
make zsa/moonlander/reva:wlr-dvorakish
qmk compile -kb zsa/moonlander/reva -km wlr-dvorakish

# Flash firmware
qmk flash -kb zsa/moonlander/reva -km wlr-dvorakish

# Generate compile_commands.json for clangd/LSP (must regenerate when switching keyboard/keymap)
qmk build --compiledb

# Run all C unit tests
make test:all
# Run a specific test suite
make test:basic

# Lint a keyboard definition
qmk lint --keyboard zsa/moonlander

# Format C code
qmk format-c --core-only -a

# Clean build artifacts
make clean
make distclean    # also removes .bin/.hex/.uf2 output files
```

The build command format is `make keyboard_path:keymap[:target]`. Keyboard paths map to directory hierarchies under `keyboards/` (e.g., `zsa/moonlander/reva`).

## Architecture

### Key Processing Pipeline

`keyboard.c:keyboard_task()` → matrix scan → `action.c` (action processing) → `quantum.c:process_record_quantum()` (chains through feature-specific `process_record_*()` handlers) → `tmk_core/protocol/host.c` (sends HID reports)

### Directory Structure

- **`quantum/`** — Core QMK logic: key processing, layer management, feature implementations (`process_keycode/`), LED/RGB subsystems, pointing device support, split keyboard communication
- **`tmk_core/`** — Lower-level keyboard library: USB protocol implementations (LUFA for AVR, ChibiOS for ARM), HID report structures
- **`platforms/`** — Hardware abstraction: `avr/`, `chibios/`, `test/` (native compilation for unit tests)
- **`drivers/`** — Hardware drivers for LEDs, sensors, GPIO expanders, displays, haptic
- **`keyboards/zsa/`** — ZSA keyboard definitions (board init, matrix scanning, hardware config)
- **`modules/`** — Community modules (reusable code packages referenced by `keyboard.json` or `keymap.json`)
- **`lib/`** — External dependencies (ChibiOS, LUFA, googletest) and QMK Python CLI (`lib/python/qmk/`)
- **`builddefs/`** — Build system makefiles; `build_keyboard.mk` is the main keyboard build logic
- **`data/`** — JSON schemas, keycode definitions, templates
- **`tests/`** — Unit tests using Google Test

### Key Patterns

**Feature flags:** Features like `RGB_MATRIX_ENABLE`, `MOUSEKEY_ENABLE` etc. are toggled in `rules.mk` or `keyboard.json`. The build system conditionally compiles source files and sets preprocessor defines via `builddefs/common_features.mk`.

**Callback chain:** QMK uses `_quantum` → `_kb` → `_user` callback chaining. For example, `process_record_quantum()` calls `process_record_kb()` which calls `process_record_user()`. Community modules insert their own hooks in this chain.

**Configuration inheritance:** Settings merge from multiple levels (later overrides earlier): `keyboard.json` at each keyboard path level → keyboard `rules.mk`/`config.h` at each level → keymap `rules.mk`/`config.h` → module configurations.

**Data-driven config:** `keyboard.json` is increasingly the source of truth for keyboard definitions. The build system generates `rules.mk` variables and `config.h` defines from it.

### Community Modules

Modules under `modules/` are referenced from `keyboard.json` or `keymap.json` via `{"modules": ["zsa/oryx"]}`. Each module has a `qmk_module.json` manifest and follows the callback pattern with `process_record_<module_name>()` hooks.

ZSA modules: `defaults` (common config/keycodes), `oryx` (Oryx/Keymapp connectivity), `navigator_trackball`, `automouse`, `keycolors`, `doubleclick`, `mousejiggler`.

### Keyboard Structure

Each keyboard has a folder hierarchy with revision subfolders (e.g., `moonlander/reva/`, `moonlander/revb/`). The revision's `keyboard.json` defines USB IDs, feature flags, physical layout, RGB positions, and module references. Keymaps live under `keymaps/` and minimally require a `keymap.c` with the `keymaps[]` array.

### Moonlander Board Revisions

The Moonlander has two hardware revisions with different bootloaders:

| | Rev A | Rev B |
|---|---|---|
| Keyboard path | `zsa/moonlander/reva` | `zsa/moonlander/revb` |
| USB VID:PID (normal) | `3297:1969` | `3297:1972` |
| USB VID:PID (DFU) | `0483:df11` | `3297:2003` |
| Bootloader type | `stm32-dfu` (ST ROM) | `custom` (flash-resident) |
| Flash offset | `0x08000000` | `0x08002000` (8K bootloader) |

Both revisions share the same keymap, matrix layout, and physical key layout. The only build-time difference is the `-kb` argument. To detect which board is connected (in DFU mode) for flashing:

```sh
# Linux
lsusb -d 0483:df11  # Rev A
lsusb -d 3297:2003  # Rev B

# macOS
system_profiler SPUSBDataType 2>/dev/null | grep -A2 'Vendor ID: 0x0483' | grep 'Product ID: 0xdf11'  # Rev A
system_profiler SPUSBDataType 2>/dev/null | grep -A2 'Vendor ID: 0x3297' | grep 'Product ID: 0x2003'  # Rev B

# Cross-platform (requires dfu-util)
dfu-util -l 2>/dev/null | grep '0483:df11'  # Rev A
dfu-util -l 2>/dev/null | grep '3297:2003'  # Rev B
```

### Split Keyboard (Moonlander)

The Moonlander uses I2C to an MCP23018 GPIO expander for the right half. Custom matrix scanning logic is in `moonlander/matrix.c`.

## Code Style

- C: 4-space indentation, no tabs (tabs for Makefiles). Google-based style via `.clang-format`. Pointer alignment right (`char *foo`). No line length limit (column limit 1000).
- Makefiles/`.mk`: Tab indentation.
- Python: 4-space indentation, 200 char line limit.
- YAML: 2-space indentation.
- All files: LF line endings, UTF-8, trailing newline.
- `lib/` directory has no style overrides (external code).

## Testing

Tests use Google Test under `tests/`. Each test suite has a directory containing `test.mk`, `config.h`, and `test_*.cpp` files. Test infrastructure in `tests/test_common/` provides `TestFixture`, `TestDriver` (mock HID), and `KeymapKey` helpers.

```cpp
#include "test_common.hpp"
class MyTest : public TestFixture {};

TEST_F(MyTest, Example) {
    TestDriver driver;
    auto key = KeymapKey(0, 0, 0, KC_A);
    set_keymap({key});
    key.press();
    EXPECT_REPORT(driver, (key.report_code));
    keyboard_task();
}
```

## User Keymap (wlr-dvorakish)

The `wlr-dvorakish` keymap is a Dvorak-variant layout for the Moonlander with 11 layers (BASE, SHIFT, NUM, SHIFTNUM, NAV, SHIFTNAV, WINDOWNAV, WN_NUM, WN_LAUNCHER, WN_SCRATCHPAD, WN_SWITCHER). Uses `LM()` for custom shift layers, OS detection for cross-platform modifier handling, and a custom `windownav` module for window management. Design docs are in `docs/plans/`.
