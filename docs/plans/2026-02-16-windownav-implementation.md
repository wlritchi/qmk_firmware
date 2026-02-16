# WINDOWNAV Layer Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Implement the modal window navigation layer described in `docs/plans/2026-02-16-windownav-layer-design.md` for the ZSA Moonlander wlr-dvorakish keymap.

**Architecture:** State machine in `process_record_user` tracking scope (4 values) and prefix (consume/emit). Five QMK layers total: WINDOWNAV (main, toggled), WN_NUM (absolute workspace, momentary), WN_LAUNCHER (one-shot), WN_SCRATCHPAD (one-shot), WN_SWITCHER (programmatic). Directional operations resolved via lookup table indexed by (scope, action, direction) → host keybind (F13-F24 + modifier combos). Separate source file `windownav.c`/`.h` for the new logic.

**Tech Stack:** QMK firmware (C), ZSA Moonlander, LAYER_STATE_16BIT (max 16 layers, currently using 7, adding 4 more = 11 total)

**Key files:**
- `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c` (modify)
- `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.h` (create)
- `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c` (create)
- `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk` (modify)
- `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/config.h` (no change needed)

**Build command:** `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

**Host keybind scheme:** F13-F24 with modifiers. The keyboard sends unique combos; the host WM/app is configured separately to respond to them. The encoding:

| F-key range | Operation type |
|---|---|
| F13=left, F14=up, F15=down, F16=right | Directional (navigate/move/resize) |
| F17=left, F18=up, F19=down, F20=right | Consume (prefix `i` + direction) |
| F21=left, F22=up, F23=down, F24=right | Emit (prefix `e` + direction) |

Modifier encoding for scope (applied to all F-key ranges above):

| Modifier | Scope |
|---|---|
| (none) | Window |
| Alt | Workspace |
| GUI/Super | Pane |
| Alt+GUI | Monitor |

Additional modifier for action (directional only, added on top of scope):

| Additional modifier | Action |
|---|---|
| (none) | Navigate |
| Shift | Move |
| Ctrl | Resize |

Example: "Move window to workspace above" = Alt+Shift+F14. "Navigate pane left" = GUI+F13. "Resize window right" = Ctrl+F16.

For one-shot actions, tabs, absolute workspace, launchers, and scratchpads: individual keybinds documented per task below.

---

### Task 1: Create windownav.h with enums and declarations

**Files:**
- Create: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.h`

**Step 1: Create the header file**

```c
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

// ── Custom keycodes ─────────────────────────────────────────────────────────
// These must be added to the keymap's custom_keycodes enum after SAFE_RANGE.
// Listed here for reference; actual enum values assigned in keymap.c.

// Directional keys (resolve via scope + mods):
//   WN_H, WN_C, WN_T, WN_N
//
// Tab keys (unscoped):
//   WN_TAB_L, WN_TAB_R
//
// Scope keys:
//   WN_SCOPE_W, WN_SCOPE_S, WN_SCOPE_P, WN_SCOPE_O
//
// One-shot actions:
//   WN_FULLSCREEN, WN_FLOAT, WN_CLOSE, WN_CREATE
//
// Prefix keys:
//   WN_CONSUME, WN_EMIT
//
// Switcher keys:
//   WN_SWITCH_FWD, WN_SWITCH_BACK, WN_SWITCH_CONFIRM
//
// Absolute workspace (on WN_NUM layer):
//   WN_WS_0 .. WN_WS_9

// ── Binding table entry ─────────────────────────────────────────────────────

typedef struct {
    uint8_t  mods;
    uint16_t keycode;
} wn_binding_t;

// ── Public API ──────────────────────────────────────────────────────────────

// Call from process_record_user. Returns true if the key was NOT handled
// (pass through to default processing), false if handled (suppress).
bool wn_process_record(uint16_t keycode, keyrecord_t *record);

// Call from layer_state_set_user to reset state on layer changes.
void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer);

// Call from rgb_matrix_indicators_user when WINDOWNAV is active.
// Sets LED colors based on current scope.
void wn_set_leds(void);
```

**Step 2: Compile to verify header syntax**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles successfully (header not yet included anywhere).

**Step 3: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.h
git commit -m "feat(windownav): add header with enums and declarations"
```

---

### Task 2: Create windownav.c with state and binding tables

**Files:**
- Create: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk`

**Step 1: Create windownav.c with state variables and lookup tables**

