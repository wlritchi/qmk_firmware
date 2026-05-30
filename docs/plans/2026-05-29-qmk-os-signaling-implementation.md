# QMK Host-OS Signaling Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Let the `wlr-dvorakish` Moonlander firmware accept an authoritative host-OS value pushed by the USB switch (RP2040 broker) over the shared Oryx raw-HID interface, and feed it into `os_detection` so the keymap's Mac-vs-not logic works through the switch.

**Architecture:** Add `os_detection_set_explicit()` + an authoritative lock to core `os_detection` (TDD via the existing Google Test suite). Add a weak `raw_hid_receive_user` pre-hook to the vendored Oryx module so a keymap can claim raw-HID reports before Oryx parses them. Implement the magic-tagged QUERY/SET_HOST_OS handler (with capability ACK) in a new keymap-local `os_signal.c`.

**Tech Stack:** C (QMK / ChibiOS, ARM STM32F303), Google Test (native test build), QMK raw HID (`0xFF60/0x61`, `RAW_EPSIZE = 32`).

**Design reference:** `docs/plans/2026-05-29-qmk-os-signaling-design.md` and the interface contract docs alongside it.

**Conventions:** Commit directly to `main`. Do **not** run autoformatters on the keymap files (`os_signal.c`, `keymap.c`); match surrounding style by hand. End commit messages with the `Co-Authored-By` line shown in each commit step.

---

## File structure

| File | Responsibility | Task |
|------|----------------|------|
| `quantum/os_detection.h` | Declare `os_detection_set_explicit()` | 1 |
| `quantum/os_detection.c` | Setter, `os_locked` flag, `process_wlength` guard, `erase_wlength_data` reset | 1 |
| `quantum/os_detection/tests/os_detection.cpp` | Unit tests for the above | 1 |
| `modules/zsa/oryx/oryx.c` | Weak `raw_hid_receive_user` pre-hook + call (local patch) | 2 |
| `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/os_signal.c` | **New.** QUERY/SET_HOST_OS handler + capability ACK | 3 |
| `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk` | `SRC += os_signal.c` | 3 |

---

## Task 1: `os_detection_set_explicit` + authoritative lock

**Files:**
- Modify: `quantum/os_detection.h`
- Modify: `quantum/os_detection.c`
- Test: `quantum/os_detection/tests/os_detection.cpp`

- [ ] **Step 1: Write the failing tests**

Append to the **end** of `quantum/os_detection/tests/os_detection.cpp` (the helpers `check_sequence`, `advance_time`, `assert_reported`, and the static `usb_device_state_configured` are all defined earlier in this file):

```cpp
// --- Explicit host-OS signaling (os_detection_set_explicit) ---

TEST_F(OsDetectionTest, TestExplicitSetsValue) {
    os_detection_set_explicit(OS_MACOS);
    EXPECT_EQ(detected_host_os(), OS_MACOS);
}

TEST_F(OsDetectionTest, TestExplicitLockBeatsNative) {
    os_detection_set_explicit(OS_MACOS);
    // A Linux fingerprint must NOT override the locked explicit value.
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF}), OS_MACOS);
    EXPECT_EQ(detected_host_os(), OS_MACOS);
}

TEST_F(OsDetectionTest, TestExplicitUnsureKeepsLast) {
    os_detection_set_explicit(OS_MACOS);
    os_detection_set_explicit(OS_UNSURE);  // transient UNSURE must not revert
    EXPECT_EQ(detected_host_os(), OS_MACOS);
}

TEST_F(OsDetectionTest, TestNativeWorksWithoutExplicit) {
    // Lock defaults off (erase_wlength_data runs in SetUp), so native still works.
    EXPECT_EQ(check_sequence({0xFF, 0xFF, 0xFF}), OS_LINUX);
}

TEST_F(OsDetectionTest, TestExplicitReportsOnceIdempotent) {
    os_detection_notify_usb_device_state_change(usb_device_state_configured);
    os_detection_set_explicit(OS_MACOS);
    advance_time(OS_DETECTION_DEBOUNCE + 1);
    os_detection_task();
    assert_reported(OS_MACOS);

    // Re-applying the same OS must not fire the callback again.
    os_detection_set_explicit(OS_MACOS);
    advance_time(OS_DETECTION_DEBOUNCE + 1);
    os_detection_task();
    assert_reported(OS_MACOS);  // still reported exactly once
}
```

