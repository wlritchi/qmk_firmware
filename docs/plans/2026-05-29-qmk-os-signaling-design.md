# Explicit Host-OS Signaling — QMK side (design)

Firmware support for receiving an authoritative host-OS value from the USB switch
(RP2040 broker) over raw HID, and feeding it into the existing `os_detection`
machinery so the `wlr-dvorakish` keymap's Mac-vs-not logic works through the
switch.

The cross-agent interface negotiation that produced this contract lives in the
repo root: `qmk-os-signaling-interface.md` (broker motivation),
`qmk-os-signaling-interface-response.md` (our review),
`qmk-os-signaling-interface-broker-reply.md`, and
`qmk-os-signaling-interface-response-2.md` (settled). This document is the
QMK-side implementation design only; the broker/hid_device side is out of scope.

## Why

Through the switch the keyboard enumerates against the broker (a constant), so
native `os_detection` can never see the real host. The broker detects the real
OS on the `hid_device` board and pushes it to the keyboard explicitly. The
keymap already reads `detected_host_os()` synchronously at keypress
(`keymap.c`, `windownav.c`) and only distinguishes **Mac-family vs. not**, so if
we make `detected_host_os()` return the pushed value, the keymap needs no
changes.

## Settled wire contract

Shared transport: the **existing Oryx raw-HID interface** (usage page `0xFF60`,
usage `0x61`, `RAW_EPSIZE = 32`). VIA is off; Oryx owns `raw_hid_receive`, so we
interpose ahead of it (below). All fields are single bytes; `os` uses QMK
`os_variant_t` values directly.

| Message | Dir | Bytes (`0..3`, rest `0`) |
|---------|-----|--------------------------|
| `QUERY` | broker → kbd (OUT) | `0xB0, 0x01, 0x00, –` |
| `ACK` (capable fw only) | kbd → broker (IN) | `0xB0, 0x01, 0x00, caps` where `caps` bit0 = SET_HOST_OS |
| `SET_HOST_OS` | broker → kbd (OUT) | `0xB0, 0x01, 0x01, os` (`os` ∈ `0..4`) |

- Byte 0 `magic = 0xB0` is outside Oryx's command **and** event spaces
  (`0x00..0x0B`, `0xFE`, `0xFF`), so it cleanly disambiguates in both directions.
- `QUERY`/`SET_HOST_OS` require no pairing. `SET_HOST_OS` is fire-and-forget and
  idempotent; the broker re-pushes on every (re)enumeration.
- On stock (non-OS-aware) firmware, `0xB0` falls through to Oryx's `default:` →
  one `ORYX_EVT_ERROR` (`0xFF, 0xFF`), which is how the broker detects "not
  capable."

## Architecture

Four units, in increasing fork-locality:

1. **`os_detection` core** (`quantum/os_detection.{c,h}`) — gains a public
   `os_detection_set_explicit()` plus an "authoritative" lock. General, minimal,
   plausibly upstreamable.
2. **Raw-HID pre-hook** (`modules/zsa/oryx/oryx.c`) — a 1-call interception point
   so a `_user` handler can claim reports before Oryx. Fork-local glue against the
   vendored module.
3. **OS-signal handler** (`keymaps/wlr-dvorakish/os_signal.c`, new) — parses
   `QUERY`/`SET_HOST_OS`, emits `ACK`, calls the setter. All keymap-local.
4. **Build wiring** (`keymaps/wlr-dvorakish/rules.mk`).

## Detailed design

### 1. `os_detection` core — setter + lock

Add to `os_detection.h`:

```c
// Adopt an externally-supplied host OS as authoritative. Overrides native
// fingerprinting until the next erase/reboot. OS_UNSURE is a no-op (keep-last).
void os_detection_set_explicit(os_variant_t os);
```

Add to `os_detection.c`:

```c
static volatile bool os_locked = false;   // explicit value received; native detection suppressed

void os_detection_set_explicit(os_variant_t os) {
    if (os == OS_UNSURE) {
        return;                            // keep-last: never downgrade on transient UNSURE
    }
    detected_os = os;
    os_locked   = true;
    last_time   = timer_read_fast();       // drive the normal report path too
    debouncing  = true;
}
```

