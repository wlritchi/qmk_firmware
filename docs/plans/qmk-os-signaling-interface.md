# QMK ↔ USB-switch: explicit host-OS signaling — interface contract & motivation

**Status:** draft for review by the QMK-firmware agent
**Audience:** an agent/engineer familiar with QMK who is *not* assumed to know this USB-switch project
**What we want back:** criticism, corrections, and concrete requests/constraints on the interface
below. Once the contract is settled here, the QMK changes get their own full spec; this document only
covers the *boundary* between the switch and the keyboard firmware, plus enough motivation to judge it.

Throughout, **MUST/SHOULD/MAY** are requirements language; **OPEN** marks a question we want your
opinion on; **PROPOSAL** marks something we've sketched but are happy to change.

---

## 1. Motivation

The user runs a QMK keyboard and relies on QMK's `os_detection` feature: the keymap reads the
detected host OS and adjusts some keybinds (so the same muscle memory works across Linux/macOS/
Windows). They want this to keep working when the keyboard is used through our **USB switch** (a
multi-host KVM-style switch built from RP2040 boards).

### Why native `os_detection` cannot work through the switch

The switch puts **two independent USB links** between the keyboard and the real host PC:

```
[real QMK keyboard] --USB--> broker (RP2040, USB HOST) --I2C--> hid_device (RP2040, USB DEVICE) --USB--> [real host PC]
```

- The keyboard enumerates against the **broker**, which is an RP2040 running a TinyUSB *host* stack.
  It never sees the real PC's USB stack.
- QMK's `os_detection` fingerprints the host purely from the `wLength` values of the host's
  `GET_DESCRIPTOR(String)` requests during enumeration (`process_wlength()` in
  `quantum/os_detection.c`, called from `tmk_core/protocol/usb_descriptor.c`). Through the switch,
  the only "host" the keyboard can fingerprint is the broker — a constant. So native detection on
  the keyboard reports something fixed and meaningless, never the real OS.

Two further facts make "just re-trigger native detection per switch" a dead end:

1. **The accumulator is never cleared in production.** `erase_wlength_data()` is referenced only by
   the test suite (`quantum/os_detection/tests/os_detection.cpp`); no USB-reset or state-change path
   calls it. `setups_data` is zero-initialized at boot and only a full MCU reboot clears it. A USB
   bus reset does **not**. (This is also why the KVM mitigation `OS_DETECTION_KEYBOARD_RESET`
   performs a full `soft_reset_keyboard()`, not a re-enumeration.)
2. **The classifier can't be re-targeted once "dirty."** Counters are cumulative and `detected_os`
   is sticky (only ever replaced by a non-`UNSURE` guess). Some rules are non-monotonic — Linux
   needs `count == cnt_ff`, iOS needs exactly `count == 4` — so once any other pattern has been seen,
   those OSes can never be re-detected without a reboot.

**Conclusion:** detection must happen where the real host is actually visible — on the
**hid_device** (the USB-*device* board plugged into each PC) — and the resulting OS must be
**delivered to the keyboard explicitly**. This document is about that delivery.

### Division of responsibility (so you know what the switch already handles)

Everything below is the **switch's** job and needs nothing from QMK; it's here only for context:

- Each `hid_device` reimplements QMK's `wLength` classifier on its TinyUSB *device* side (it has a
  one-line hook into `process_get_descriptor()` to observe `wLength`), debounces it, and holds the
  resulting `os_variant` in RAM. It re-derives the OS on every enumeration of its host.
- The **broker** (the USB host the keyboard is plugged into; also the I²C master) reads the active
  host's OS from the relevant `hid_device` over I²C and is responsible for pushing it to the
  keyboard on connect, on switch, and whenever the active host's OS changes.

So from QMK's perspective: **a USB host (the broker) will hand the keyboard an authoritative
host-OS value over a side channel, and the keyboard should treat it as ground truth.**

---

## 2. What we need from the keyboard firmware (overview)

