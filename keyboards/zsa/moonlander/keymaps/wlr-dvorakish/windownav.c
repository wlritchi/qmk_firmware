#include "windownav.h"

// ── State ───────────────────────────────────────────────────────────────────

static uint8_t wn_scope  = WN_SCOPE_WINDOW;
static uint8_t wn_prefix = WN_PREFIX_NONE;
static uint8_t wn_layer_windownav = 0;
static uint8_t wn_layer_switcher  = 0;
static bool    wn_switcher_active __attribute__((unused)) = false;

// ── Modifier bits for scope encoding ────────────────────────────────────────

static const uint8_t scope_mods[WN_SCOPE_COUNT] = {
    [WN_SCOPE_WINDOW]    = 0,
    [WN_SCOPE_WORKSPACE] = MOD_BIT(KC_LALT),
    [WN_SCOPE_PANE]      = MOD_BIT(KC_LGUI),
    [WN_SCOPE_MONITOR]   = MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI),
};

// ── F-key bases for directional operations ──────────────────────────────────

static const uint16_t dir_fkeys[WN_DIR_COUNT] = {
    [WN_DIR_LEFT]  = KC_F13,
    [WN_DIR_UP]    = KC_F14,
    [WN_DIR_DOWN]  = KC_F15,
    [WN_DIR_RIGHT] = KC_F16,
};

static const uint16_t consume_fkeys[WN_DIR_COUNT] = {
    [WN_DIR_LEFT]  = KC_F17,
    [WN_DIR_UP]    = KC_F18,
    [WN_DIR_DOWN]  = KC_F19,
    [WN_DIR_RIGHT] = KC_F20,
};

static const uint16_t emit_fkeys[WN_DIR_COUNT] = {
    [WN_DIR_LEFT]  = KC_F21,
    [WN_DIR_UP]    = KC_F22,
    [WN_DIR_DOWN]  = KC_F23,
    [WN_DIR_RIGHT] = KC_F24,
};

// ── Action modifier bits ────────────────────────────────────────────────────

static const uint8_t action_mods[WN_ACT_COUNT] = {
    [WN_ACT_NAVIGATE] = 0,
    [WN_ACT_MOVE]     = MOD_BIT(KC_LSFT),
    [WN_ACT_RESIZE]   = MOD_BIT(KC_LCTL),
};

// ── Helper: send a binding (mods + keycode tap) ─────────────────────────────

static void send_binding(uint8_t mods, uint16_t keycode) {
    if (mods) {
        register_mods(mods);
    }
    tap_code(keycode);
    if (mods) {
        unregister_mods(mods);
    }
}

// ── Helper: determine action from currently held real mods ──────────────────

static uint8_t get_action(void) {
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_CTRL) return WN_ACT_RESIZE;
    if (mods & MOD_MASK_SHIFT) return WN_ACT_MOVE;
    return WN_ACT_NAVIGATE;
}

// ── Helper: send directional operation ──────────────────────────────────────

static void __attribute__((unused)) send_directional(uint8_t direction) {
    uint8_t action = get_action();
    uint8_t real_mods = get_mods();
    clear_mods();

    uint8_t mods;
    uint16_t keycode;

    switch (wn_prefix) {
        case WN_PREFIX_CONSUME:
            keycode = consume_fkeys[direction];
            mods = scope_mods[wn_scope];
            break;
        case WN_PREFIX_EMIT:
            keycode = emit_fkeys[direction];
            mods = scope_mods[wn_scope];
            break;
        default:
            keycode = dir_fkeys[direction];
            mods = scope_mods[wn_scope] | action_mods[action];
            break;
    }

    send_binding(mods, keycode);
    set_mods(real_mods);
    wn_prefix = WN_PREFIX_NONE;
}

// ── Public: init ────────────────────────────────────────────────────────────

void wn_init(uint8_t windownav_layer, uint8_t switcher_layer) {
    wn_layer_windownav = windownav_layer;
    wn_layer_switcher  = switcher_layer;
}

// ── Public: layer change handler ────────────────────────────────────────────

void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer) {
    if (get_highest_layer(state) == windownav_layer) {
        wn_scope  = WN_SCOPE_WINDOW;
        wn_prefix = WN_PREFIX_NONE;
    }
}

// ── Public: LED placeholder ─────────────────────────────────────────────────

void wn_set_leds(void) {}

// ── Public: process_record placeholder ──────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record) {
    return true;
}
