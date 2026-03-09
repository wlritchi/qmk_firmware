#include QMK_KEYBOARD_H
#include "version.h"
#include "windownav.h"

#define OS_DETECTION_KEYBOARD_RESET

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

enum custom_keycodes {
  MACRO_0X = WN_SAFE_RANGE,
  TG_WN,  // toggle WINDOWNAV on keypress (not release)
};

const uint16_t PROGMEM ALWAYS_CTRL_KEYS[] = {
    KC_D,
    0,
};
const uint16_t PROGMEM CTRL_CMD_KEYS[] = {
    KC_C,
    0,
};
const uint16_t PROGMEM CMD_CTRL_KEYS[] = {
    0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        // left top: $ & [ { ( + =
        KC_DLR, KC_AMPR, KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS, KC_EQUAL,
        // right top: = * ) } ] ! #
        KC_EQUAL, KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_EXLM, KC_HASH,

        // left upper: (tab) ' , . p y (nav)
        KC_TAB, KC_QUOTE, KC_COMMA, KC_DOT, KC_P, KC_Y, MO(NAV),
        // right upper: | f g c r l /
        KC_PIPE, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLASH,

        // left home: (esc/ctrl) a o e u i (num)
        MT(MOD_LCTL, KC_ESCAPE), KC_A, KC_O, KC_E, KC_U, KC_I, MO(NUM),
        // right home: @ d h t n s -
        KC_AT, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINUS,

        // left lower: (shift) ; q x j k
        LM(SHIFT, MOD_LSFT), KC_SCLN, KC_Q, KC_X, KC_J, KC_K,
        // right lower: b m w v z (shift)
        KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RIGHT_SHIFT,

        // left bottom: (noop) (super) (alt) (shiftnav) (nav)
        KC_TRANSPARENT, KC_LEFT_GUI, KC_LEFT_ALT, MO(SHIFTNAV), MO(NAV),
        // left red: (noop)
        KC_TRANSPARENT,
        // right red: (delete)
        KC_DELETE,
        // right bottom: (nav) (noop) (noop) (noop) (noop)
        MO(NAV), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        // left thumb cluster: (space) (shift) (windownav)
        KC_SPACE, LM(SHIFT, MOD_LSFT), TG_WN,
        // right thumb cluster: (tab) (backspace) (enter)
        KC_TAB, KC_BSPC, KC_ENTER
    ),
    [SHIFT] = LAYOUT_moonlander(
        // left top: ~ 0 1 2 3 4 (noop)
        KC_TILD, KC_0, KC_1, KC_2, KC_3, KC_4, KC_NO,
        // right top: % 5 6 7 8 9 `
        KC_PERC, KC_5, KC_6, KC_7, KC_8, KC_9, KC_GRAVE,

        // left upper: (shift+tab) " < > P Y (shiftnav)
        LSFT(KC_TAB), KC_DQUO, KC_LABK, KC_RABK, LSFT(KC_P), LSFT(KC_Y), MO(SHIFTNAV),
        // right upper: \ F G C R L ?
        KC_BSLS, LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), KC_QUES,

        // left home: (esc/ctrl) A O E U I (shiftnum)
        KC_TRANSPARENT, LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), MO(SHIFTNUM),
        // right home: ^ D H T N S _
        KC_CIRC, LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS,

        // left lower: (shift) : Q X J K
        KC_TRANSPARENT, KC_COLN, LSFT(KC_Q), LSFT(KC_X), LSFT(KC_J), LSFT(KC_K),
        // right lower: B M W V Z (shift)
        LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_TRANSPARENT,

        // left bottom: (led) (super) (alt) (shiftnav) (shiftnav)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(SHIFTNAV),
        // left red: (noop)
        KC_TRANSPARENT,
        // right red: (noop)
        KC_TRANSPARENT,
        // right bottom: (shiftnav) (noop) (noop) (noop) (noop)
        MO(SHIFTNAV), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        // left thumb cluster: (space) (shift) (alt)
        LSFT(KC_SPACE), KC_TRANSPARENT, KC_TRANSPARENT,
        // right thumb cluster: (tab) (backspace) (enter)
        LSFT(KC_TAB), LSFT(KC_BSPC), LSFT(KC_ENTER)
    ),
    [NUM] = LAYOUT_moonlander(
        // left top: (noop) (noop) F1 F2 F3 F4 (noop)
        KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO,
        // right top: (noop) F5 F6 F7 F8 F9 F10
        KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,

        // left upper: (shift-tab ???) (noop) (noop) (noop) (noop) (noop) (noop)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right upper: (noop) * 7 8 9 (noop) F11
        KC_NO, KC_KP_ASTERISK, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO, KC_F11,

        // left home: (esc/ctrl) (noop) (noop) (noop) (noop) (noop) (num)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        // right home: (noop) = 4 5 6 (noop) F12
        KC_NO, KC_EQUAL, KC_KP_4, KC_KP_5, KC_KP_6, KC_NO, KC_F12,

        // left lower: (shiftnum) (noop) (noop) (noop) (noop) (noop)
        MO(SHIFTNUM), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower: + 1 2 3 (noop) (shift)
        KC_KP_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, KC_TRANSPARENT,

        // left bottom: (led) (super) (alt) (noop) (noop)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO,
        // left red: (noop)
        KC_TRANSPARENT,
        // right red: (noop)
        KC_TRANSPARENT,
        // right bottom: 0 . (noop) (noop) (noop)
        KC_KP_0, KC_KP_DOT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        // left thumb cluster: (space) (shiftnum) (alt)
        KC_TRANSPARENT, MO(SHIFTNUM), KC_TRANSPARENT,
        // right thumb cluster: (tab) (backspace) (enter)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [SHIFTNUM] = LAYOUT_moonlander(
        // left top: (noop) (noop) (shift)+F1 (shift)+F2 (shift)+F3 (shift)+F4 (noop)
        KC_NO, KC_NO, LSFT(KC_F1), LSFT(KC_F2), LSFT(KC_F3), LSFT(KC_F4), KC_NO,
        // right top: (noop) (shift)+F5 (shift)+F6 (shift)+F7 (shift)+F8 (shift)+F9 (shift)+F10
        KC_NO, LSFT(KC_F5), LSFT(KC_F6), LSFT(KC_F7), LSFT(KC_F8), LSFT(KC_F9), LSFT(KC_F10),

        // left upper: (shift-tab) (noop) (noop) (noop) (noop) (noop) (noop)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right upper: (noop) / D E F (noop) (shift)+F11
        KC_NO, KC_KP_SLASH, KC_D, KC_E, KC_F, KC_NO, LSFT(KC_F11),

        // left home: (esc/ctrl) (noop) (noop) (noop) (noop) (noop) (num)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        // right home: (noop) - A B C (noop) (shift)+F12
        KC_NO, KC_KP_MINUS, KC_A, KC_B, KC_C, KC_NO, LSFT(KC_F12),

        // left lower: (shiftnum) (noop) (noop) (noop) (noop) (noop)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower: (noop) (noop) (noop) (noop) (noop) (shift)
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,

        // left bottom: (led) (super) (alt) (noop) (noop)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO,
        // left red: (noop)
        KC_TRANSPARENT,
        // right red: (noop)
        KC_TRANSPARENT,
        // right bottom: 0x (noop) (noop) (noop) (noop)
        MACRO_0X, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        // left thumb cluster: (space) (shiftnum) (alt)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        // right thumb cluster: (tab) (backspace) (enter)
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [NAV] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, KC_PAGE_UP, KC_UP, KC_PGDN, KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_NO,

        MO(SHIFTNAV), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, MO(SHIFTNAV), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [SHIFTNAV] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, LSFT(KC_PAGE_UP), LSFT(KC_UP), LSFT(KC_PGDN), KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, LSFT(KC_HOME), LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RIGHT), LSFT(KC_END), KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [WINDOWNAV] = LAYOUT_moonlander(
        // left top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper: _ _ _ _ p _ _
        KC_NO, KC_NO, KC_NO, KC_NO, WN_KEY_SCOPE_PANE, KC_NO, KC_NO,
        // right upper: _ f g c r _ _
        KC_NO, WN_FULLSCREEN, WN_TAB_LEFT, WN_KEY_UP, WN_TAB_RIGHT, KC_NO, KC_NO,

        // left home: ctrl a o e _ i num
        KC_LCTL, WN_CREATE, WN_KEY_SCOPE_MONITOR, WN_EMIT, KC_NO, WN_CONSUME, MO(WN_NUM),
        // right home: _ _ h t n s _
        KC_NO, KC_NO, WN_KEY_LEFT, WN_KEY_DOWN, WN_KEY_RIGHT, WN_KEY_SCOPE_WORKSPACE, KC_NO,

        // left lower: _ _ _ x _ _
        KC_NO, KC_NO, KC_NO, WN_CLOSE, KC_NO, KC_NO,
        // right lower: _ _ w v z _
        KC_NO, KC_NO, WN_KEY_SCOPE_WINDOW, WN_FLOAT, WN_ZOOM, KC_NO,

        // left bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red
        KC_NO,
        // right red
        KC_NO,
        // right bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb: space(launcher) shift toggle
        OSL(WN_LAUNCHER), KC_LSFT, TG_WN,
        // right thumb: tab(sw-back) bspc(sw-fwd) enter(scratchpad)
        WN_SWITCHER_BACK, WN_SWITCHER_FORWARD, OSL(WN_SCRATCHPAD)
    ),
    [WN_NUM] = LAYOUT_moonlander(
        // left top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right upper: _ _ 7 8 9 _ _
        KC_NO, KC_NO, WN_WORKSPACE_7, WN_WORKSPACE_8, WN_WORKSPACE_9, KC_NO, KC_NO,

        // left home: ctrl _ _ _ _ _ (num)
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        // right home: _ _ 4 5 6 _ _
        KC_NO, KC_NO, WN_WORKSPACE_4, WN_WORKSPACE_5, WN_WORKSPACE_6, KC_NO, KC_NO,

        // left lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower: _ 1 2 3 _ _
        KC_NO, WN_WORKSPACE_1, WN_WORKSPACE_2, WN_WORKSPACE_3, KC_NO, KC_NO,

        // left bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red
        KC_NO,
        // right red
        KC_NO,
        // right bottom: 0 _ _ _ _
        WN_WORKSPACE_0, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb: _ shift _
        KC_NO, KC_TRANSPARENT, KC_NO,
        // right thumb
        KC_NO, KC_NO, KC_NO
    ),
    [WN_LAUNCHER] = LAYOUT_moonlander(
        // left top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper: _ _ _ _ p _ _
        KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_P), KC_NO, KC_NO,
        // right upper
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left home
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right home: _ _ _ t _ s _
        KC_NO, KC_NO, KC_NO, LSA(KC_T), KC_NO, LSA(KC_S), KC_NO,

        // left lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red
        KC_NO,
        // right red
        KC_NO,
        // right bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb
        KC_NO, KC_NO, KC_NO,
        // right thumb
        KC_NO, KC_NO, KC_NO
    ),
    [WN_SCRATCHPAD] = LAYOUT_moonlander(
        // left top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right upper: _ _ _ c _ l _
        KC_NO, KC_NO, KC_NO, MEH(KC_C), KC_NO, MEH(KC_L), KC_NO,

        // left home
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right home: _ _ _ t n _ _
        KC_NO, KC_NO, KC_NO, MEH(KC_T), MEH(KC_N), KC_NO, KC_NO,

        // left lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red
        KC_NO,
        // right red
        KC_NO,
        // right bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb
        KC_NO, KC_NO, KC_NO,
        // right thumb
        KC_NO, KC_NO, KC_NO
    ),
    [WN_SWITCHER] = LAYOUT_moonlander(
        // left top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right top
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left upper
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right upper
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left home
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right home
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // left red
        KC_NO,
        // right red
        KC_NO,
        // right bottom
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        // left thumb: _ _ exit
        KC_NO, KC_NO, WN_SWITCHER_EXIT,
        // right thumb: back fwd confirm
        WN_SWITCHER_BACK, WN_SWITCHER_FORWARD, WN_SWITCHER_CONFIRM
    ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  wn_init(WINDOWNAV, WN_SWITCHER);
}