```c
#include "windownav.h"

// ── State ───────────────────────────────────────────────────────────────────

static uint8_t wn_scope  = WN_SCOPE_WINDOW;
static uint8_t wn_prefix = WN_PREFIX_NONE;

// ── Modifier bits for scope encoding ────────────────────────────────────────

static const uint8_t scope_mods[WN_SCOPE_COUNT] = {
    [WN_SCOPE_WINDOW]    = 0,
    [WN_SCOPE_WORKSPACE] = MOD_BIT(KC_LALT),
    [WN_SCOPE_PANE]      = MOD_BIT(KC_LGUI),
    [WN_SCOPE_MONITOR]   = MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI),
};

// ── F-key bases for directional operations ──────────────────────────────────
// Index by wn_direction: LEFT=0, UP=1, DOWN=2, RIGHT=3

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
    // Clear real mods so they don't interfere with our synthetic mods
    uint8_t real_mods = get_mods();
    clear_mods();

    uint8_t mods = scope_mods[wn_scope] | action_mods[action];
    uint16_t keycode;

    switch (wn_prefix) {
        case WN_PREFIX_CONSUME:
            keycode = consume_fkeys[direction];
            mods = scope_mods[wn_scope]; // no action modifier for consume
            break;
        case WN_PREFIX_EMIT:
            keycode = emit_fkeys[direction];
            mods = scope_mods[wn_scope]; // no action modifier for emit
            break;
        default:
            keycode = dir_fkeys[direction];
            break;
    }

    send_binding(mods, keycode);
    set_mods(real_mods);
    wn_prefix = WN_PREFIX_NONE; // always reset prefix after use
}

// ── Public: layer change handler ────────────────────────────────────────────

void wn_on_layer_change(layer_state_t state, uint8_t windownav_layer) {
    if (layer_state_cmp(state, windownav_layer)) {
        // Layer just activated (or is active): reset state
        // Only reset when transitioning from inactive to active
        // We check this by seeing if the layer is now the highest
    }
    // Always reset scope when WINDOWNAV becomes the highest layer
    // (i.e. we just entered it, not when a sub-layer like WN_NUM is on top)
    if (get_highest_layer(state) == windownav_layer) {
        wn_scope  = WN_SCOPE_WINDOW;
        wn_prefix = WN_PREFIX_NONE;
    }
}

// placeholder: LED implementation in Task 10
void wn_set_leds(void) {}

// placeholder: process_record implementation in subsequent tasks
bool wn_process_record(uint16_t keycode, keyrecord_t *record) {
    return true; // pass through for now
}
```

**Step 2: Add SRC to rules.mk**

Add to `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk`:

```makefile
SRC += windownav.c
```

**Step 3: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles with no errors. Warnings about unused static functions are OK at this stage.

**Step 4: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c \
       keyboards/zsa/moonlander/keymaps/wlr-dvorakish/rules.mk
git commit -m "feat(windownav): add state machine, binding tables, and build config"
```

---

### Task 3: Add custom keycodes and layer enums to keymap.c

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c`

**Step 1: Add `#include "windownav.h"` at the top of keymap.c (after existing includes)**

After line 2 (`#include "version.h"`), add:

```c
#include "windownav.h"
```

**Step 2: Add new layer enums**

Replace the existing `enum layers` (lines 6-14) with:

```c
enum layers {
    BASE,
    SHIFT,
    NUM,
    SHIFTNUM,
    NAV,
    SHIFTNAV,
    WINDOWNAV,
    WN_NUM,
    WN_LAUNCHER,
    WN_SCRATCHPAD,
    WN_SWITCHER,
};
```

That's 11 layers, within the 16-layer limit of `LAYER_STATE_16BIT`.

**Step 3: Replace custom keycodes enum**

Replace the existing `enum custom_keycodes` (lines 16-30) with:

```c
enum custom_keycodes {
    MACRO_0X = SAFE_RANGE,
    // WINDOWNAV directional keys
    WN_H,       // left
    WN_C,       // up
    WN_T,       // down
    WN_N,       // right
    // Tab keys (unscoped)
    WN_TAB_L,   // tab left (g position)
    WN_TAB_R,   // tab right (r position)
    // Scope keys
    WN_SCOPE_W, // window (default)
    WN_SCOPE_S, // workspace
    WN_SCOPE_P, // pane
    WN_SCOPE_O, // monitor/output
    // Scoped one-shot actions
    WN_FULLSCR, // fullscreen / zoom
    WN_FLOAT,   // float toggle
    WN_CLOSE,   // close
    WN_CREATE,  // create / add
    // Prefix keys
    WN_CONSUME, // consume prefix (i)
    WN_EMIT,    // emit prefix (e)
    // Switcher
    WN_SW_FWD,  // switcher forward (backspace in WINDOWNAV)
    WN_SW_BACK, // switcher backward (tab in WINDOWNAV)
    WN_SW_CONF, // switcher confirm (enter/escape in WN_SWITCHER)
    WN_SW_EXIT, // switcher exit to normal (toggle in WN_SWITCHER)
    // Absolute workspace (on WN_NUM layer)
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
    // Launcher keys (on WN_LAUNCHER layer)
    WN_LAUNCH_PROGRAMS,
    WN_LAUNCH_SSH,
    WN_LAUNCH_OATH,
    // Scratchpad keys (on WN_SCRATCHPAD layer)
    WN_SCRATCH_NOTES,
    WN_SCRATCH_TERM,
    WN_SCRATCH_LLM,
    WN_SCRATCH_CALC,
};
```

**Step 4: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles. The new keycodes are defined but not yet used in layers or `process_record_user`.

**Step 5: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "feat(windownav): add custom keycodes and layer enums"
```

---

### Task 4: Define WINDOWNAV and sub-layer keymaps

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c`

**Step 1: Add WINDOWNAV layer to the `keymaps[]` array**

After the existing `[SHIFTNAV]` layer definition (after line 226), and before the closing `};` of the keymaps array, add all five new layers.

Refer to the BASE layer comments for position reference. The Moonlander LAYOUT_moonlander macro has this structure per side:
- Top row: 7 keys
- Upper row: 7 keys
- Home row: 7 keys
- Lower row: 6 keys
- Bottom row: 5 keys + 1 red key
- Thumb cluster: 3 keys

```c
    [WINDOWNAV] = LAYOUT_moonlander(
        // left top: (noop x7 - workspace numbers are on WN_NUM)
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top: (noop x7)
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper: _ _ _ p(pane) _ (WN_NUM)
        KC_NO, KC_NO, KC_NO, WN_SCOPE_P, KC_NO, KC_NO, MO(WN_NUM),
        // right upper: f(fullscr) g(tab-l) c(up) r(tab-r) _ _
        KC_NO, WN_FULLSCR, WN_TAB_L, WN_C, WN_TAB_R, KC_NO, KC_NO,

        // left home: (ctrl) a(add) o(monitor) e(emit) _ i(ingest) _
        KC_LCTL, WN_CREATE, WN_SCOPE_O, WN_EMIT, KC_NO, WN_CONSUME, KC_NO,
        // right home: _ _ h(left) t(down) n(right) s(workspace) _
        KC_NO, KC_NO, WN_H, WN_T, WN_N, WN_SCOPE_S, KC_NO,

        // left lower: _ _ _ x(close) _ _
        KC_NO, KC_NO, KC_NO, WN_CLOSE, KC_NO, KC_NO,
        // right lower: _ _ w(window) v(float) _ _
        KC_NO, KC_NO, WN_SCOPE_W, WN_FLOAT, KC_NO, KC_NO,

        // left bottom: _ _ _ _ _
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red: _
        KC_NO,
        // right red: _
        KC_NO,
        // right bottom: _ _ _ _ _
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb: space(launcher) shift(move mod) TOGGLE
        OSL(WN_LAUNCHER), KC_LSFT, TG(WINDOWNAV),
        // right thumb: tab(sw-back) bksp(sw-fwd) enter(scratchpad)
        WN_SW_BACK, WN_SW_FWD, OSL(WN_SCRATCHPAD)
    ),

    [WN_NUM] = LAYOUT_moonlander(
        // All KC_NO except numpad positions mapped to WN_WS_* keycodes.
        // Layout mirrors the existing NUM layer numpad positions.
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, WN_WS_7, WN_WS_8, WN_WS_9, KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, WN_WS_4, WN_WS_5, WN_WS_6, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, WN_WS_1, WN_WS_2, WN_WS_3, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,
        KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO
    ),

    [WN_LAUNCHER] = LAYOUT_moonlander(
        // All KC_NO except mnemonic positions for launchers.
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, WN_LAUNCH_PROGRAMS, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, WN_LAUNCH_OATH, KC_NO, WN_LAUNCH_SSH, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,
        KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO
    ),

    [WN_SCRATCHPAD] = LAYOUT_moonlander(
        // All KC_NO except mnemonic positions for scratchpads.
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, WN_SCRATCH_CALC, KC_NO, KC_NO, WN_SCRATCH_LLM,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, WN_SCRATCH_TERM, WN_SCRATCH_NOTES, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,
        KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO
    ),

    [WN_SWITCHER] = LAYOUT_moonlander(
        // Nearly all KC_NO. Only backspace/tab/enter/toggle active.
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,
        KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb: _ _ exit-to-normal
        KC_NO, KC_NO, WN_SW_EXIT,
        // right thumb: tab(sw-back) bksp(sw-fwd) enter(sw-confirm)
        WN_SW_BACK, WN_SW_FWD, WN_SW_CONF
    ),
```

