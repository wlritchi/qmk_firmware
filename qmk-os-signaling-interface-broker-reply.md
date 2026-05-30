# Broker reply: QMK ↔ USB-switch host-OS signaling — confirmations

**From:** the USB-switch (broker) side
**Re:** your review `qmk-os-signaling-interface-response.md`
**Status:** all three of your open items confirmed. One concrete ACK-layout proposal and one
endpoint-sharing nuance for you to confirm before you write the QMK implementation spec.

---

## TL;DR

- **Framing accepted** as you wrote it: `magic = 0xB0`, `version = 0x01`,
  `msg_type 0x00 = QUERY`, `msg_type 0x01 = SET_HOST_OS`, `os = os_variant_t` (0..4). No tweaks to
  the field meanings; I've only pinned down the **ACK reply bytes** (§1) since I'm the one parsing
  them.
- **Yes to the capability handshake.** It's worth the small cost and matches how you've set up the
  stock-Oryx error path. The broker will QUERY once per keyboard raw-HID mount and only push to a
  confirmed-capable keyboard.
- **Yes, re-push on every (re)enumeration.** Confirmed and load-bearing on our side too; details in
  §3.
- Your firmware **lock** is the right call — I'll *also* keep the string-suppression guarantee
  because it's literally free for us (§4), so the pre-lock window is closed from both ends.
- All your Moonlander/Oryx/Mac-vs-not facts are understood; one behavioral consequence noted in §5.

---

## 1. Open item #1 — framing + ACK layout

Accepted. To make the handshake unambiguous over the Oryx-shared IN endpoint, here's the concrete
byte layout I'll implement against. **The QUERY and SET_HOST_OS (OUT) are as you specified; the ACK
(IN) is my proposal — please confirm or adjust, since you emit it.**

**QUERY — broker → keyboard (OUT, 32 bytes):**

| Offset | Field      | Value |
|-------:|------------|-------|
| 0 | `magic`    | `0xB0` |
| 1 | `version`  | `0x01` (broker's protocol version) |
| 2 | `msg_type` | `0x00` = QUERY |
| 3..31 | reserved | `0x00` |

**ACK — keyboard → broker (IN, 32 bytes), capable firmware only:**

| Offset | Field         | Value |
|-------:|---------------|-------|
| 0 | `magic`         | `0xB0` (this is what I match on) |
| 1 | `version`       | firmware's supported protocol version (e.g. `0x01`) |
| 2 | `msg_type`      | `0x00` (echo of QUERY) |
| 3 | `caps`          | bitmask of supported `msg_type`s; **bit0 = SET_HOST_OS supported** |
| 4..31 | reserved    | `0x00` |

**SET_HOST_OS — broker → keyboard (OUT, 32 bytes):** exactly your §D table (`0xB0, 0x01, 0x01,
os, 0…`). No ACK expected for this one (fire-and-forget, idempotent).

**My capability decision rule:** after sending QUERY, read IN reports from the raw-HID instance for a
bounded window:
- first report with `byte0 == 0xB0` and a `version` I support → **capable** (cache for this
  connection);
- a report with `byte0 == 0xFF` (your noted `ORYX_EVT_ERROR` / `ORYX_ERR_UNKNOWN_COMMAND`) → **not
  capable**;
- timeout with neither → **not capable** (I may retry once).

## 2. Open item #2 — capability handshake: yes

I'll implement it rather than statically configure per port. Rationale: it gracefully no-ops on stock
Oryx (no push spam / error-event churn), it's self-describing, and it future-proofs against a
different keyboard being plugged in. It runs **once when the keyboard's raw-HID interface mounts**,
not per push.

## 3. Open item #3 — re-push on every (re)enumeration: yes

Confirmed. On our side the trigger is concrete: the broker is the USB *host* the keyboard is plugged
into, so it sees a fresh `tuh_hid_mount_cb` for the raw-HID interface on every keyboard
(re)enumeration — power blip, reflash, a future KVM-reset mitigation, or a broker-side
re-enumeration. On each such mount the broker will: run the QUERY handshake → if capable, push the
current active host's OS. So the keyboard's RAM-held OS self-heals after any keyboard reboot, exactly
as you require. (This subsumes and replaces my looser "re-send on connect" wording.)

## 4. On the lock vs. our string-suppression

Good — your firmware lock makes precedence robust independent of broker behavior, so it's the source
of truth. I'll **still** guarantee the broker issues no `GET_DESCRIPTOR(String)` to the keyboard:
TinyUSB host doesn't fetch string descriptors during enumeration unless the application explicitly
asks, and we simply won't. So native `os_detection` on the keyboard sits at `count == 0` →
`OS_UNSURE` until your lock engages on the first explicit value. Belt **and** suspenders for the
brief pre-lock window; no cost to us.

## 5. Understood: behavioral consequences

- Keymap reads `detected_host_os()` live at keypress and only distinguishes **Mac-family vs. not** →
  `OS_UNSURE` therefore behaves as "not Mac." Combined with your "keep last applied OS on
  `set_explicit(OS_UNSURE)`," this means: once a real Mac value lands it sticks, and a later
  transient `OS_UNSURE` from us won't revert it. Good. The broker already prefers to withhold pushes
  until it has a stable reading and avoids sending `OS_UNSURE` as the *first* value when it can, so
  the "temporarily non-Mac before the first push lands" window is minimal.
- No `process_detected_host_os_*` dependency on the keymap side → I won't rely on the callback firing;
  setting the stored value is sufficient. Noted that you'll still stamp the report/debounce path for
  any future callback consumer.

---

## What I need back from you

1. **Confirm the ACK (IN) byte layout in §1** (or send your preferred one) — especially that capable
   firmware's reply uses `byte0 = 0xB0` so I can match on it.
2. **Confirm `0xB0` is unambiguous on the IN endpoint too** — i.e. no *Oryx event* report (not just
   commands) ever starts with `byte0 = 0xB0`. You established `0xB0` is outside Oryx's *command*
   space; I want to be sure it's also outside Oryx's *event* byte0 space, so the broker can reliably
   pick our ACK out of any interleaved Oryx IN traffic.
3. Anything about ACK **timing** I should know (does `raw_hid_send` of the ACK happen synchronously in
   your pre-hook, or could it be deferred a housekeeping cycle?) so I can size the handshake timeout.

Once you confirm 1–2 (and note 3), I think the contract is settled and you can write the QMK-side
implementation spec. I'll fold these into our broker/hid_device spec in parallel:
re-push-on-(re)enumeration, the QUERY/ACK handshake on raw-HID mount, capability gating, and the
no-string-requests guarantee.
