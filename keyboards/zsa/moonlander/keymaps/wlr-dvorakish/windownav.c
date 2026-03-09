#include "windownav.h"

extern rgb_config_t rgb_matrix_config;

// ── State ───────────────────────────────────────────────────────────────────

static uint8_t wn_scope           = WN_SCOPE_WINDOW;
static uint8_t wn_prefix          = WN_PREFIX_NONE;
static uint8_t wn_layer_windownav = 0;
static uint8_t wn_layer_switcher  = 0;
static bool    wn_switcher_active = false;
static bool    wn_was_active      = false;

// ── Key repeat state ─────────────────────────────────────────────────────────

static deferred_token wn_repeat_token   = INVALID_DEFERRED_TOKEN;
static uint16_t       wn_repeat_keycode = KC_NO;

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
    uint8_t action    = get_action();
    uint8_t real_mods = get_mods();
    clear_mods();

    uint8_t  mods;
    uint16_t keycode;

    switch (wn_prefix) {
        case WN_PREFIX_CONSUME:
            keycode = consume_fkeys[direction];
            mods    = scope_mods[wn_scope];
            break;
        case WN_PREFIX_EMIT:
            keycode = emit_fkeys[direction];
            mods    = scope_mods[wn_scope];
            break;
        default:
            keycode = dir_fkeys[direction];
            mods    = scope_mods[wn_scope] | action_mods[action];
            break;
    }

    send_binding(mods, keycode);
    set_mods(real_mods);
    wn_prefix = WN_PREFIX_NONE;
}

// ── Helper: send tab operation ───────────────────────────────────────────────

static void send_tab(uint16_t fkey) {
    uint8_t real_mods = get_mods();
    bool    is_move   = (real_mods & MOD_MASK_SHIFT) || (real_mods & MOD_MASK_CTRL);
    clear_mods();
    uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
    if (is_move) mods |= MOD_BIT(KC_LSFT);
    send_binding(mods, fkey);
    set_mods(real_mods);
}

// ── Key repeat helpers ──────────────────────────────────────────────────────

static void wn_fire_repeat(void) {
    switch (wn_repeat_keycode) {
        case WN_KEY_LEFT:
            send_directional(WN_DIR_LEFT);
            break;
        case WN_KEY_UP:
            send_directional(WN_DIR_UP);
            break;
        case WN_KEY_DOWN:
            send_directional(WN_DIR_DOWN);
            break;
        case WN_KEY_RIGHT:
            send_directional(WN_DIR_RIGHT);
            break;
        case WN_TAB_LEFT:
            send_tab(KC_F13);
            break;
        case WN_TAB_RIGHT:
            send_tab(KC_F16);
            break;
        default:
            break;
    }
}

static uint32_t wn_repeat_callback(uint32_t trigger_time, void *cb_arg) {
    wn_fire_repeat();
    return WN_REPEAT_INTERVAL;
}

static void wn_start_repeat(uint16_t keycode) {
    if (wn_repeat_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(wn_repeat_token);
    }
    wn_repeat_keycode = keycode;
    wn_repeat_token   = defer_exec(WN_REPEAT_DELAY, wn_repeat_callback, NULL);
}

static void wn_stop_repeat(uint16_t keycode) {
    if (wn_repeat_keycode == keycode && wn_repeat_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(wn_repeat_token);
        wn_repeat_token   = INVALID_DEFERRED_TOKEN;
        wn_repeat_keycode = KC_NO;
    }
}

static void wn_cancel_repeat(void) {
    if (wn_repeat_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(wn_repeat_token);
        wn_repeat_token   = INVALID_DEFERRED_TOKEN;
        wn_repeat_keycode = KC_NO;
    }
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
    if (!is_active && wn_was_active) {
        wn_cancel_repeat();
    }
    wn_was_active = is_active;
}

// ── LED indices for scope keys (used for dynamic override) ──────────────────
// Moonlander LED indices are column-major per half, derived from keyboard.json.
#define LED_SCOPE_PANE 21      // p position: left upper key 4  [1,4]
#define LED_SCOPE_MONITOR 12   // o position: left home key 2   [2,2]
#define LED_SCOPE_WORKSPACE 43 // s position: right home key 5  [8,5]
#define LED_SCOPE_WINDOW 54    // w position: right lower key 2 [9,3]

// ── Public: override active scope key from yellow (ledmap) to green ──────────
// Called after set_layer_color(WINDOWNAV) sets the baseline from ledmap.

void wn_set_leds(void) {
    float   f  = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    uint8_t gr = f * 0x00, gg = f * 0xFF, gb = f * 0x00; // green

    static const uint8_t scope_leds[] = {
        LED_SCOPE_WINDOW,
        LED_SCOPE_WORKSPACE,
        LED_SCOPE_PANE,
        LED_SCOPE_MONITOR,
    };
    rgb_matrix_set_color(scope_leds[wn_scope], gr, gg, gb);
}

// ── Helper: get the switcher modifier (alt or cmd depending on OS) ──────────

