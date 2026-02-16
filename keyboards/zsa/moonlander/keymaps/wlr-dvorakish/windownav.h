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

// ── Custom keycodes ────────────────────────────────────────────────────────

enum wn_keycodes {
    WN_H = SAFE_RANGE,
    WN_C,
    WN_T,
    WN_N,
    WN_TAB_L,
    WN_TAB_R,
    WN_SCOPE_W,
    WN_SCOPE_S,
    WN_SCOPE_P,
    WN_SCOPE_O,
    WN_FULLSCR,
    WN_FLOAT,
    WN_CLOSE,
    WN_CREATE,
    WN_CONSUME,
    WN_EMIT,
    WN_SW_FWD,
    WN_SW_BACK,
    WN_SW_CONF,
    WN_SW_EXIT,
    WN_WS_0,
    WN_WS_1,
    WN_WS_2,
    WN_WS_3,
    WN_WS_4,
    WN_WS_5,
    WN_WS_6,
    WN_WS_7,
    WN_WS_8,
    WN_WS_9,
    WN_LAUNCH_PROGRAMS,
    WN_LAUNCH_SSH,
    WN_LAUNCH_OATH,
    WN_SCRATCH_NOTES,
    WN_SCRATCH_TERM,
    WN_SCRATCH_LLM,
    WN_SCRATCH_CALC,
    WN_SAFE_RANGE,
};

// ── Public API ──────────────────────────────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record);
void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer);
void wn_set_leds(void);
void wn_init(uint8_t windownav_layer, uint8_t switcher_layer);