**Step 2: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles. The layers are defined but custom keycodes don't do anything yet.

Note: The `WN_LAUNCHER` and `WN_SCRATCHPAD` layer key positions assume Dvorak letter positions. Verify these match:
- `p` = left upper row, 4th key (index 3 in that row) → WN_LAUNCH_PROGRAMS
- `s` = right home row, 6th key (index 5) → WN_LAUNCH_SSH
- `t` = right home row, 4th key (index 3) → WN_LAUNCH_OATH
- `n` = right home row, 5th key (index 4) → WN_SCRATCH_NOTES
- `t` = right home row, 4th key → WN_SCRATCH_TERM
- `l` = right upper row, 6th key → WN_SCRATCH_LLM
- `c` = right upper row, 4th key → WN_SCRATCH_CALC

Double-check these positions against the BASE layer comments before compiling. If a position is wrong, adjust it to match the correct Dvorak letter position.

**Step 3: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "feat(windownav): define all five layer keymaps"
```

---

### Task 5: Implement process_record for directional and scope keys

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c`

**Step 1: Implement wn_process_record in windownav.c**

Replace the placeholder `wn_process_record` function with:

```c
bool wn_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true; // only handle key-down events
    }

    switch (keycode) {
    // ── Scope keys ──────────────────────────────────────────────────────
    case WN_SCOPE_W:
        wn_scope = WN_SCOPE_WINDOW;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_S:
        wn_scope = WN_SCOPE_WORKSPACE;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_P:
        wn_scope = WN_SCOPE_PANE;
        wn_prefix = WN_PREFIX_NONE;
        return false;
    case WN_SCOPE_O:
        wn_scope = WN_SCOPE_MONITOR;
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
    // Tab navigate: bare. Tab move: shift or ctrl.
    // Host keybinds: F13+Ctrl+Shift = tab-left-nav, F16+Ctrl+Shift = tab-right-nav
    // Using Ctrl+Shift+Alt+GUI+F13/F16 to avoid collision with directional bindings.
    // Actually, use a separate range. Let's use Ctrl+Alt+F13 for tab-left-nav,
    // Ctrl+Alt+F16 for tab-right-nav, +Shift for move.
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
    case WN_FULLSCR:
        send_binding(scope_mods[wn_scope], KC_F13);
        // Reuse F13 is wrong — need distinct keycodes for one-shots.
        // Use a separate encoding: Ctrl+Shift+GUI + scope_mods won't collide.
        // Better: define one-shot host keybinds explicitly.
        // F-key approach: scope_mods + Shift+Ctrl + specific key.
        // For simplicity, use letter keys with hyper:
        // fullscreen = Ctrl+Alt+Shift+GUI + F (plus scope mods handled separately)
        // This needs rethinking — see note below.
        return false;

    default:
        return true; // not a WINDOWNAV key, pass through
    }
}
```

**Important note on one-shot and special keybinds:** The F13-F24 range is used for directional, consume, and emit. For non-directional operations (one-shots, tabs, workspace, launchers, scratchpads), we need a different approach since we've exhausted F13-F24.

Options (pick one during implementation):
1. Use letter keycodes with `Ctrl+Alt+Shift+GUI` (hyper) modifier — e.g., Hyper+F for fullscreen, Hyper+V for float. Scope is encoded by adding/removing Alt and GUI from hyper.
2. Use keycodes from the "consumer" or "system" range.
3. Reuse F13-F16 with different modifier combos that don't collide with directional bindings.

**Recommended: Option 1.** Define one-shot bindings as:

```c
// One-shot host keybind table: [scope][action_index] -> binding
// action_index: 0=fullscreen, 1=float, 2=close, 3=create
static const wn_binding_t oneshot_bindings[WN_SCOPE_COUNT][4] = {
    [WN_SCOPE_WINDOW] = {
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI), KC_F},  // fullscreen
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI), KC_V},  // float
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI), KC_X},  // close
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI), KC_A},  // create
    },
    [WN_SCOPE_WORKSPACE] = {
        // Same keys but add Alt to distinguish scope
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT), KC_F},
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT), KC_V},
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT), KC_X},
        {MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_LALT), KC_A},
    },
    // Pane and Monitor scopes: follow the same pattern using scope_mods
    // to differentiate. Since scope_mods uses Alt and GUI, and one-shots
    // use Ctrl+Shift base, combine them:
    // Pane: Ctrl+Shift+GUI + key (GUI encodes pane scope — but that collides
    // with window scope which also uses Ctrl+Shift+GUI!)
    //
    // Better approach: use scope_mods directly:
    //   base = Ctrl+Shift, add scope_mods on top
    //   Window:    Ctrl+Shift + F
    //   Workspace: Ctrl+Shift+Alt + F
    //   Pane:      Ctrl+Shift+GUI + F
    //   Monitor:   Ctrl+Shift+Alt+GUI + F
};
```

Revise the one-shot bindings to use `Ctrl+Shift` as the base for one-shots, plus `scope_mods` for scope encoding. This avoids collision with directional bindings (which use no Ctrl+Shift base). Update the `WN_FULLSCR` etc. cases accordingly:

```c
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
```

**Step 2: Wire wn_process_record into keymap.c's process_record_user**

In `keymap.c`, at the **top** of `process_record_user` (before the existing `if (!record->event.pressed)` check), add:

```c
    // WINDOWNAV handling — must come before macOS modifier swap
    if (keycode >= WN_H && keycode <= WN_SCRATCH_CALC) {
        return wn_process_record(keycode, record);
    }
```

This range check ensures only WINDOWNAV keycodes are routed to the handler, and they bypass the macOS modifier swap logic (which would interfere).

**Step 3: Add layer_state_set_user to keymap.c**

Add this function (it doesn't exist yet in the file):

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    wn_on_layer_change(state, WINDOWNAV);
    return state;
}
```

**Step 4: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles with no errors.

**Step 5: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c \
       keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "feat(windownav): implement directional, scope, tab, one-shot, and prefix handling"
```

---

### Task 6: Implement absolute workspace keycodes

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`

**Step 1: Add workspace handling to wn_process_record**

Add these cases to the switch in `wn_process_record`, before the `default:` case:

```c
    // ── Absolute workspace ──────────────────────────────────────────────
    // WN_WS_0 through WN_WS_9: switch to workspace N, or shift+N = send window
    // Host keybind: Ctrl+Alt + F-key (F13=ws0, F14=ws1, ... uses separate range)
    // Since F13-F24 are taken, use number keys with Ctrl+Alt+Shift+GUI:
    //   Ctrl+Alt+GUI + 0-9 = switch workspace
    //   Ctrl+Alt+GUI+Shift + 0-9 = send window to workspace
    case WN_WS_0: case WN_WS_1: case WN_WS_2: case WN_WS_3: case WN_WS_4:
    case WN_WS_5: case WN_WS_6: case WN_WS_7: case WN_WS_8: case WN_WS_9: {
        uint8_t ws_index = keycode - WN_WS_0;
        uint16_t ws_key = KC_0 + ws_index; // KC_0=0x27, KC_1=0x1E, etc.
        // Actually KC_0 and KC_1-KC_9 are not sequential! KC_1=0x1E..KC_9=0x26, KC_0=0x27.
        // Use a lookup:
        static const uint16_t ws_keys[] = {
            KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,
        };
        uint8_t real_mods = get_mods();
        bool is_send = real_mods & MOD_MASK_SHIFT;
        clear_mods();
        uint8_t mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
        if (is_send) mods |= MOD_BIT(KC_LSFT);
        send_binding(mods, ws_keys[ws_index]);
        set_mods(real_mods);
        return false;
    }
```

**Step 2: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles.

**Step 3: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c
git commit -m "feat(windownav): implement absolute workspace switch/send keycodes"
```

---

