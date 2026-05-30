# Response: QMK ↔ USB-switch host-OS signaling — interface review

**From:** the QMK-firmware side (reviewed against the actual target firmware — ZSA Moonlander,
`wlr-dvorakish` keymap, this fork of QMK)
**Re:** `qmk-os-signaling-interface.md`
**Status:** accepted in substance; one structural correction + concrete answers to all 8 open
questions below. Nothing here blocks you; most of it tightens the contract.

---

## TL;DR

- Your motivation and your model of QMK's `os_detection` internals are **correct** — I verified each
  claim against the source. Minor additions in §A.
- **One thing to re-frame:** coexistence is *not* a VIA problem. On this keyboard **VIA is disabled**,
  but **ZSA's Oryx community module already owns the standard raw-HID interface** (`usage page
  0xFF60`, `usage 0x61`, `RAW_EPSIZE = 32`) and provides the one and only `raw_hid_receive`. So we
  reuse *that* interface; the conflict to design around is Oryx, not VIA.
- **Your proposed wire format works essentially as-is.** Reusing the Oryx interface means byte 0 is
  interpreted as an Oryx command — and your `magic = 0xB0` happens to fall outside Oryx's command
  space, so it doubles perfectly as the disambiguator. Keep your 32-byte layout.
- **Apply path: your Approach (A) is the right call**, and it's *simpler* than you assumed: this
  keymap reads `detected_host_os()` **synchronously at keypress** and never registers the OS
  callback, so we only need to set the stored value — there's no 250 ms callback latency to worry
  about. It also only distinguishes **Mac-family vs. not**, so precision beyond that is a bonus.
- **One new MUST for the broker:** because the keyboard holds OS in RAM and may reboot, you must
  **re-push on every (re)enumeration of the keyboard**, not only on switch/change. You already commit
  to "re-send on connect" — keep it; it's load-bearing.

---

## A. Corrections & confirmations to your §3 (QMK internals)

All confirmed:

- `os_variant_t` = `{OS_UNSURE=0, OS_LINUX=1, OS_WINDOWS=2, OS_MACOS=3, OS_IOS=4}` ✔
- `detected_host_os()` returns the stored guess ✔
- Sticky classifier (`detected_os` only replaced by a non-`UNSURE` guess; Linux needs
  `count == cnt_ff`, iOS needs `count == 4`) — accurate; your "can't re-target once dirty"
  reasoning holds ✔
- `erase_wlength_data()` referenced **only** by the test suite ✔
- `slave_update_detected_host_os()` works as you describe ✔ — **caveat:** it's compiled only under
  `#if defined(SPLIT_KEYBOARD) && defined(SPLIT_DETECTED_OS_ENABLE)`. The Moonlander is **not** a QMK
  "split" (single controller + I²C GPIO expander), so that function isn't built here. It's still a
  fine *model* to copy; we just can't call it directly.

Two additions:

1. `os_detection_task()` fires **`process_detected_host_os_modules(os)` *before* `_kb`/`_user`**
   (`os_detection.c:113`). No module overrides it in this tree, so injecting an OS triggers nothing
   surprising — just noting it exists.
2. `process_wlength()` is invoked from `usb_descriptor.c:1246` (ChibiOS / this board) on
   `GET_DESCRIPTOR(String)`. So your "broker can simply not request string descriptors → native
   detection stays `OS_UNSURE`" claim is mechanically correct. We will *also* add a firmware lock
   (below), so you don't have to rely on that politeness.

---

## B. The one structural correction: the interface is already occupied by Oryx (not VIA)

- `raw_hid_receive` is a **single override point** — there is no `_kb`/`_user` weak chain for it
  (`quantum/raw_hid.c:11` is the weak default; `modules/zsa/oryx/oryx.c:110` is the strong override
  in this build). So we cannot simply "add our own handler"; we extend/interpose on Oryx's.
- VIA is **off** (`oryx`'s manifest sets `"via": false`; nothing enables it). So your OPEN about a
  "VIA command-ID carve-out vs. separate interface" maps onto **Oryx**, and the answer is: **reuse
  Oryx's existing interface** (you asked us to pick the lowest-effort path; this is it, and a second
  dedicated USB interface on ChibiOS is meaningfully more work for no benefit here).

**What this means for you (the broker):** target the existing `0xFF60 / 0x61` interface exactly as
you planned. The keyboard-side mechanics of sharing it with Oryx are **our problem, not yours** — see
§E for the boundary. The only thing it imposes on the wire format is the `magic`-byte choice, which
your draft already satisfies.

---

## C. Point-by-point answers to your 8 open questions

1. **Interface choice (raw HID `0xFF60/0x61` vs. dedicated):** **Reuse standard raw HID
   `0xFF60/0x61`.** It already exists (via Oryx), `RAW_EPSIZE = 32`, host-detectable and OUT-writable.
   No dedicated interface.

2. **VIA coexistence:** **VIA not in use — non-issue.** The incumbent is Oryx; handled keyboard-side
   (§E). No carve-out needed in *your* protocol.

3. **Apply mechanism (A inject vs. B parallel accessor):** **(A), confirmed.** And simpler than your
   write-up: the keymap polls `detected_host_os()` live at keypress (`keymap.c:804`,
   `windownav.c:244`) and does **not** use `process_detected_host_os_*`. So adopting the value is
   "set the stored `detected_os` (+ lock)"; it's visible on the very next keystroke. Zero keymap
   changes required.

4. **New public `os_detection_set_explicit(os_variant_t)`:** **Acceptable**, and a reasonable
   upstream shape (mirrors `slave_update_detected_host_os`). We'll add it plus an "authoritative"
   lock. (See §D for precedence.)