Guard native detection in `process_wlength()` (very top):

```c
void process_wlength(const uint16_t w_length) {
    if (os_locked) {
        return;                            // explicit value wins; don't accumulate or overwrite
    }
    ...
}
```

Reset the flag in `erase_wlength_data()` (keeps test isolation and is correct):

```c
void erase_wlength_data(void) {
    ...
    os_locked = false;
}
```

Notes:
- Not behind the `SPLIT_KEYBOARD` guard (that gates `slave_update_detected_host_os`,
  which is not compiled on the Moonlander). The setter is available whenever
  `OS_DETECTION_ENABLE` is set.
- `detected_host_os()` is unchanged and now transparently returns the pushed
  value. The keymap polls it live, so the value is visible on the next keypress;
  the `last_time`/`debouncing` stamp also fires `process_detected_host_os_*` for
  any future callback consumer.
- Context: the setter is called from `raw_hid_receive` (main-loop via
  `raw_hid_task()`), same context as `os_detection_task()`. No ISR race; the
  `volatile`s suffice.

### 2. Raw-HID pre-hook (vendored Oryx module)

QMK exposes a single `raw_hid_receive`; Oryx defines it strongly and offers no
`_user` chain. Add a weak pre-hook so a keymap can claim reports first.

`modules/zsa/oryx/oryx.c`, at the very top of `raw_hid_receive()`:

```c
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (raw_hid_receive_user(data, length)) {
        return;                            // claimed by keymap (e.g. OS signaling); skip Oryx
    }
    uint8_t  command = data[0];
    ...
}
```

Weak default (so stock builds and other keymaps are unaffected):

```c
__attribute__((weak)) bool raw_hid_receive_user(uint8_t *data, uint8_t length) {
    return false;
}
```

Mark this as a local patch (comment) so it survives a future re-vendor of the
module. **Decision point (see Open decisions):** the weak default + prototype can
instead live in core `quantum/raw_hid.{c,h}` if we prefer a generic, upstreamable
hook over a module-local one.

### 3. OS-signal handler (new keymap file)

New `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/os_signal.c`:

```c
#include QMK_KEYBOARD_H
#include "raw_hid.h"        // raw_hid_send
#include "os_detection.h"   // os_variant_t, os_detection_set_explicit

#define OSIG_MAGIC        0xB0
#define OSIG_VERSION      0x01
#define OSIG_MSG_QUERY    0x00
#define OSIG_MSG_SET_OS   0x01
#define OSIG_CAP_SET_OS   0x01   // bit0

bool raw_hid_receive_user(uint8_t *data, uint8_t length) {
    if (length < 3 || data[0] != OSIG_MAGIC) {
        return false;            // not ours → let Oryx handle it
    }
    // We own every 0xB0 report from here, so Oryx never errors on it.
    switch (data[2]) {           // msg_type
        case OSIG_MSG_QUERY: {
            // Always answer with OUR version, regardless of the broker's QUERY
            // version byte (data[1]), so version discovery works across mismatches.
            uint8_t ack[RAW_EPSIZE] = {0};
            ack[0] = OSIG_MAGIC;
            ack[1] = OSIG_VERSION;
            ack[2] = OSIG_MSG_QUERY;     // echo msg_type
            ack[3] = OSIG_CAP_SET_OS;
            raw_hid_send(ack, RAW_EPSIZE);
            break;
        }
        case OSIG_MSG_SET_OS:
            // Apply only when the layout matches our protocol version.
            if (data[1] == OSIG_VERSION && length >= 4 && data[3] <= OS_IOS) {
                os_detection_set_explicit((os_variant_t)data[3]);
            }
            break;
        default:
            break;                       // claim + ignore unknown msg_type
    }
    return true;
}
```

### 4. Build wiring

`keymaps/wlr-dvorakish/rules.mk`: `SRC += os_signal.c`. `RAW_ENABLE` (via Oryx)
and `OS_DETECTION_ENABLE = yes` are already set; native detection stays on so a
direct-to-PC plug still self-detects until the lock engages.

## Behavior & edge cases