### Task 7: Implement launcher and scratchpad keycodes

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`

**Step 1: Add launcher and scratchpad handling to wn_process_record**

These send specific host keybinds directly. The user will configure these per machine. Use `Alt+<key>` as a starting point (the user mentioned `Alt+P` for app launcher).

Add these cases before `default:`:

```c
    // ── Launchers ───────────────────────────────────────────────────────
    // These send specific host keybinds. Adjust per machine.
    case WN_LAUNCH_PROGRAMS:
        send_binding(MOD_BIT(KC_LALT), KC_P);
        return false;
    case WN_LAUNCH_SSH: {
        // Placeholder: Alt+Shift+S (adjust per machine)
        send_binding(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_S);
        return false;
    }
    case WN_LAUNCH_OATH: {
        // Placeholder: Alt+Shift+T (adjust per machine)
        send_binding(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_T);
        return false;
    }

    // ── Scratchpads ─────────────────────────────────────────────────────
    // Toggle visibility of persistent apps. Adjust per machine.
    case WN_SCRATCH_NOTES: {
        // Placeholder: Ctrl+Alt+Shift+N
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_N);
        return false;
    }
    case WN_SCRATCH_TERM: {
        // Placeholder: Ctrl+Alt+Shift+T (common for dropdown terminals)
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_T);
        return false;
    }
    case WN_SCRATCH_LLM: {
        // Placeholder: Ctrl+Alt+Shift+L
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_L);
        return false;
    }
    case WN_SCRATCH_CALC: {
        // Placeholder: Ctrl+Alt+Shift+C
        send_binding(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT), KC_C);
        return false;
    }
```

**Step 2: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles.

**Step 3: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c
git commit -m "feat(windownav): implement launcher and scratchpad keycodes"
```

---

### Task 8: Implement window switcher

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.h`

This is the most complex feature. The switcher must:
1. Register alt (or cmd on macOS) as a held modifier
2. Send tab to cycle the OS window switcher
3. Keep alt held until explicitly confirmed or cancelled
4. Manage the WN_SWITCHER layer

**Step 1: Add layer index storage to windownav.h**

The switcher needs to know layer indices to activate/deactivate them. Add to the public API section of `windownav.h`:

```c
// Must be called once at init to tell windownav which layer indices to use.
void wn_init(uint8_t windownav_layer, uint8_t switcher_layer);
```

**Step 2: Add switcher state and init to windownav.c**

Add near the top of `windownav.c`:

```c
static uint8_t wn_layer_windownav = 0;
static uint8_t wn_layer_switcher  = 0;
static bool    wn_switcher_active = false;
```

Add the init function:

```c
void wn_init(uint8_t windownav_layer, uint8_t switcher_layer) {
    wn_layer_windownav = windownav_layer;
    wn_layer_switcher  = switcher_layer;
}
```

**Step 3: Add switcher handling to wn_process_record**

Add these cases before `default:`:

```c
    // ── Switcher ────────────────────────────────────────────────────────
    case WN_SW_FWD: {
        // Enter switcher (or cycle forward if already in it)
        uint8_t mod = KC_LALT;
        if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            mod = KC_LGUI;
        }
        if (!wn_switcher_active) {
            register_code(mod);
            wn_switcher_active = true;
            layer_on(wn_layer_switcher);
        }
        tap_code(KC_TAB);
        return false;
    }
    case WN_SW_BACK: {
        uint8_t mod = KC_LALT;
        if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            mod = KC_LGUI;
        }
        if (!wn_switcher_active) {
            register_code(mod);
            wn_switcher_active = true;
            layer_on(wn_layer_switcher);
        }
        // shift+tab to go backward
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
        return false;
    }
    case WN_SW_CONF: {
        // Confirm selection: release alt/cmd, exit switcher layer
        if (wn_switcher_active) {
            uint8_t mod = KC_LALT;
            if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
                mod = KC_LGUI;
            }
            unregister_code(mod);
            wn_switcher_active = false;
            layer_off(wn_layer_switcher);
        }
        return false;
    }
    case WN_SW_EXIT: {
        // Exit switcher AND windownav entirely
        if (wn_switcher_active) {
            uint8_t mod = KC_LALT;
            if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
                mod = KC_LGUI;
            }
            unregister_code(mod);
            wn_switcher_active = false;
            layer_off(wn_layer_switcher);
        }
        // Toggle off WINDOWNAV
        layer_off(wn_layer_windownav);
        return false;
    }