static uint8_t switcher_mod(void) {
    os_variant_t os = detected_host_os();
    return (os == OS_MACOS || os == OS_IOS) ? KC_LGUI : KC_LALT;
}

// ── Public: process_record ──────────────────────────────────────────────────

bool wn_process_record(uint16_t keycode, keyrecord_t *record) {
    // ── Repeatable keys need both press and release handling ─────────────
    switch (keycode) {
        case WN_KEY_LEFT:
        case WN_KEY_UP:
        case WN_KEY_DOWN:
        case WN_KEY_RIGHT:
        case WN_TAB_LEFT:
        case WN_TAB_RIGHT:
            if (!record->event.pressed) {
                wn_stop_repeat(keycode);
                return false;
            }
            break;
        default:
            if (!record->event.pressed) return true;
            break;
    }

    switch (keycode) {
        // ── Scope keys ──────────────────────────────────────────────────────
        case WN_KEY_SCOPE_WINDOW:
            wn_scope  = WN_SCOPE_WINDOW;
            wn_prefix = WN_PREFIX_NONE;
            return false;
        case WN_KEY_SCOPE_WORKSPACE:
            wn_scope  = WN_SCOPE_WORKSPACE;
            wn_prefix = WN_PREFIX_NONE;
            return false;
        case WN_KEY_SCOPE_PANE:
            wn_scope  = WN_SCOPE_PANE;
            wn_prefix = WN_PREFIX_NONE;
            return false;
        case WN_KEY_SCOPE_MONITOR:
            wn_scope  = WN_SCOPE_MONITOR;
            wn_prefix = WN_PREFIX_NONE;
            return false;

        // ── Directional keys ────────────────────────────────────────────────
        case WN_KEY_LEFT:
            send_directional(WN_DIR_LEFT);
            wn_start_repeat(keycode);
            return false;
        case WN_KEY_UP:
            send_directional(WN_DIR_UP);
            wn_start_repeat(keycode);
            return false;
        case WN_KEY_DOWN:
            send_directional(WN_DIR_DOWN);
            wn_start_repeat(keycode);
            return false;
        case WN_KEY_RIGHT:
            send_directional(WN_DIR_RIGHT);
            wn_start_repeat(keycode);
            return false;

        // ── Prefix keys ─────────────────────────────────────────────────────
        case WN_CONSUME:
            wn_prefix = WN_PREFIX_CONSUME;
            return false;
        case WN_EMIT:
            wn_prefix = WN_PREFIX_EMIT;
            return false;

        // ── Tab keys (unscoped) ─────────────────────────────────────────────
        case WN_TAB_LEFT:
            send_tab(KC_F13);
            wn_start_repeat(keycode);
            return false;
        case WN_TAB_RIGHT:
            send_tab(KC_F16);
            wn_start_repeat(keycode);
            return false;

        // ── Scoped one-shot actions ─────────────────────────────────────────
        case WN_FULLSCREEN:
        case WN_FLOAT:
        case WN_CLOSE:
        case WN_CREATE:
        case WN_ZOOM: {
            static const uint16_t oneshot_fkeys[] = {
                [0] = KC_F17, // fullscreen
                [1] = KC_F18, // float
                [2] = KC_F19, // close
                [3] = KC_F20, // create
                [4] = KC_F21, // zoom
            };
            uint8_t real_mods = get_mods();
            clear_mods();
            send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | scope_mods[wn_scope],
                         oneshot_fkeys[keycode - WN_FULLSCREEN]);
            set_mods(real_mods);
            return false;
        }

        // ── Absolute workspace keys ─────────────────────────────────────────
        case WN_WORKSPACE_0:
        case WN_WORKSPACE_1:
        case WN_WORKSPACE_2:
        case WN_WORKSPACE_3:
        case WN_WORKSPACE_4:
        case WN_WORKSPACE_5:
        case WN_WORKSPACE_6:
        case WN_WORKSPACE_7:
        case WN_WORKSPACE_8:
        case WN_WORKSPACE_9: {
            static const uint16_t ws_keys[] = {
                KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
            };
            uint8_t ws_index  = keycode - WN_WORKSPACE_0;
            uint8_t real_mods = get_mods();
            bool    is_send   = real_mods & MOD_MASK_SHIFT;
            clear_mods();
            uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
            if (is_send) mods |= MOD_BIT(KC_LSFT);
            send_binding(mods, ws_keys[ws_index]);
            set_mods(real_mods);
            return false;
        }

        // ── Switcher keys ───────────────────────────────────────────────────
        case WN_SWITCHER_FORWARD: {
            if (!wn_switcher_active) {
                register_code(switcher_mod());
                layer_on(wn_layer_switcher);
                wn_switcher_active = true;
            }
            tap_code(KC_TAB);
            return false;
        }
        case WN_SWITCHER_BACK: {
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
        case WN_SWITCHER_CONFIRM: {
            if (!wn_switcher_active) return false;
            unregister_code(switcher_mod());
            layer_off(wn_layer_switcher);
            wn_switcher_active = false;
            return false;
        }
        case WN_SWITCHER_EXIT: {
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