- **Precedence.** The lock engages on the first explicit non-`UNSURE` value.
  Before that (e.g. direct-plug), native detection drives `detected_os`. After,
  `process_wlength()` early-returns, so native fingerprinting of the broker can
  never override the pushed value. The broker additionally suppresses
  `GET_DESCRIPTOR(String)`, so native detection sits at `OS_UNSURE` pre-lock
  anyway — belt and suspenders.
- **Idempotency.** Re-pushing the same OS leaves `detected_os` unchanged;
  `os_detection_task()` sees `detected_os == reported_os` and refires no callback.
- **`OS_UNSURE` = keep-last.** `set_explicit(OS_UNSURE)` is a no-op, so a
  transient UNSURE from the broker never reverts a good Mac value.
- **Reboot / re-enumeration self-heal.** A reboot clears RAM (`os_locked = false`,
  `detected_os = OS_UNSURE`). The broker re-runs QUERY→ACK on raw-HID mount and
  re-pushes, re-engaging the lock. Depends on the broker's re-push-on-mount
  (in the contract).
- **ACK timing.** `raw_hid_receive` runs in the main loop (`raw_hid_task()` in
  `quantum/main.c`), not an ISR, so the ACK is queued synchronously but at
  main-loop cadence — typically a few ms, occasionally tens of ms under RGB-matrix
  rendering / suspend-resume / EEPROM writes. The broker uses a 100–250 ms window
  with one retry.

## Testing

Unit tests (extend `quantum/os_detection/tests/os_detection.cpp`; the harness's
`SetUp()` already calls `erase_wlength_data()`, which now also clears `os_locked`):

- `set_explicit(OS_MACOS)` → `detected_host_os() == OS_MACOS`; after
  `advance_time(DEBOUNCE)` + `os_detection_task()`, reported once.
- **Lock wins:** `set_explicit(OS_MACOS)`, then a `process_wlength` sequence that
  natively yields Linux → `detected_host_os()` stays `OS_MACOS`.
- **Keep-last:** `set_explicit(OS_MACOS)` then `set_explicit(OS_UNSURE)` →
  stays `OS_MACOS`.
- **Pre-lock native still works:** without calling the setter, an existing native
  sequence still detects (guards against the early-return regressing native use).
- **Idempotent re-apply:** `set_explicit(OS_MACOS)` twice → reported exactly once.

The raw-HID handler (`os_signal.c`) is keymap-local and not covered by the C unit
harness. Manual integration test: with the keyboard plugged directly into a PC
(Keymapp closed), use a host raw-HID tool (e.g. `hidapitester`) on `0xFF60/0x61`
to send `QUERY` (expect the `ACK` bytes back) and `SET_HOST_OS` with `os = 3`
(expect Mac-style modifier behavior in the keymap), then `os = 1` (expect it to
revert). End-to-end through the switch is validated jointly with the broker.

## Files to create / modify

| File | Change |
|------|--------|
| `quantum/os_detection.h` | declare `os_detection_set_explicit` |
| `quantum/os_detection.c` | setter, `os_locked`, `process_wlength` guard, `erase_wlength_data` reset |
| `modules/zsa/oryx/oryx.c` | `raw_hid_receive_user` pre-hook call + weak default (local patch) |
| `keymaps/wlr-dvorakish/os_signal.c` | **new** — magic-tagged QUERY/SET_HOST_OS handler + ACK |
| `keymaps/wlr-dvorakish/rules.mk` | `SRC += os_signal.c` |
| `quantum/os_detection/tests/os_detection.cpp` | tests above |

## Open decisions (for review)

1. **Hook placement:** weak `raw_hid_receive_user` in the vendored Oryx module
   (recommended — confines extra churn; only `os_detection` touches core) vs. in
   core `quantum/raw_hid.{c,h}` (more upstreamable, generic). Both are tiny.
2. **Handler location:** separate `os_signal.c` (recommended — keeps the 800-line
   `keymap.c` focused) vs. inline in `keymap.c`.
3. **Upstreaming:** `os_detection_set_explicit` + lock is general enough to offer
   to QMK upstream later; not a blocker.

## Out of scope

hid_device detection, I²C, broker scheduling, the QUERY/ACK timing budget on the
broker side, descriptor-spoofing for stock keyboards, and NV persistence of OS
state (RAM-only; self-heals on re-enumeration).
