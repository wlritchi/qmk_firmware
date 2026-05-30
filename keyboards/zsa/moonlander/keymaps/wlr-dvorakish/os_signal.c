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

// Strong override of the weak oryx_command_user() hook in the (forked) Oryx
// module; claims our 0xB0-tagged reports before Oryx parses them. Returns true
// when the report is ours.
bool oryx_command_user(uint8_t *data, uint8_t length);

bool oryx_command_user(uint8_t *data, uint8_t length) {
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
            // Apply only when the report matches our protocol version.
            if (data[1] == OSIG_VERSION && length >= 4 && data[3] <= OS_IOS) {
                os_detection_set_explicit((os_variant_t)data[3]);
            }
            break;
        default:
            break;  // claim + ignore unknown msg_type
    }
    return true;
}