```

**Step 4: Call wn_init from keymap.c**

Add to `keyboard_post_init_user` in keymap.c (which already exists for RGB):

```c
void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    wn_init(WINDOWNAV, WN_SWITCHER);
}
```

**Step 5: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles.

**Step 6: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c \
       keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.h \
       keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "feat(windownav): implement window switcher with alt-tab emulation"
```

---

### Task 9: Implement LED feedback

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c`
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c`

**Step 1: Implement wn_set_leds in windownav.c**

Replace the placeholder `wn_set_leds` with an implementation that colors LEDs based on scope. Use the existing `rgb_matrix_set_color` function. Active keys get the scope color; inactive keys are off.

```c
// Scope colors (R, G, B)
static const uint8_t scope_colors[WN_SCOPE_COUNT][3] = {
    [WN_SCOPE_WINDOW]    = {0x00, 0xFF, 0xFF}, // cyan (matches base layer theme)
    [WN_SCOPE_WORKSPACE] = {0xFF, 0xA5, 0x00}, // orange
    [WN_SCOPE_PANE]      = {0x00, 0xFF, 0x00}, // green
    [WN_SCOPE_MONITOR]   = {0xFF, 0x00, 0xFF}, // magenta
};

void wn_set_leds(void) {
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    uint8_t r = f * scope_colors[wn_scope][0];
    uint8_t g = f * scope_colors[wn_scope][1];
    uint8_t b = f * scope_colors[wn_scope][2];

    // Set all LEDs to off first, then light up active keys with scope color
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    // Light up directional keys (h, c, t, n positions) and other active keys
    // with scope color. LED indices must match physical positions.
    // The exact LED indices depend on the Moonlander's LED mapping.
    // For now, set ALL LEDs to scope color as a simple indicator.
    // Refine to per-key coloring once LED index mapping is confirmed.
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }
}
```

Note: A more refined LED map (like the per-key ledmaps in the existing code) can be added later. For the initial implementation, a uniform scope color provides clear feedback about the current scope.

**Step 2: Wire wn_set_leds into rgb_matrix_indicators_user in keymap.c**

In the `rgb_matrix_indicators_user` function in keymap.c, add a case for the WINDOWNAV layer and its sub-layers. Before the `default:` case in the switch:

```c
    case WINDOWNAV:
    case WN_NUM:
    case WN_LAUNCHER:
    case WN_SCRATCHPAD:
    case WN_SWITCHER:
        wn_set_leds();
        break;
```

**Step 3: Compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles.

**Step 4: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/windownav.c \
       keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "feat(windownav): implement scope-dependent LED feedback"
```

---

### Task 10: Clean up and integrate

**Files:**
- Modify: `keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c`

**Step 1: Remove old unused custom keycodes**

The old keycodes `UP_WINDOW`, `LEFT_WINDOW`, `RIGHT_WINDOW`, `DOWN_WINDOW`, `UP_WITHIN_WINDOW`, `LEFT_WITHIN_WINDOW`, `RIGHT_WITHIN_WINDOW`, `DOWN_WITHIN_WINDOW`, `UP_SCREEN`, `LEFT_SCREEN`, `RIGHT_SCREEN`, `DOWN_SCREEN` are superseded by the new WINDOWNAV system. They should already be gone from Task 3, but verify they are fully removed.

**Step 2: Verify the complete layer enum has correct indices**

Ensure the `biton32(layer_state)` calls in `rgb_matrix_indicators_user` correctly handle all 11 layers. The existing switch uses numeric cases 0-5; update to use enum names for clarity:

```c
    switch (biton32(layer_state)) {
    case BASE:
        set_layer_color(BASE);
        break;
    case SHIFT:
        set_layer_color(SHIFT);
        break;
    case NUM:
        set_layer_color(NUM);
        break;
    case SHIFTNUM:
        set_layer_color(SHIFTNUM);
        break;
    case NAV:
        set_layer_color(NAV);
        break;
    case SHIFTNAV:
        set_layer_color(SHIFTNAV);
        break;
    case WINDOWNAV:
    case WN_NUM:
    case WN_LAUNCHER:
    case WN_SCRATCHPAD:
    case WN_SWITCHER:
        wn_set_leds();
        break;
    default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
            rgb_matrix_set_color_all(0, 0, 0);
        break;
    }