// NOTE: layer_state_set_user is NOT called on this keyboard because
// MOONLANDER_USER_LEDS causes layer_state_set_kb to skip it.
// Layer change detection is handled in rgb_matrix_indicators_user instead.

#define RGB_MAUVE    0xFF, 0x00, 0xD2

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [BASE] = {
        {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_YELLOW}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_YELLOW}, {RGB_CYAN},
        {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    [SHIFT] = {
        {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    [NUM] = {
        {RGB_BLACK}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_CYAN}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_CYAN},
        {RGB_MAUVE}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_YELLOW}, {RGB_YELLOW}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    [SHIFTNUM] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_CYAN}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN},
        {RGB_MAUVE}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_YELLOW}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    [NAV] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    [SHIFTNAV] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_CYAN}
    },

    // WINDOWNAV: baseline colors (scope keys default to yellow;
    // active scope overridden to green by wn_set_leds)
    [WINDOWNAV] = {
        // left col 0: _ _ ctrl _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        // left col 1: _ _ create/a _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        // left col 2: _ _ monitor/o _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        // left col 3: _ _ emit/e close/x _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_YELLOW}, {RGB_BLACK},
        // left col 4: _ pane/p _ _ _
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left col 5: _ _ consume/i _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK},
        // left col 6: _ _ num
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        // left thumb: launcher/space shift toggle
        {RGB_CYAN}, {RGB_MAUVE}, {RGB_WHITE},
        // left red
        {RGB_BLACK},
        // right col 6: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 5: _ _ workspace/s zoom/z _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_YELLOW}, {RGB_BLACK},
        // right col 4: _ tab-right/r right/n float/v _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW}, {RGB_BLACK},
        // right col 3: _ up/c down/t window/w _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW}, {RGB_BLACK},
        // right col 2: _ tab-left/g left/h _ _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        // right col 1: _ fullscreen/f _ _
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        // right col 0: _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right thumb: scratchpad/enter sw-fwd/bksp sw-back/tab
        {RGB_CYAN}, {RGB_WHITE}, {RGB_WHITE},
        // right red
        {RGB_CYAN}
    },

    // WN_NUM: workspace numpad on right hand
    [WN_NUM] = {
        // left col 0-4 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left col 5-6
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left thumb: _ shift _
        {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK},
        // left red
        {RGB_BLACK},
        // right col 6: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 5: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 4: _ 9 6 3 _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        // right col 3: _ 8 5 2 _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        // right col 2: _ 7 4 1 0
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        // right col 1: _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 0: _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right thumb
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right red
        {RGB_CYAN}
    },

    // WN_LAUNCHER: launcher mnemonic keys
    [WN_LAUNCHER] = {
        // left col 0-3 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left col 4: _ p/programs _ _ _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left col 5-6
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left thumb
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left red
        {RGB_BLACK},
        // right col 6: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 5: _ _ s/ssh _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        // right col 4: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 3: _ _ t/tokens _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        // right col 2-0 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right thumb
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right red
        {RGB_CYAN}
    },

    // WN_SCRATCHPAD: scratchpad mnemonic keys
    [WN_SCRATCHPAD] = {
        // left col 0-6 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left thumb
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left red
        {RGB_BLACK},
        // right col 6: _ _ _ _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 5: _ l/llm _ _ _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right col 4: _ _ n/notes _ _
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        // right col 3: _ c/calc t/terminal _ _
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        // right col 2-0 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right thumb
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right red
        {RGB_CYAN}
    },

    // WN_SWITCHER: only thumb cluster keys bound
    [WN_SWITCHER] = {
        // left col 0-6 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // left thumb: _ _ exit
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        // left red
        {RGB_BLACK},
        // right col 6-0 (all black)
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        // right thumb: back fwd confirm
        {RGB_WHITE}, {RGB_WHITE}, {RGB_WHITE},
        // right red
        {RGB_CYAN}
    },
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    RGB rgb = {
        .r = pgm_read_byte(&ledmap[layer][i][0]),
        .g = pgm_read_byte(&ledmap[layer][i][1]),
        .b = pgm_read_byte(&ledmap[layer][i][2]),
    };
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
  }
}