1. **A capability advertisement + transport**: a vendor/raw-HID interface that our broker (a TinyUSB
   *host*) can detect during enumeration and send OUT reports to. Its mere presence tells the broker
   "this keyboard accepts explicit OS signals," so the broker uses the explicit path and never
   attempts the (fragile, out-of-scope) descriptor-spoofing fallback.
2. **An apply path**: on receiving our message, the keyboard adopts the given OS as the
   authoritative host OS and drives the *existing* OS-dependent keymap logic with it.
3. **Precedence**: the explicit value MUST win over (and not be clobbered by) the keyboard's own
   native detection of the broker.

Note: the entity sending the report is an **RP2040 acting as a USB host**, not a PC application.
There is no host-side companion software and there never will be — the signal is fully automatic.

---

## 3. Our understanding of the relevant QMK internals

Please correct anything wrong here; the contract depends on it.

- `os_variant_t` (in `quantum/os_detection.h`):
  `OS_UNSURE=0, OS_LINUX=1, OS_WINDOWS=2, OS_MACOS=3, OS_IOS=4`.
- `os_variant_t detected_host_os(void)` returns the current best guess.
- After a stable result, `os_detection_task()` fires `process_detected_host_os_kb(os)` →
  `process_detected_host_os_user(os)` (both weak, overridable). Default debounce
  `OS_DETECTION_DEBOUNCE = 250 ms`.
- For split keyboards there's already precedent for *injecting* a detected OS from outside the
  fingerprinter: `slave_update_detected_host_os(os)` sets `detected_os`, stamps `last_time`, and
  sets `debouncing = true` so the normal task path then reports it. This is conceptually very close
  to what we want.
- Raw HID (`RAW_ENABLE = yes`) exposes a vendor HID interface (conventionally usage page `0xFF60`,
  usage `0x61`) with IN/OUT endpoints of `RAW_EPSIZE` (32) bytes, delivering host→keyboard data via
  `raw_hid_receive(uint8_t *data, uint8_t length)`.

---

## 4. Proposed interface contract

### 4.1 Transport & capability advertisement

- The keyboard **MUST** expose a vendor HID interface that a USB host can (a) discover by descriptor
  inspection and (b) write OUT reports to. We intend to match it by **usage page / usage** during
  the broker's enumeration of the keyboard.
- **OPEN (interface choice):** Is QMK's standard raw HID (`0xFF60/0x61`) the right vehicle, or do you
  prefer a dedicated vendor interface? The constraint is only that it be cleanly host-detectable and
  OUT-writable.
- **OPEN (VIA coexistence):** Does this board use VIA? VIA consumes `raw_hid_receive` on `0xFF60`.
  If so, we need either a command-ID carve-out within VIA's raw-HID protocol or a second dedicated
  interface. Your call on which is cleaner / more upstream-friendly.

### 4.2 Wire protocol (PROPOSAL)

A single fixed-size OUT report (`RAW_EPSIZE` = 32 bytes), broker → keyboard:

| Offset | Field        | Value / meaning                                                        |
|-------:|--------------|-----------------------------------------------------------------------|
| 0      | `magic`      | `0xB0` (sanity tag; lets the handler ignore unrelated raw-HID traffic) |
| 1      | `version`    | protocol version, starts at `0x01`                                     |
| 2      | `msg_type`   | `0x01` = `SET_HOST_OS` (room for future messages)                      |
| 3      | `os`         | `os_variant_t` value — **MUST** match QMK's enum so no translation     |
| 4..31  | reserved     | zero                                                                   |

- The keyboard **MUST** ignore reports whose `magic`/`version`/`msg_type` it doesn't recognize.
- Sends are **idempotent**: the broker re-sends the current OS on connect, on every switch, and on
  change. Applying the same value twice MUST be a no-op beyond re-confirming it.
- **OPEN:** Do you want the OS enum carried as QMK's own `os_variant_t` values (our preference), or a
  protocol-stable mapping you control? We'll align to whatever you specify.

### 4.3 Apply semantics

We see two ways for the keyboard to adopt the value. **We recommend (A)** because it reuses the
user's existing keymap logic unchanged, but defer to you.

