#include "windownav.h"

extern rgb_config_t rgb_matrix_config;

// ── State ───────────────────────────────────────────────────────────────────

static uint8_t wn_scope  = WN_SCOPE_WINDOW;
static uint8_t wn_prefix = WN_PREFIX_NONE;
static uint8_t wn_layer_windownav = 0;
static uint8_t wn_layer_switcher  = 0;
static bool    wn_switcher_active = false;
static bool    wn_was_active      = false;

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

static void send_directional(uint8_t direction) {
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
    bool is_active = layer_state_cmp(state, windownav_layer);
    if (is_active && !wn_was_active) {
        wn_scope  = WN_SCOPE_WINDOW;
        wn_prefix = WN_PREFIX_NONE;
    }
    wn_was_active = is_active;
}

// ── Scope LED colors (R, G, B) ──────────────────────────────────────────────

static const uint8_t scope_colors[WN_SCOPE_COUNT][3] = {
    [WN_SCOPE_WINDOW]    = {0x00, 0xFF, 0xFF},  // cyan
    [WN_SCOPE_WORKSPACE] = {0xFF, 0xA5, 0x00},  // orange
    [WN_SCOPE_PANE]      = {0x00, 0xFF, 0x00},  // green
    [WN_SCOPE_MONITOR]   = {0xFF, 0x00, 0xFF},  // magenta
};

// ── Public: set LEDs based on current scope ─────────────────────────────────

void wn_set_leds(void) {
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    uint8_t r = f * scope_colors[wn_scope][0];
    uint8_t g = f * scope_colors[wn_scope][1];
    uint8_t b = f * scope_colors[wn_scope][2];
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

// ── Helper: get the switcher modifier (alt or cmd depending on OS) ──────────

static uint8_t switcher_mod(void) {
    os_variant_t os = detected_host_os();
    return (os == OS_MACOS || os == OS_IOS) ? KC_LGUI : KC_LALT;
}

// ── Public: process_record ──────────────────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {

    // ── Scope keys ──────────────────────────────────────────────────────
    case WN_SCOPE_W:
        wn_scope  = WN_SCOPE_WINDOW;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_S:
        wn_scope  = WN_SCOPE_WORKSPACE;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_P:
        wn_scope  = WN_SCOPE_PANE;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_O:
        wn_scope  = WN_SCOPE_MONITOR;
        wn_prefix = WN_PREFIX_NONE;
        return false;

    // ── Directional keys ────────────────────────────────────────────────
    case WN_H:
        send_directional(WN_DIR_LEFT);
        return false;
    case WN_C:
        send_directional(WN_DIR_UP);
        return false;
    case WN_T:
        send_directional(WN_DIR_DOWN);
        return false;
    case WN_N:
        send_directional(WN_DIR_RIGHT);
        return false;

    // ── Prefix keys ─────────────────────────────────────────────────────
    case WN_CONSUME:
        wn_prefix = WN_PREFIX_CONSUME;
        return false;
    case WN_EMIT:
        wn_prefix = WN_PREFIX_EMIT;
        return false;

    // ── Tab keys (unscoped) ─────────────────────────────────────────────
    case WN_TAB_L: {
        uint8_t real_mods = get_mods();
        bool is_move = (real_mods & MOD_MASK_SHIFT) || (real_mods & MOD_MASK_CTRL);
        clear_mods();
        uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
        if (is_move) mods |= MOD_BIT(KC_LSFT);
        send_binding(mods, KC_F13);
        set_mods(real_mods);
        return false;
    }
    case WN_TAB_R: {
        uint8_t real_mods = get_mods();
        bool is_move = (real_mods & MOD_MASK_SHIFT) || (real_mods & MOD_MASK_CTRL);
        clear_mods();
        uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
        if (is_move) mods |= MOD_BIT(KC_LSFT);
        send_binding(mods, KC_F16);
        set_mods(real_mods);
        return false;
    }

    // ── Scoped one-shot actions ─────────────────────────────────────────
    case WN_FULLSCR: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | scope_mods[wn_scope], KC_F);
        set_mods(real_mods);
        return false;
    }
    case WN_FLOAT: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | scope_mods[wn_scope], KC_V);
        set_mods(real_mods);
        return false;
    }
    case WN_CLOSE: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | scope_mods[wn_scope], KC_X);
        set_mods(real_mods);
        return false;
    }
    case WN_CREATE: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | scope_mods[wn_scope], KC_A);
        set_mods(real_mods);
        return false;
    }

    // ── Absolute workspace keys ─────────────────────────────────────────
    case WN_WS_0: case WN_WS_1: case WN_WS_2: case WN_WS_3: case WN_WS_4:
    case WN_WS_5: case WN_WS_6: case WN_WS_7: case WN_WS_8: case WN_WS_9: {
        static const uint16_t ws_keys[] = {
            KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
        };
        uint8_t ws_index = keycode - WN_WS_0;
        uint8_t real_mods = get_mods();
        bool is_send = real_mods & MOD_MASK_SHIFT;
        clear_mods();
        uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
        if (is_send) mods |= MOD_BIT(KC_LSFT);
        send_binding(mods, ws_keys[ws_index]);
        set_mods(real_mods);
        return false;
    }

    // ── Launcher keys ───────────────────────────────────────────────────
    case WN_LAUNCH_PROGRAMS: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LALT), KC_P);
        set_mods(real_mods);
        return false;
    }
    case WN_LAUNCH_SSH: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_S);
        set_mods(real_mods);
        return false;
    }
    case WN_LAUNCH_OATH: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_T);
        set_mods(real_mods);
        return false;
    }

    // ── Scratchpad keys ─────────────────────────────────────────────────
    case WN_SCRATCH_NOTES: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_N);
        set_mods(real_mods);
        return false;
    }
    case WN_SCRATCH_TERM: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_T);
        set_mods(real_mods);
        return false;
    }
    case WN_SCRATCH_LLM: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_L);
        set_mods(real_mods);
        return false;
    }
    case WN_SCRATCH_CALC: {
        uint8_t real_mods = get_mods();
        clear_mods();
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_C);
        set_mods(real_mods);
        return false;
    }

    // ── Switcher keys ───────────────────────────────────────────────────
    case WN_SW_FWD: {
        if (!wn_switcher_active) {
            register_code(switcher_mod());
            layer_on(wn_layer_switcher);
            wn_switcher_active = true;
        }
        tap_code(KC_TAB);
        return false;
    }
    case WN_SW_BACK: {
        if (!wn_switcher_active) {
            register_code(switcher_mod());
            layer_on(wn_layer_switcher);
            wn_switcher_active = true;
        }
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
        return false;
    }
    case WN_SW_CONF: {
        if (!wn_switcher_active) return false;
        unregister_code(switcher_mod());
        layer_off(wn_layer_switcher);
        wn_switcher_active = false;
        return false;
    }
    case WN_SW_EXIT: {
        if (wn_switcher_active) {
            unregister_code(switcher_mod());
            layer_off(wn_layer_switcher);
            wn_switcher_active = false;
        }
        layer_off(wn_layer_windownav);
        return false;
    }

    default:
        return true;
    }
}