bool rgb_matrix_indicators_user(void) {
  // Detect WINDOWNAV activation edge here because layer_state_set_user
  // is never called (MOONLANDER_USER_LEDS blocks it in layer_state_set_kb).
  wn_on_layer_change(layer_state, WINDOWNAV);

  if (rawhid_state.rgb_control) {
    return false;
  }
  if (keyboard_config.disable_layer_led) {
    return false;
  }
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
  case WN_NUM:
  case WN_LAUNCHER:
  case WN_SCRATCHPAD:
  case WN_SWITCHER:
    set_layer_color(biton32(layer_state));
    break;
  case WINDOWNAV:
    set_layer_color(WINDOWNAV);
    wn_set_leds();  // override scope keys with active/inactive colors
    break;
  default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode >= WN_KEY_LEFT && keycode < WN_SAFE_RANGE) {
    return wn_process_record(keycode, record);
  }
  if (keycode == TG_WN && record->event.pressed) {
    layer_invert(WINDOWNAV);
    return false;
  }
  // After a launcher or scratchpad key fires, exit windownav entirely
  if (record->event.pressed && keycode != KC_NO) {
    uint8_t top_layer = biton32(layer_state);
    if (top_layer == WN_LAUNCHER || top_layer == WN_SCRATCHPAD) {
      layer_off(WINDOWNAV);
    }
  }
  if (!record->event.pressed) {
    return true;
  }
  switch (keycode) {
  case MACRO_0X:
    SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_X));
    break;
  }
  uint8_t unset_mods = 0;
  uint8_t force_mods = 0;
  bool raw_hit_before = false;
  bool raw_hit_after = false;
  bool override_keycode = false;
  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
    if (get_mods() & MOD_MASK_CTRL) {
      if (
        (keycode < QK_MOMENTARY || keycode > QK_MOMENTARY_MAX)
        && (keycode < QK_MOD_TAP || keycode > QK_MOD_TAP_MAX)
        && (keycode < QK_LAYER_TAP || keycode > QK_LAYER_TAP_MAX)
      ) {
        unset_mods |= MOD_MASK_CTRL;
        force_mods |= MOD_MASK_GUI;
        for (uint16_t i = 0; ALWAYS_CTRL_KEYS[i] != 0; i++) {
          if (keycode == ALWAYS_CTRL_KEYS[i]) {
            unset_mods = 0;
            force_mods = 0;
            break;
          }
        }
        for (uint16_t i = 0; CTRL_CMD_KEYS[i] != 0; i++) {
          if (keycode == CTRL_CMD_KEYS[i]) {
            raw_hit_before = true;
            break;
          }
        }
        for (uint16_t i = 0; CMD_CTRL_KEYS[i] != 0; i++) {
          if (keycode == CMD_CTRL_KEYS[i]) {
            raw_hit_after = true;
            break;
          }
        }
      }
    }
  }
  if (keycode == KC_DLR && (get_mods() & MOD_MASK_ALT)) {
    // hack: alt-dollar comes in as alt-shift-4 because qwerty
    // convert it to alt+` (which is how Aerospace parses it on OS-dvorak anyway, and can be added as a separate bind in Niri)
    keycode = KC_GRAVE;
    override_keycode = true;
  }
  switch (keycode) {
  case KC_GRAVE:
  case KC_BSLS:
    unset_mods |= MOD_MASK_SHIFT;
    break;
  }
  if (unset_mods || force_mods || override_keycode) {
    if (raw_hit_before) {
      register_code(keycode);
      unregister_code(keycode);
    }
    uint8_t real_mods = get_mods();
    set_mods((real_mods & ~unset_mods) | force_mods);
    register_code(keycode);
    unregister_code(keycode);
    set_mods(real_mods);
    if (raw_hit_after) {
      register_code(keycode);
      unregister_code(keycode);
    }
    return false;
  }
  return true;
}
