#include "windownav.h"

extern rgb_config_t rgb_matrix_config;

// ── State ───────────────────────────────────────────────────────────────────

static uint8_t wn_scope  = WN_SCOPE_WINDOW;
static uint8_t wn_prefix = WN_PREFIX_NONE;
static uint8_t wn_layer_windownav   = 0;
static uint8_t wn_layer_switcher    = 0;
static uint8_t wn_layer_launcher    = 0;
static uint8_t wn_layer_scratchpad  = 0;
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

void wn_init(uint8_t windownav_layer, uint8_t switcher_layer,
             uint8_t launcher_layer, uint8_t scratchpad_layer) {
    wn_layer_windownav  = windownav_layer;
    wn_layer_switcher   = switcher_layer;
    wn_layer_launcher   = launcher_layer;
    wn_layer_scratchpad = scratchpad_layer;
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

// ── LED index mapping ───────────────────────────────────────────────────────
// Moonlander LED indices are column-major per half. These were derived from
// the rgb_matrix layout in keyboard.json mapping LED index → matrix position,
// then cross-referenced with LAYOUT_moonlander key order.
//
// Left hand columns 0-6 top-to-bottom, right hand columns 6-0 top-to-bottom.
// Thumb clusters and red buttons follow.

// Directional keys (cyan)
#define LED_KEY_UP     52  // c position: right upper key 3 [7,3]
#define LED_KEY_LEFT   58  // h position: right home key 2  [8,2]
#define LED_KEY_DOWN   53  // t position: right home key 3  [8,3]
#define LED_KEY_RIGHT  48  // n position: right home key 4  [8,4]

// Action modifiers (magenta)
#define LED_MOD_CTRL   2   // left home key 0  [2,0]
#define LED_MOD_SHIFT  33  // left thumb key 1  [5,1]

// Scope keys (active = green, inactive = yellow)
#define LED_SCOPE_PANE      21  // p position: left upper key 4  [1,4]
#define LED_SCOPE_MONITOR   12  // o position: left home key 2   [2,2]
#define LED_SCOPE_WORKSPACE 43  // s position: right home key 5  [8,5]
#define LED_SCOPE_WINDOW    54  // w position: right lower key 2 [9,3]

// Other bound keys (white)
#define LED_CREATE     7   // a position: left home key 1   [2,1]
#define LED_EMIT       17  // e position: left home key 3   [2,3]
#define LED_CONSUME    27  // i position: left home key 5   [2,5]
#define LED_CLOSE      18  // x position: left lower key 3  [3,3]
#define LED_FULLSCREEN 62  // f position: right upper key 1 [7,1]
#define LED_TAB_LEFT   57  // g position: right upper key 2 [7,2]
#define LED_TAB_RIGHT  47  // r position: right upper key 4 [7,4]
#define LED_FLOAT      49  // v position: right lower key 3 [9,4]
#define LED_NUM_LAYER  31  // num hold: left home key 6     [2,6]
#define LED_LAUNCHER   32  // space: left thumb key 0       [5,0]
#define LED_TOGGLE     34  // toggle: left thumb key 2      [5,2]
#define LED_SW_BACK    70  // tab: right thumb key 0        [11,4]
#define LED_SW_FWD     69  // bksp: right thumb key 1       [11,5]
#define LED_SCRATCHPAD 68  // enter: right thumb key 2      [11,6]

// Launcher layer keys
#define LED_LAUNCH_P   21  // p position: left upper key 4  [1,4]
#define LED_LAUNCH_T   53  // t position: right home key 3  [8,3]
#define LED_LAUNCH_S   43  // s position: right home key 5  [8,5]

// Scratchpad layer keys
#define LED_SCRATCH_C  52  // c position: right upper key 3 [7,3]
#define LED_SCRATCH_L  42  // l position: right upper key 5 [7,5]
#define LED_SCRATCH_T  53  // t position: right home key 3  [8,3]
#define LED_SCRATCH_N  48  // n position: right home key 4  [8,4]

// ── Public: set LEDs based on current state ─────────────────────────────────

void wn_set_leds(void) {
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    uint8_t active_layer = biton32(layer_state);

    // All LEDs off first
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    uint8_t cr = f * 0x00, cg = f * 0xFF, cb = f * 0xFF;  // cyan

    // Launcher layer: only show bound keys
    if (active_layer == wn_layer_launcher) {
        rgb_matrix_set_color(LED_LAUNCH_P, cr, cg, cb);
        rgb_matrix_set_color(LED_LAUNCH_T, cr, cg, cb);
        rgb_matrix_set_color(LED_LAUNCH_S, cr, cg, cb);
        return;
    }

    // Scratchpad layer: only show bound keys
    if (active_layer == wn_layer_scratchpad) {
        rgb_matrix_set_color(LED_SCRATCH_C, cr, cg, cb);
        rgb_matrix_set_color(LED_SCRATCH_L, cr, cg, cb);
        rgb_matrix_set_color(LED_SCRATCH_T, cr, cg, cb);
        rgb_matrix_set_color(LED_SCRATCH_N, cr, cg, cb);
        return;
    }

    // ── WINDOWNAV base / WN_NUM / WN_SWITCHER ──

    // Directional keys + tabs: cyan
    rgb_matrix_set_color(LED_KEY_UP, cr, cg, cb);
    rgb_matrix_set_color(LED_KEY_LEFT, cr, cg, cb);
    rgb_matrix_set_color(LED_KEY_DOWN, cr, cg, cb);
    rgb_matrix_set_color(LED_KEY_RIGHT, cr, cg, cb);
    rgb_matrix_set_color(LED_TAB_LEFT, cr, cg, cb);
    rgb_matrix_set_color(LED_TAB_RIGHT, cr, cg, cb);

    // Action modifiers: magenta (0xFF, 0x00, 0xD2)
    uint8_t mr = f * 0xFF, mg = f * 0x00, mb = f * 0xD2;
    rgb_matrix_set_color(LED_MOD_CTRL, mr, mg, mb);
    rgb_matrix_set_color(LED_MOD_SHIFT, mr, mg, mb);

    // Scope keys: active = green, inactive = yellow
    uint8_t ar = f * 0x00, ag = f * 0xFF, ab = f * 0x00;  // active (green)
    uint8_t yr = f * 0xFF, yg = f * 0xFF, yb = f * 0x00;  // inactive (yellow)
    static const uint8_t scope_leds[] = {
        LED_SCOPE_WINDOW, LED_SCOPE_WORKSPACE, LED_SCOPE_PANE, LED_SCOPE_MONITOR,
    };
    for (int i = 0; i < WN_SCOPE_COUNT; i++) {
        if (i == wn_scope) {
            rgb_matrix_set_color(scope_leds[i], ar, ag, ab);
        } else {
            rgb_matrix_set_color(scope_leds[i], yr, yg, yb);
        }
    }

    // Scoped one-shots: yellow
    rgb_matrix_set_color(LED_CREATE, yr, yg, yb);
    rgb_matrix_set_color(LED_CLOSE, yr, yg, yb);
    rgb_matrix_set_color(LED_FULLSCREEN, yr, yg, yb);
    rgb_matrix_set_color(LED_FLOAT, yr, yg, yb);

    // Prefix keys (consume/emit): cyan
    rgb_matrix_set_color(LED_CONSUME, cr, cg, cb);
    rgb_matrix_set_color(LED_EMIT, cr, cg, cb);

    // Launcher prefixes (OSL layers): cyan
    rgb_matrix_set_color(LED_LAUNCHER, cr, cg, cb);
    rgb_matrix_set_color(LED_SCRATCHPAD, cr, cg, cb);

    // Remaining bound keys: white
    uint8_t wr = f * 0xFF, wg = f * 0xFF, wb = f * 0xFF;
    rgb_matrix_set_color(LED_NUM_LAYER, wr, wg, wb);
    rgb_matrix_set_color(LED_TOGGLE, wr, wg, wb);
    rgb_matrix_set_color(LED_SW_BACK, wr, wg, wb);
    rgb_matrix_set_color(LED_SW_FWD, wr, wg, wb);
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
        return false;
    case WN_KEY_UP:
        send_directional(WN_DIR_UP);
        return false;
    case WN_KEY_DOWN:
        send_directional(WN_DIR_DOWN);
        return false;
    case WN_KEY_RIGHT:
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
    case WN_TAB_LEFT: {
        uint8_t real_mods = get_mods();
        bool is_move = (real_mods & MOD_MASK_SHIFT) || (real_mods & MOD_MASK_CTRL);
        clear_mods();
        uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
        if (is_move) mods |= MOD_BIT(KC_LSFT);
        send_binding(mods, KC_F13);
        set_mods(real_mods);
        return false;
    }
    case WN_TAB_RIGHT: {
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
    case WN_FULLSCREEN: {
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
    case WN_WORKSPACE_0: case WN_WORKSPACE_1: case WN_WORKSPACE_2: case WN_WORKSPACE_3: case WN_WORKSPACE_4:
    case WN_WORKSPACE_5: case WN_WORKSPACE_6: case WN_WORKSPACE_7: case WN_WORKSPACE_8: case WN_WORKSPACE_9: {
        static const uint16_t ws_keys[] = {
            KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
        };
        uint8_t ws_index = keycode - WN_WORKSPACE_0;
        uint8_t real_mods = get_mods();
        bool is_send = real_mods & MOD_MASK_SHIFT;
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