- [ ] **Step 2: Run the tests to verify they fail**

Run: `make test:os_detection`
Expected: FAIL — compile error, `os_detection_set_explicit` not declared.

- [ ] **Step 3: Declare the setter in the header**

In `quantum/os_detection.h`, add the declaration immediately after the `erase_wlength_data` line (currently line 33):

```c
void         erase_wlength_data(void);
void         os_detection_set_explicit(os_variant_t os);
```

- [ ] **Step 4: Add the lock flag**

In `quantum/os_detection.c`, add the flag right after `static volatile os_variant_t reported_os = OS_UNSURE;` (currently line 62):

```c
static volatile os_variant_t reported_os = OS_UNSURE;

// set when an explicit host OS has been pushed in; suppresses native fingerprinting
static volatile bool os_locked = false;
```

- [ ] **Step 5: Guard native detection in `process_wlength`**

In `quantum/os_detection.c`, make the lock check the very first statement of `process_wlength` (before the `OS_DETECTION_DEBUG_ENABLE` block):

```c
void process_wlength(const uint16_t w_length) {
    if (os_locked) {
        // an explicit host OS is authoritative; ignore native fingerprinting
        return;
    }
#ifdef OS_DETECTION_DEBUG_ENABLE
    usb_setups[setups_data.count] = w_length;
#endif
```

- [ ] **Step 6: Implement the setter**

In `quantum/os_detection.c`, add the function immediately after `detected_host_os()` (currently ends line 181):

```c
os_variant_t detected_host_os(void) {
    return detected_os;
}

void os_detection_set_explicit(os_variant_t os) {
    if (os == OS_UNSURE) {
        // keep-last: a transient UNSURE must never downgrade a good value
        return;
    }
    detected_os = os;
    os_locked   = true;
    last_time   = timer_read_fast();  // drive the normal debounce/report path too
    debouncing  = true;
}
```

- [ ] **Step 7: Reset the lock in `erase_wlength_data`**

In `quantum/os_detection.c`, add the reset to `erase_wlength_data` (after `first_report = true;`):

```c
    first_report                             = true;
    os_locked                                = false;
}
```

- [ ] **Step 8: Run the tests to verify they pass**

Run: `make test:os_detection`
Expected: PASS — all `OsDetectionTest` cases green, including the five new ones.

- [ ] **Step 9: Commit**

```bash
git add quantum/os_detection.h quantum/os_detection.c quantum/os_detection/tests/os_detection.cpp
git commit -m "$(cat <<'EOF'
feat(os_detection): add os_detection_set_explicit with authoritative lock

New public setter adopts an externally-supplied host OS as authoritative:
it sets detected_os, drives the normal debounce/report path, and locks out
native wLength fingerprinting until the next erase/reboot. OS_UNSURE is a
no-op (keep-last). For pushing the real host OS through a USB switch.

Co-Authored-By: Claude Opus 4.8 <noreply@anthropic.com>
EOF
)"
```

---

## Task 2: Raw-HID pre-hook in the Oryx module

**Files:**
- Modify: `modules/zsa/oryx/oryx.c` (currently `raw_hid_receive` starts at line 110)

A weak `raw_hid_receive_user` lets a keymap claim a report before Oryx parses it. Default no-op, so this commit changes no runtime behavior on its own. Kept module-local per design decision #1 (no core `raw_hid.{c,h}` change).

- [ ] **Step 1: Add the weak default + interception call**

In `modules/zsa/oryx/oryx.c`, insert the weak default immediately **above** `void raw_hid_receive(uint8_t *data, uint8_t length) {`, then add the call as the first statements inside that function:

```c
// [local patch] Pre-hook so a keymap can claim raw-HID reports before Oryx parses
// them (used for explicit host-OS signaling). Default no-op; the keymap provides a
// strong override. Re-apply this hook if the oryx module is re-vendored from upstream.
__attribute__((weak)) bool raw_hid_receive_user(uint8_t *data, uint8_t length) {
    return false;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (raw_hid_receive_user(data, length)) {
        return;  // claimed by the keymap (e.g. host-OS signaling); don't let Oryx parse it
    }
    uint8_t  command = data[0];
    uint8_t *param   = &data[1];
```