```

**Step 3: Verify the ledmap array has entries for existing layers only**

The `ledmap` array currently has entries for BASE through SHIFTNAV (indices 0-5). The `set_layer_color` function reads from this array by index. The WINDOWNAV layers use `wn_set_leds()` instead, so no ledmap entries are needed for them. Verify `set_layer_color` is never called with an index >= the ledmap array size.

**Step 4: Final compile**

Run: `qmk compile -kb zsa/moonlander -km wlr-dvorakish`

Expected: Compiles cleanly with no warnings.

**Step 5: Commit**

```bash
git add keyboards/zsa/moonlander/keymaps/wlr-dvorakish/keymap.c
git commit -m "refactor(windownav): clean up old keycodes and integrate LED handling"
```

---

## Host Keybind Reference

For configuring niri, Aerospace, tmux, etc. on the host side. This is the complete mapping of what the keyboard sends for each operation.

### Directional operations

**F-key = direction:** F13=left, F14=up, F15=down, F16=right

| Operation | Modifiers + F-key |
|---|---|
| Navigate window {dir} | F13-F16 |
| Move window {dir} | Shift + F13-F16 |
| Resize window {dir} | Ctrl + F13-F16 |
| Navigate workspace {dir} | Alt + F13-F16 |
| Move window to workspace {dir} | Alt+Shift + F13-F16 |
| Resize workspace {dir} | Alt+Ctrl + F13-F16 |
| Navigate pane {dir} | GUI + F13-F16 |
| Move pane {dir} | GUI+Shift + F13-F16 |
| Resize pane {dir} | GUI+Ctrl + F13-F16 |
| Navigate monitor {dir} | Alt+GUI + F13-F16 |
| Move window to monitor {dir} | Alt+GUI+Shift + F13-F16 |
| (resize monitor) | Alt+GUI+Ctrl + F13-F16 (likely no-op) |

### Consume/emit

| Operation | Modifiers + F-key |
|---|---|
| Consume window from {dir} | F17-F20 |
| Consume workspace {dir} | Alt + F17-F20 |
| Consume pane from {dir} | GUI + F17-F20 |
| Emit window {dir} | F21-F24 |
| Emit workspace {dir} | Alt + F21-F24 |
| Emit pane {dir} | GUI + F21-F24 |

### Tabs (unscoped)

| Operation | Keybind |
|---|---|
| Tab navigate left | Ctrl+Alt + F13 |
| Tab navigate right | Ctrl+Alt + F16 |
| Tab move left | Ctrl+Alt+Shift + F13 |
| Tab move right | Ctrl+Alt+Shift + F16 |

### One-shot scoped actions

**Base modifiers:** Ctrl+Shift, **+scope_mods** for scope.

| Operation | Window | Workspace | Pane | Monitor |
|---|---|---|---|---|
| Fullscreen | Ctrl+Shift+F | Ctrl+Shift+Alt+F | Ctrl+Shift+GUI+F | Ctrl+Shift+Alt+GUI+F |
| Float | Ctrl+Shift+V | Ctrl+Shift+Alt+V | Ctrl+Shift+GUI+V | Ctrl+Shift+Alt+GUI+V |
| Close | Ctrl+Shift+X | Ctrl+Shift+Alt+X | Ctrl+Shift+GUI+X | Ctrl+Shift+Alt+GUI+X |
| Create | Ctrl+Shift+A | Ctrl+Shift+Alt+A | Ctrl+Shift+GUI+A | Ctrl+Shift+Alt+GUI+A |

### Absolute workspace

| Operation | Keybind |
|---|---|
| Switch to workspace N | Ctrl+Alt+GUI + {0-9} |
| Send window to workspace N | Ctrl+Alt+GUI+Shift + {0-9} |

### Launchers (configurable per machine)

| Operation | Default keybind |
|---|---|
| App launcher | Alt+P |
| SSH prompt | Alt+Shift+S |
| OATH tokens | Alt+Shift+T |

### Scratchpads (configurable per machine)

| Operation | Default keybind |
|---|---|
| Notes | Ctrl+Alt+Shift+N |
| Terminal | Ctrl+Alt+Shift+T |
| LLM | Ctrl+Alt+Shift+L |
| Calculator | Ctrl+Alt+Shift+C |

### Window switcher

Handled natively via alt-tab (Linux) or cmd-tab (macOS). No synthetic keybind needed — the keyboard registers/unregisters the actual alt/cmd modifier.