- **(A) Inject into existing `os_detection` state (recommended).** Add a small public function —
  e.g. `void os_detection_set_explicit(os_variant_t os)` — analogous to
  `slave_update_detected_host_os()`: set `detected_os`, mark it authoritative, and let the normal
  task path fire `process_detected_host_os_kb/_user`. Net effect: `detected_host_os()` and the
  existing callbacks transparently reflect the pushed OS, so a keymap already written against
  `os_detection` needs **no changes**. This best matches the user's original wish to "trigger the
  existing logic."
- **(B) Parallel accessor.** Expose `host_os()` returning the pushed value when valid, else
  `detected_host_os()`, and repoint the keymap at it. Simpler to reason about, but requires keymap
  edits and leaves two sources of truth.

**OPEN:** Which do you prefer, and is a new public API like `os_detection_set_explicit()`
acceptable / potentially upstreamable?

### 4.4 Precedence over native detection

- Once an explicit value has been received, it **MUST** take precedence and **MUST NOT** be
  overwritten by the keyboard's native fingerprinting of the broker (e.g., a "locked/authoritative"
  flag).
- Helpful property from our side: the broker **can avoid issuing any `GET_DESCRIPTOR(String)`
  requests** during its enumeration of the keyboard, so native `os_detection` stays at `OS_UNSURE`
  (`count < 3`) and never produces a competing guess. We're happy to guarantee this if it
  simplifies arbitration.
- **OPEN:** Given that, do you want `OS_DETECTION_ENABLE` to remain on in the switch build (so the
  same firmware also self-detects when the keyboard is plugged *directly* into a PC — a nice bonus),
  with explicit taking precedence when present? Or is it cleaner to gate native detection off in
  this build? Either works for us.

### 4.5 Handling `OS_UNSURE`

- The broker withholds pushing until the hid_device's reading is stable, and only sends `OS_UNSURE`
  as a last resort (host asleep / mid-enumeration / detection never stabilized).
- **OPEN:** Preferred keyboard behavior on receiving `OS_UNSURE` — keep the last applied OS, or fall
  back to a configured default? We'll send it faithfully; you define the policy.

---

## 5. Requirements summary

- **MUST** expose a host-detectable, OUT-writable vendor HID interface (capability + transport).
- **MUST** apply a valid `SET_HOST_OS` message as the authoritative host OS and drive existing
  OS-dependent keymap behavior from it.
- **MUST** make the explicit value win over native detection and survive idempotent re-sends.
- **MUST** match `os` byte values to an enum we both agree on (QMK's `os_variant_t` proposed).
- **SHOULD** ignore malformed/unknown reports gracefully.
- **SHOULD** keep working as a normal QMK keyboard when plugged directly into a PC (no broker).

---

## 6. Open questions for the QMK agent (consolidated)

1. Interface choice: standard raw HID (`0xFF60/0x61`) vs. a dedicated vendor interface?
2. VIA coexistence: is VIA in use, and if so, carve-out vs. separate interface?
3. Apply mechanism: inject into existing `os_detection` state (A) vs. parallel `host_os()` (B)?
4. Is a new public `os_detection_set_explicit(os_variant_t)` (or similar) acceptable/upstreamable?
5. OS enum on the wire: QMK's `os_variant_t` values vs. a mapping you control?
6. Capability handshake: is interface-presence + per-message `version` byte enough, or do you want
   the keyboard to report its supported version back to the broker (e.g., a `HELLO`/`QUERY` reply on
   the IN endpoint)?
7. Report size / `RAW_EPSIZE` assumptions — any issue with a 32-byte fixed report?
8. Any concern with the "host" being an RP2040 USB host rather than a PC app (timing, driver
   expectations, anything QMK gates on the host side)?

---

## 7. Non-goals (for this contract)

- The hid_device's OS detection algorithm, the I²C transport, and broker scheduling are the switch's
  responsibility and are out of scope here (mentioned only for context).
- The descriptor-spoofing fallback for *stock* (unmodified) keyboards is explicitly **not** being
  asked of you; capability negotiation exists precisely so we never need it for this keyboard.
- Non-volatile persistence of OS state is out of scope (the broker holds it in RAM; it self-heals on
  re-enumeration).
