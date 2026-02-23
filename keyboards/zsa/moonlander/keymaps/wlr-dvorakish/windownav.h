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

// ── Custom keycodes ────────────────────────────────────────────────────────

enum wn_keycodes {
    WN_KEY_LEFT = SAFE_RANGE,
    WN_KEY_UP,
    WN_KEY_DOWN,
    WN_KEY_RIGHT,
    WN_TAB_LEFT,
    WN_TAB_RIGHT,
    WN_KEY_SCOPE_WINDOW,
    WN_KEY_SCOPE_WORKSPACE,
    WN_KEY_SCOPE_PANE,
    WN_KEY_SCOPE_MONITOR,
    WN_FULLSCREEN,
    WN_FLOAT,
    WN_CLOSE,
    WN_CREATE,
    WN_CONSUME,
    WN_EMIT,
    WN_SWITCHER_FORWARD,
    WN_SWITCHER_BACK,
    WN_SWITCHER_CONFIRM,
    WN_SWITCHER_EXIT,
    WN_WORKSPACE_0,
    WN_WORKSPACE_1,
    WN_WORKSPACE_2,
    WN_WORKSPACE_3,
    WN_WORKSPACE_4,
    WN_WORKSPACE_5,
    WN_WORKSPACE_6,
    WN_WORKSPACE_7,
    WN_WORKSPACE_8,
    WN_WORKSPACE_9,
    WN_SAFE_RANGE,
};

// ── Public API ──────────────────────────────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record);
void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer);
void wn_set_leds(void);
void wn_init(uint8_t windownav_layer, uint8_t switcher_layer,
             uint8_t launcher_layer, uint8_t scratchpad_layer);