5. **OS enum on the wire:** **Use QMK's `os_variant_t` values directly** (0..4 as above). The keymap
   consumes them verbatim — no translation. Your `version` byte is enough to remap later in the
   unlikely event the enum changes (it's been append-only historically).

6. **Capability handshake — is interface-presence + `version` byte enough?** **No — please add a
   tiny query/ack.** Because *every* ZSA-with-Oryx keyboard exposes `0xFF60/0x61`, interface presence
   alone cannot distinguish "OS-aware firmware" from "stock Oryx." Recommended: broker sends a
   `QUERY` message; capable firmware replies on the IN endpoint with an ACK (echo `magic`, report
   `version` + supported `msg_type`s). **Stock Oryx answers the same bytes with its error event**
   (`byte0 = 0xFF` `ORYX_EVT_ERROR`, `byte1 = 0xFF` `ORYX_ERR_UNKNOWN_COMMAND`), which you can treat
   as "not capable." That gives you a *positive* capability test over the shared interface. (If you'd
   rather just statically configure "this port is OS-aware," the handshake is optional — but it's
   cheap and makes the contract self-describing.)

7. **32-byte fixed report:** **Fine.** `RAW_EPSIZE = 32` confirmed on ChibiOS; the message uses 4
   bytes, rest zero.

8. **"Host" is an RP2040 USB host, not a PC app:** **No concern.** Raw-HID OUT (interrupt OUT) is
   host-agnostic; nothing in QMK gates on the host being a PC application. Requirement is only
   standard enumeration + interrupt-OUT writes, which TinyUSB host does. (Capability ACK uses the
   interrupt-IN endpoint; make sure your host polls it if you implement the handshake.)

---

## D. Concrete contract we'll implement (keyboard side)

### Transport
Existing Oryx raw-HID interface: **usage page `0xFF60`, usage `0x61`, report size 32**. Broker writes
OUT reports; capability ACK (if used) comes back on the IN endpoint.

### Wire format — accepted as drafted

| Offset | Field      | Value / meaning |
|-------:|------------|-----------------|
| 0 | `magic`    | `0xB0` — sanity tag **and** Oryx-disambiguation byte (outside Oryx's command space: Oryx uses `0x00..0x0A`, `0xFE`). **Keep this value.** |
| 1 | `version`  | `0x01` |
| 2 | `msg_type` | `0x01 = SET_HOST_OS`; reserve `0x00 = QUERY` for the capability handshake |
| 3 | `os`       | `os_variant_t` (0..4), QMK values directly |
| 4..31 | reserved | zero |

Idempotent re-sends: **applying the same OS twice is a no-op** beyond re-confirming it (matches your
requirement). ✔

### Apply semantics (Approach A)
`os_detection_set_explicit(os)` sets the stored `detected_os` and marks it authoritative. Because the
keymap polls live, it takes effect on the next keypress. We'll also stamp the debounce/report path so
any future callback-based consumer still works.

### Precedence (your §4.4)
We add a firmware **lock**: once `os_detection_set_explicit()` has been called, `process_wlength()`
stops overwriting `detected_os`. This makes precedence robust **regardless of broker behavior** — your
offer to suppress `GET_DESCRIPTOR(String)` is welcome belt-and-suspenders but **not required**. Native
detection stays enabled, so direct-plug-into-a-PC still self-detects until/unless an explicit value
arrives (the lock only engages after the first explicit signal).

### `OS_UNSURE` policy (your §4.5)
**Keep the last applied OS.** `os_detection_set_explicit(OS_UNSURE)` is a no-op that preserves the
prior value and the lock. So you may send `OS_UNSURE` freely without disturbing a good prior value —
though, per your draft, please still prefer a cached real value when you have one.

---

## E. The Oryx boundary (FYI — keyboard-side, not your concern)

So you understand why the `magic` byte matters and why nothing else leaks to you: on capable firmware
we interpose ahead of Oryx (a small `raw_hid_receive_user`-style pre-hook) that claims only messages
with `magic = 0xB0` and forwards everything else to Oryx untouched. Stock firmware has no such hook,
so your `0xB0` message falls through to Oryx's `default:` and is answered with the error event noted
in Q6 — which is exactly what makes the capability handshake reliable. None of this changes the bytes
on the wire.

---

## F. New/explicit requirements for the broker

- **MUST re-push the current OS on every (re)enumeration of the keyboard**, not only on switch / OS
  change. The keyboard holds OS in RAM and can reboot (power blips, future KVM-reset mitigations, a
  broker-side re-enumeration); re-push is what makes it self-heal. (Your "re-send on connect" already
  covers this — just don't drop it.)
- **SHOULD** implement the `QUERY` handshake (Q6) for positive capability detection, unless you're
  statically configuring capability per port.
- **MAY** suppress `GET_DESCRIPTOR(String)` during enumeration; not required (we lock firmware-side).

## G. Non-goals — agreed

Your three non-goals (hid_device detection algorithm / I²C / broker scheduling; descriptor-spoofing
fallback for stock keyboards; NV persistence) are all fine and out of scope here. We confirm we do
**not** need host-side companion software.

---

### Open items we'd like back from you
1. Confirm you'll adopt the `magic = 0xB0`, `msg_type 0x00 = QUERY / 0x01 = SET_HOST_OS` framing, or
   propose tweaks.
2. Confirm whether you want the capability handshake (Q6) or prefer static per-port configuration.
3. Confirm the broker will re-push on every keyboard (re)enumeration (§F).

Once these are settled we'll write the QMK-side implementation spec (the `os_detection_set_explicit`
+ lock + Oryx pre-hook + magic-tagged handler).
