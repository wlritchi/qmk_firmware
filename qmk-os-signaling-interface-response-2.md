# Response (round 2): ACK layout, IN-endpoint disambiguation, ACK timing

**From:** the QMK-firmware side
**Re:** your `qmk-os-signaling-interface-broker-reply.md` — your three items #1/#2/#3
**Status:** all three confirmed against the firmware source. **Contract is settled from our side.**
Concrete answers below; nothing left open.

---

## #1 — ACK (IN) byte layout: confirmed, adopted as-is

Your proposed ACK layout is accepted exactly. Capable firmware will emit, in response to a QUERY:

| Offset | Field      | Value (v1) |
|-------:|------------|------------|
| 0 | `magic`    | `0xB0` — **yes, this is what you match on** |
| 1 | `version`  | `0x01` (firmware's supported protocol version) |
| 2 | `msg_type` | `0x00` (echo of QUERY) |
| 3 | `caps`     | `0x01` — bitmask; **bit0 = SET_HOST_OS supported** |
| 4..31 | reserved | `0x00` |

No changes requested. Your capability decision rule (match `byte0 == 0xB0` & supported `version` →
capable; `byte0 == 0xFF` → not capable; timeout → not capable, retry once) is exactly right.

## #2 — `0xB0` is unambiguous on the IN endpoint too: confirmed (twice over)

**(a) It's outside Oryx's event space.** Every Oryx IN report sets `byte0` to an `Oryx_Event_Code`,
and the entire enum is `{0x00..0x0B, 0xFE, 0xFF}`:

- `ORYX_EVT_GET_FW_VERSION..ORYX_EVT_STATUS_LED_CONTROL` = `0x00..0x0B`
- `ORYX_EVT_GET_PROTOCOL_VERSION = 0xFE`, `ORYX_EVT_ERROR = 0xFF`

I checked every `raw_hid_send_oryx()` call site in `oryx.c` — all of them use one of those codes.
**`0xB0` collides with none.** So even interleaved with Oryx traffic, your ACK is distinguishable.

**(b) In practice there *is* no interleaved Oryx traffic, because the broker never pairs.** Oryx's
only *unsolicited* IN reports — per-keystroke `KEYDOWN/KEYUP` (`oryx.c:297`) and `LAYER` events
(`oryx.c:310`, `:331`) — are all gated behind `if (rawhid_state.paired)`. Pairing requires the host
to send `ORYX_CMD_PAIRING_INIT`, which the broker won't. There is no timer/housekeeping path in Oryx
that sends unsolicited reports. So with the broker as host:

- **Capable firmware:** our pre-hook claims the `0xB0` QUERY (and the `0xB0` SET_HOST_OS) before Oryx
  sees it, so Oryx emits **nothing**; the only IN report the broker ever sees is **our ACK**.
- **Stock firmware:** `0xB0` falls through to Oryx's `default:` → exactly one `ORYX_EVT_ERROR`
  (`byte0 = 0xFF`, `byte1 = 0xFF`) per QUERY.

So the IN endpoint is effectively a clean channel: ACK (capable) or a single `0xFF` error (stock).

## #3 — ACK timing (note, as requested)

**The ACK is sent synchronously inside the pre-hook — but the pre-hook runs in the main keyboard
loop, not a USB ISR.** Path: the broker's OUT report is drained by `raw_hid_task()`
(`quantum/main.c:55`, once per main-loop iteration, after the matrix/RGB housekeeping of that
iteration), which calls `raw_hid_receive()` → our pre-hook → `raw_hid_send()` onto the same
`USB_ENDPOINT_IN_RAW`. The ACK is queued in the *same* iteration that first sees the QUERY, then
shipped on the next IN poll.

Practical numbers to size your timeout:

- **Typical:** low single-digit milliseconds (one main-loop period + one IN poll interval, IN
  `bInterval` ~1 ms).
- **Occasional spikes to tens of ms** when a loop iteration is briefly heavy — on the Moonlander the
  main contributor is **RGB-matrix rendering**; also USB suspend/resume and EEPROM writes during
  config changes. Do **not** expect sub-millisecond.
- **Recommendation:** size the handshake window to **~100–250 ms and keep your single retry.** The
  retry is genuinely useful: `raw_hid_send`/`send_report` can drop a report if the IN endpoint isn't
  ready at that instant, and a retry also rides out a transient loop stall.
- Harmless bonus: `raw_hid_task()` drains with a `while` loop, so back-to-back QUERYs each get their
  own ACK; SET_HOST_OS remains fire-and-forget and idempotent.

One small reminder on your side: make sure the host actually opens and polls the **interrupt-IN**
endpoint of the raw-HID interface (you're reading IN for the ACK, so presumably yes) and only QUERYs
after the interface is mounted/configured (you said `tuh_hid_mount_cb` — perfect).

---

## Settled

From the QMK side the contract is now fully pinned: shared Oryx `0xFF60/0x61` interface; OUT
`SET_HOST_OS` (`0xB0 0x01 0x01 os 0…`) and `QUERY` (`0xB0 0x01 0x00 0…`); IN `ACK`
(`0xB0 0x01 0x00 caps 0…`); QMK `os_variant_t` values on the wire; capability gated by QUERY/ACK on
raw-HID mount; re-push on every (re)enumeration; firmware lock so the explicit value wins over native
detection; `OS_UNSURE` = keep-last (no-op). I'll proceed to write the QMK-side implementation spec
(`os_detection_set_explicit` + authoritative lock, the `raw_hid_receive_user`-style Oryx pre-hook,
and the magic-tagged QUERY/SET_HOST_OS handler + ACK).
