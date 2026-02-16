#pragma once

#include QMK_KEYBOARD_H

// ── Scopes ──────────────────────────────────────────────────────────────────

enum wn_scope {
    WN_SCOPE_WINDOW,
    WN_SCOPE_WORKSPACE,
    WN_SCOPE_PANE,
    WN_SCOPE_MONITOR,
    WN_SCOPE_COUNT,
};

// ── Prefix state (for consume/emit) ────────────────────────────────────────

enum wn_prefix {
    WN_PREFIX_NONE,
    WN_PREFIX_CONSUME,
    WN_PREFIX_EMIT,
};

// ── Directions ──────────────────────────────────────────────────────────────

enum wn_direction {
    WN_DIR_LEFT,
    WN_DIR_UP,
    WN_DIR_DOWN,
    WN_DIR_RIGHT,
    WN_DIR_COUNT,
};

// ── Actions ─────────────────────────────────────────────────────────────────

enum wn_action {
    WN_ACT_NAVIGATE,
    WN_ACT_MOVE,
    WN_ACT_RESIZE,
    WN_ACT_COUNT,
};

// ── Binding table entry ─────────────────────────────────────────────────────

typedef struct {
    uint8_t  mods;
    uint16_t keycode;
} wn_binding_t;

// ── Public API ──────────────────────────────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record);
void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer);
void wn_set_leds(void);
void wn_init(uint8_t windownav_layer, uint8_t switcher_layer);