(The existing body — `uint8_t command = data[0];` onward — is unchanged; the snippet above just shows the new lines preceding it.)

- [ ] **Step 2: Compile to verify it still builds**

Run: `qmk compile -kb zsa/moonlander/reva -km wlr-dvorakish`
Expected: builds successfully (`.build/...uf2` produced). Behavior unchanged — the weak hook returns false.

- [ ] **Step 3: Commit**

```bash
git add modules/zsa/oryx/oryx.c
git commit -m "$(cat <<'EOF'
feat(oryx): add raw_hid_receive_user pre-hook ahead of Oryx parsing

Local patch: a weak raw_hid_receive_user is consulted before Oryx's raw-HID
command switch, so a keymap can claim vendor reports (e.g. host-OS signals)
without colliding with Oryx. Default no-op; no behavior change on its own.

Co-Authored-By: Claude Opus 4.8 <noreply@anthropic.com>
EOF
)"
```

---

## Task 3: Host-OS signal handler in the keymap

**Files:**
- Create: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/os_signal.c`
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk`

- [ ] **Step 1: Create the handler**

Create `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/os_signal.c` with exactly:

```c
// Explicit host-OS signaling: receive an authoritative host OS from the USB
// switch (RP2040 broker) over the shared Oryx raw-HID interface and feed it into
// os_detection. See docs/plans/2026-05-29-qmk-os-signaling-design.md.

#include QMK_KEYBOARD_H
#include "raw_hid.h"       // raw_hid_send
#include "os_detection.h"  // os_variant_t, OS_IOS, os_detection_set_explicit

#ifndef RAW_EPSIZE
#    define RAW_EPSIZE 32
#endif

#define OSIG_MAGIC      0xB0
#define OSIG_VERSION    0x01
#define OSIG_MSG_QUERY  0x00
#define OSIG_MSG_SET_OS 0x01
#define OSIG_CAP_SET_OS 0x01  // capability bitmask: bit0 = SET_HOST_OS supported

// Strong override of the weak hook in the oryx module; claims our 0xB0 reports
// before Oryx parses them. Returns true when the report is ours.
bool raw_hid_receive_user(uint8_t *data, uint8_t length);

bool raw_hid_receive_user(uint8_t *data, uint8_t length) {
    if (length < 3 || data[0] != OSIG_MAGIC) {
        return false;  // not ours -> let Oryx handle it
    }
    // We own every 0xB0 report from here, so Oryx never errors on it.
    switch (data[2]) {  // msg_type
        case OSIG_MSG_QUERY: {
            // Always answer with OUR version regardless of the broker's QUERY
            // version byte (data[1]), so version discovery works across mismatches.
            uint8_t ack[RAW_EPSIZE] = {0};
            ack[0] = OSIG_MAGIC;
            ack[1] = OSIG_VERSION;
            ack[2] = OSIG_MSG_QUERY;  // echo msg_type
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
            break;  // claim + ignore unknown msg_type
    }
    return true;
}
```

- [ ] **Step 2: Wire it into the build**

In `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk`, add the source after the existing `SRC += windownav.c` line:

```makefile
OS_DETECTION_ENABLE = yes
SRC += windownav.c
SRC += os_signal.c
```

- [ ] **Step 3: Compile to verify it builds and links**

Run: `qmk compile -kb zsa/moonlander/reva -km wlr-dvorakish`
Expected: builds successfully. The strong `raw_hid_receive_user` in `os_signal.c` overrides the weak default in `oryx.c`; `raw_hid_send` and `os_detection_set_explicit` link from core.

- [ ] **Step 4: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/os_signal.c keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk
git commit -m "$(cat <<'EOF'
feat(keymap): handle explicit host-OS signaling over raw HID

New os_signal.c implements raw_hid_receive_user: it claims 0xB0-tagged
reports ahead of Oryx, answers QUERY with a capability ACK, and applies
SET_HOST_OS via os_detection_set_explicit. Lets the USB switch push the
real host OS so the Mac-vs-not keymap logic works through the switch.

Co-Authored-By: Claude Opus 4.8 <noreply@anthropic.com>
EOF
)"
```

---

## Task 4: Manual hardware verification (no commit)

Unit tests cover the core; the raw-HID path needs hardware. Verify with the keyboard plugged **directly** into a PC (close Keymapp first so it doesn't hold the raw-HID interface), after flashing the Task 3 build.

- [ ] **Step 1: Flash the firmware**

Run: `qmk flash -kb zsa/moonlander/reva -km wlr-dvorakish`
Expected: flashes and the keyboard re-enumerates. (Use `zsa/moonlander/revb` if that's your board — see CLAUDE.md for detecting the revision.)

- [ ] **Step 2: Create a scratch host test script**

Create `test_os_signal.py` anywhere outside the firmware tree (scratch tool, not committed):

```python
#!/usr/bin/env -S uv run -qs
# vim: filetype=python

# /// script
# requires-python = ">=3.12"
# dependencies = [
#     "hidapi>=0.14",
# ]
# ///

import time

import hid

VID, PID = 0x3297, 0x1969  # Moonlander reva normal mode; revb = 0x1972
USAGE_PAGE, USAGE = 0xFF60, 0x61
REPORT_LEN = 32


def find_path() -> bytes:
    for d in hid.enumerate(VID, PID):
        if d["usage_page"] == USAGE_PAGE and d["usage"] == USAGE:
            return d["path"]
    raise SystemExit("raw-HID interface (0xFF60/0x61) not found")


def send(dev: hid.device, payload: list[int]) -> None:
    # hidapi: first byte is the report ID (0 = none), then 32 data bytes
    buf = [0x00] + payload + [0x00] * (REPORT_LEN - len(payload))
    dev.write(buf)


def main() -> None:
    dev = hid.device()
    dev.open_path(find_path())
    dev.set_nonblocking(False)

    # QUERY -> expect ACK: B0 01 00 01 ...
    send(dev, [0xB0, 0x01, 0x00])
    ack = dev.read(REPORT_LEN, timeout_ms=300)
    print("ACK:", " ".join(f"{b:02X}" for b in ack))
    assert ack and ack[0] == 0xB0 and (ack[3] & 0x01), "no/invalid capability ACK"

    # SET_HOST_OS = macOS (3)
    send(dev, [0xB0, 0x01, 0x01, 0x03])
    print("sent SET_HOST_OS=macOS; type to verify Cmd-style behavior")
    time.sleep(3)

    # SET_HOST_OS = Linux (1)
    send(dev, [0xB0, 0x01, 0x01, 0x01])
    print("sent SET_HOST_OS=Linux; behavior should revert to Alt-style")

    dev.close()


if __name__ == "__main__":
    main()
```

- [ ] **Step 3: Run it and confirm the three behaviors**

Run: `./test_os_signal.py`
Expected:
1. Prints an ACK starting `B0 01 00 01` (capability confirmed).
2. After `SET_HOST_OS=macOS`, a key that the keymap remaps under macOS (e.g. the Ctrl→Cmd swap in `keymap.c:804`) behaves Mac-style.
3. After `SET_HOST_OS=Linux`, that same key reverts to the non-Mac (Alt-style) behavior.

If the ACK doesn't arrive, widen the read timeout (RGB rendering can delay the main loop) — this mirrors the broker's 100–250 ms window + retry.

- [ ] **Step 4: Confirm direct-plug native detection still works**

With the script **not** run since the last re-enumeration, confirm the keymap reflects the PC's real OS via native detection (the lock only engages after an explicit push). Re-plug or reboot the keyboard to clear the lock if needed.

---

## Verification summary

- Task 1: `make test:os_detection` green (incl. 5 new cases) — setter, lock-beats-native, keep-last, native-without-explicit, idempotent-report.
- Task 2 & 3: `qmk compile -kb zsa/moonlander/reva -km wlr-dvorakish` builds clean.
- Task 4: hardware QUERY→ACK, SET_HOST_OS flips Mac-vs-not, native still works pre-lock.
- Full regression: `make test:all`.
