#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum layers {
  BASE,
  SHIFT,
  NUM,
  SHIFTNUM,
  NAV,
  SHIFTNAV,
  CTRL,
  CTRLSHIFT,
  CTRLNUM,
  CTRLSHIFTNUM,
  CTRLNAV,
  CTRLSHIFTNAV,
};

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  MACRO_0X,
  CC_P,
  CC_Y,
  CC_A,
  CC_O,
  CC_E,
  CC_U,
  CC_I,
  CC_Q,
  CC_X,
  CC_J,
  CC_K,
  CC_F,
  CC_G,
  CC_C,
  CC_R,
  CC_L,
  CC_D,
  CC_H,
  CC_T,
  CC_N,
  CC_S,
  CC_MINUS,
  CC_B,
  CC_M,
  CC_W,
  CC_V,
  CC_Z,
  CC_SHIFT_P,
  CC_SHIFT_Y,
  CC_SHIFT_A,
  CC_SHIFT_O,
  CC_SHIFT_E,
  CC_SHIFT_U,
  CC_SHIFT_I,
  CC_SHIFT_Q,
  CC_SHIFT_X,
  CC_SHIFT_J,
  CC_SHIFT_K,
  CC_SHIFT_F,
  CC_SHIFT_G,
  CC_SHIFT_C,
  CC_SHIFT_R,
  CC_SHIFT_L,
  CC_SHIFT_D,
  CC_SHIFT_H,
  CC_SHIFT_T,
  CC_SHIFT_N,
  CC_SHIFT_S,
  CC_SHIFT_MINUS,
  CC_SHIFT_B,
  CC_SHIFT_M,
  CC_SHIFT_W,
  CC_SHIFT_V,
  CC_SHIFT_Z,
  CC_F1,
  CC_F2,
  CC_F3,
  CC_F4,
  CC_F5,
  CC_F6,
  CC_F7,
  CC_F8,
  CC_F9,
  CC_F10,
  CC_KP7,
  CC_KP8,
  CC_KP9,
  CC_F11,
  CC_KP4,
  CC_KP5,
  CC_KP6,
  CC_F12,
  CC_KP1,
  CC_KP2,
  CC_KP3,
  CC_KP0,
  CC_KPDOT,
  CC_SHIFT_F1,
  CC_SHIFT_F2,
  CC_SHIFT_F3,
  CC_SHIFT_F4,
  CC_SHIFT_F5,
  CC_SHIFT_F6,
  CC_SHIFT_F7,
  CC_SHIFT_F8,
  CC_SHIFT_F9,
  CC_SHIFT_F10,
  CC_SHIFT_F11,
  CC_SHIFT_F12,
  CC_UP,
  CC_LEFT,
  CC_DOWN,
  CC_RIGHT,
  CC_SHIFT_UP,
  CC_SHIFT_LEFT,
  CC_SHIFT_DOWN,
  CC_SHIFT_RIGHT,
};

enum tap_dance_codes {
  DANCE_0,
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
        LT(CTRL, KC_ESCAPE), KC_A, KC_O, KC_E, KC_U, KC_I, MO(NUM),
        // right home: @ d h t n s -
        KC_AT, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINUS,
        
        // left lower: (shift) ; q x j k
        LM(SHIFT, MOD_LSFT), KC_SCLN, KC_Q, KC_X, KC_J, KC_K,
        // right lower: b m w v z (shift)
        KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RIGHT_SHIFT,

        // left bottom: (led) (super) (alt) (shiftnav) (nav)
        MOON_LED_LEVEL, KC_LEFT_GUI, KC_LEFT_ALT, MO(SHIFTNAV), MO(NAV),
        // left red: (noop)
        KC_TRANSPARENT,
        // right red: (noop)
        KC_TRANSPARENT,
        // right bottom: (nav) (noop) (noop) (noop) (noop)
        MO(NAV), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        // left thumb cluster: (space) (shift) (alt)
        KC_SPACE, LM(SHIFT, MOD_LSFT), KC_LEFT_ALT,
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

        // left home: (?????) A O E U I (shiftnum)
        TD(DANCE_0), LSFT(KC_A), LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), MO(SHIFTNUM),
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

        // left home: (esc/ctrlnum) (noop) (noop) (noop) (noop) (noop) (num)
        LT(CTRLNUM, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        // right home: (noop) + 4 5 6 (noop) F12
        KC_NO, KC_KP_PLUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_NO, KC_F12,
        
        // left lower: (shiftnum) (noop) (noop) (noop) (noop) (noop)
        MO(SHIFTNUM), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        // right lower: = 1 2 3 (noop) (shift)
        KC_EQUAL, KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, KC_TRANSPARENT,
        
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
        
        // left home: (esc/ctrlshiftnum) (noop) (noop) (noop) (noop) (noop) (num)
        LT(CTRLSHIFTNUM, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
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

        LT(CTRLNAV, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
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

        LT(CTRLSHIFTNAV, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
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
    [CTRL] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        KC_NO, KC_NO, KC_NO, KC_NO, CC_P, CC_Y, MO(CTRLNAV),
        KC_NO, CC_F, CC_G, CC_C, CC_R, CC_L, KC_NO,
        
        KC_TRANSPARENT, CC_A, CC_O, CC_E, CC_U, CC_I, MO(CTRLNUM),
        KC_NO, CC_D, CC_H, CC_T, CC_N, CC_S, CC_MINUS,
        
        MO(CTRLSHIFT), KC_NO, CC_Q, CC_X, CC_J, CC_K,
        CC_B, CC_M, CC_W, CC_V, CC_Z, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(CTRLSHIFTNAV), MO(CTRLNAV),
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        MO(CTRLNAV), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, MO(CTRLSHIFT), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [CTRLSHIFT] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        KC_NO, KC_NO, KC_NO, KC_NO, CC_SHIFT_P, CC_SHIFT_Y, MO(CTRLSHIFTNAV),
        KC_NO, CC_SHIFT_F, CC_SHIFT_G, CC_SHIFT_C, CC_SHIFT_R, CC_SHIFT_L, KC_NO,
        
        KC_TRANSPARENT, CC_SHIFT_A, CC_SHIFT_O, CC_SHIFT_E, CC_SHIFT_U, CC_SHIFT_I, MO(CTRLSHIFTNUM),
        KC_NO, CC_SHIFT_D, CC_SHIFT_H, CC_SHIFT_T, CC_SHIFT_N, CC_SHIFT_S, CC_SHIFT_MINUS,
        
        KC_TRANSPARENT, KC_NO, CC_SHIFT_Q, CC_SHIFT_X, CC_SHIFT_J, CC_SHIFT_K,
        CC_SHIFT_B, CC_SHIFT_M, CC_SHIFT_W, CC_SHIFT_V, CC_SHIFT_Z, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(CTRLSHIFTNAV), MO(CTRLSHIFTNAV),
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        MO(CTRLSHIFTNAV), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [CTRLNUM] = LAYOUT_moonlander(
        KC_NO, KC_NO, CC_F1, CC_F2, CC_F3, CC_F4, KC_NO,
        KC_NO, CC_F5, CC_F6, CC_F7, CC_F8, CC_F9, CC_F10,
        
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, CC_KP7, CC_KP8, CC_KP9, KC_NO, CC_F11,
        
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, CC_KP4, CC_KP5, CC_KP6, KC_NO, CC_F12,
        
        MO(CTRLSHIFTNUM), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, CC_KP1, CC_KP2, CC_KP3, KC_NO, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        CC_KP0, CC_KPDOT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, MO(CTRLSHIFTNUM), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [CTRLSHIFTNUM] = LAYOUT_moonlander(
        KC_NO, KC_NO, CC_SHIFT_F1, CC_SHIFT_F2, CC_SHIFT_F3, CC_SHIFT_F4, KC_NO,
        KC_NO, CC_SHIFT_F5, CC_SHIFT_F6, CC_SHIFT_F7, CC_SHIFT_F8, CC_SHIFT_F9, CC_SHIFT_F10,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, CC_SHIFT_F11,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, CC_SHIFT_F12,
        
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_NO, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [CTRLNAV] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, LCTL(KC_PAGE_UP), CC_UP, LCTL(KC_PGDN), KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, LCTL(KC_HOME), CC_LEFT, CC_DOWN, CC_RIGHT, LCTL(KC_END), KC_NO,

        MO(CTRLSHIFTNAV), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(CTRLSHIFTNAV), KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, MO(CTRLSHIFTNAV), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [CTRLSHIFTNAV] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, LCTL(LSFT(KC_PAGE_UP)), CC_SHIFT_UP, LCTL(LSFT(KC_PGDN)), KC_NO, KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, LCTL(LSFT(KC_HOME)), CC_SHIFT_LEFT, CC_SHIFT_DOWN, CC_SHIFT_RIGHT, LCTL(LSFT(KC_END)), KC_NO,

        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,

        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

#define RGB_MAUVE    0xFF, 0x00, 0xD2

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [BASE] = {
        {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_MAUVE},
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
        {RGB_BLACK}
    },

    [SHIFT] = {
        {RGB_CYAN}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_WHITE}, {RGB_MAUVE},
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
        {RGB_BLACK}
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
        {RGB_BLACK}
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
        {RGB_BLACK}
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
        {RGB_BLACK}
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
        {RGB_BLACK}
    },

    [CTRL] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    },

    [CTRLSHIFT] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_CYAN}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    },

    [CTRLNUM] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_MAUVE}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN}, {RGB_CYAN},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    },

    [CTRLSHIFTNUM] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_MAUVE}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    },

    [CTRLNAV] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    },

    [CTRLSHIFTNAV] = {
        {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_WHITE}, {RGB_BLACK},
        {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK}, {RGB_MAUVE}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_MAUVE}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_YELLOW}, {RGB_MAUVE}, {RGB_BLACK}, {RGB_WHITE},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_YELLOW}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}, {RGB_BLACK}, {RGB_BLACK},
        {RGB_BLACK}
    }
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
  if (rawhid_state.rgb_control) {
    return false;
  }
  if (keyboard_config.disable_layer_led) {
    return false;
  }
  switch (biton32(layer_state)) {
  case 0:
    set_layer_color(0);
    break;
  case 1:
    set_layer_color(1);
    break;
  case 2:
    set_layer_color(2);
    break;
  case 3:
    set_layer_color(3);
    break;
  case 4:
    set_layer_color(4);
    break;
  case 5:
    set_layer_color(5);
    break;
  case 6:
    set_layer_color(6);
    break;
  case 7:
    set_layer_color(7);
    break;
  case 8:
    set_layer_color(8);
    break;
  case 9:
    set_layer_color(9);
    break;
  case 10:
    set_layer_color(10);
    break;
  case 11:
    set_layer_color(11);
    break;
  default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

#define CC(x) SEND_STRING(detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS ? SS_LGUI(x) : SS_LCTL(x))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case MACRO_0X:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_X));
    }
    break;
  case CC_P:
    if (record->event.pressed) {
      CC(SS_TAP(X_P));
    }
    break;
  case CC_Y:
    if (record->event.pressed) {
      CC(SS_TAP(X_Y));
    }
    break;
  case CC_A:
    if (record->event.pressed) {
      CC(SS_TAP(X_A));
    }
    break;
  case CC_O:
    if (record->event.pressed) {
      CC(SS_TAP(X_O));
    }
    break;
  case CC_E:
    if (record->event.pressed) {
      CC(SS_TAP(X_E));
    }
    break;
  case CC_U:
    if (record->event.pressed) {
      CC(SS_TAP(X_U));
    }
    break;
  case CC_I:
    if (record->event.pressed) {
      CC(SS_TAP(X_I));
    }
    break;
  case CC_Q:
    if (record->event.pressed) {
      CC(SS_TAP(X_Q));
    }
    break;
  case CC_X:
    if (record->event.pressed) {
      CC(SS_TAP(X_X));
    }
    break;
  case CC_J:
    if (record->event.pressed) {
      CC(SS_TAP(X_J));
    }
    break;
  case CC_K:
    if (record->event.pressed) {
      CC(SS_TAP(X_K));
    }
    break;
  case CC_F:
    if (record->event.pressed) {
      CC(SS_TAP(X_F));
    }
    break;
  case CC_G:
    if (record->event.pressed) {
      CC(SS_TAP(X_G));
    }
    break;
  case CC_C:
    if (record->event.pressed) {
      CC(SS_TAP(X_C));
    }
    break;
  case CC_R:
    if (record->event.pressed) {
      CC(SS_TAP(X_R));
    }
    break;
  case CC_L:
    if (record->event.pressed) {
      CC(SS_TAP(X_L));
    }
    break;
  case CC_D:
    if (record->event.pressed) {
      CC(SS_TAP(X_D));
    }
    break;
  case CC_H:
    if (record->event.pressed) {
      CC(SS_TAP(X_H));
    }
    break;
  case CC_T:
    if (record->event.pressed) {
      CC(SS_TAP(X_T));
    }
    break;
  case CC_N:
    if (record->event.pressed) {
      CC(SS_TAP(X_N));
    }
    break;
  case CC_S:
    if (record->event.pressed) {
      CC(SS_TAP(X_S));
    }
    break;
  case CC_MINUS:
    if (record->event.pressed) {
      CC(SS_TAP(X_MINUS));
    }
    break;
  case CC_B:
    if (record->event.pressed) {
      CC(SS_TAP(X_B));
    }
    break;
  case CC_M:
    if (record->event.pressed) {
      CC(SS_TAP(X_M));
    }
    break;
  case CC_W:
    if (record->event.pressed) {
      CC(SS_TAP(X_W));
    }
    break;
  case CC_V:
    if (record->event.pressed) {
      CC(SS_TAP(X_V));
    }
    break;
  case CC_Z:
    if (record->event.pressed) {
      CC(SS_TAP(X_Z));
    }
    break;
  case CC_SHIFT_P:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_P)));
    }
    break;
  case CC_SHIFT_Y:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Y)));
    }
    break;
  case CC_SHIFT_A:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_A)));
    }
    break;
  case CC_SHIFT_O:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_O)));
    }
    break;
  case CC_SHIFT_E:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_E)));
    }
    break;
  case CC_SHIFT_U:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_U)));
    }
    break;
  case CC_SHIFT_I:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_I)));
    }
    break;
  case CC_SHIFT_Q:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Q)));
    }
    break;
  case CC_SHIFT_X:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_X)));
    }
    break;
  case CC_SHIFT_J:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_J)));
    }
    break;
  case CC_SHIFT_K:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_K)));
    }
    break;
  case CC_SHIFT_F:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F)));
    }
    break;
  case CC_SHIFT_G:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_G)));
    }
    break;
  case CC_SHIFT_C:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_C)));
    }
    break;
  case CC_SHIFT_R:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_R)));
    }
    break;
  case CC_SHIFT_L:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_L)));
    }
    break;
  case CC_SHIFT_D:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_D)));
    }
    break;
  case CC_SHIFT_H:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_H)));
    }
    break;
  case CC_SHIFT_T:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_T)));
    }
    break;
  case CC_SHIFT_N:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_N)));
    }
    break;
  case CC_SHIFT_S:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_S)));
    }
    break;
  case CC_SHIFT_MINUS:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_MINUS)));
    }
    break;
  case CC_SHIFT_B:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_B)));
    }
    break;
  case CC_SHIFT_M:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_M)));
    }
    break;
  case CC_SHIFT_W:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_W)));
    }
    break;
  case CC_SHIFT_V:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_V)));
    }
    break;
  case CC_SHIFT_Z:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Z)));
    }
    break;
  case CC_F1:
    if (record->event.pressed) {
      CC(SS_TAP(X_F1));
    }
    break;
  case CC_F2:
    if (record->event.pressed) {
      CC(SS_TAP(X_F2));
    }
    break;
  case CC_F3:
    if (record->event.pressed) {
      CC(SS_TAP(X_F3));
    }
    break;
  case CC_F4:
    if (record->event.pressed) {
      CC(SS_TAP(X_F4));
    }
    break;
  case CC_F5:
    if (record->event.pressed) {
      CC(SS_TAP(X_F5));
    }
    break;
  case CC_F6:
    if (record->event.pressed) {
      CC(SS_TAP(X_F6));
    }
    break;
  case CC_F7:
    if (record->event.pressed) {
      CC(SS_TAP(X_F7));
    }
    break;
  case CC_F8:
    if (record->event.pressed) {
      CC(SS_TAP(X_F8));
    }
    break;
  case CC_F9:
    if (record->event.pressed) {
      CC(SS_TAP(X_F9));
    }
    break;
  case CC_F10:
    if (record->event.pressed) {
      CC(SS_TAP(X_F10));
    }
    break;
  case CC_KP7:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_7));
    }
    break;
  case CC_KP8:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_8));
    }
    break;
  case CC_KP9:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_9));
    }
    break;
  case CC_F11:
    if (record->event.pressed) {
      CC(SS_TAP(X_F11));
    }
    break;
  case CC_KP4:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_4));
    }
    break;
  case CC_KP5:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_5));
    }
    break;
  case CC_KP6:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_6));
    }
    break;
  case CC_F12:
    if (record->event.pressed) {
      CC(SS_TAP(X_F12));
    }
    break;
  case CC_KP1:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_1));
    }
    break;
  case CC_KP2:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_2));
    }
    break;
  case CC_KP3:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_3));
    }
    break;
  case CC_KP0:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_0));
    }
    break;
  case CC_KPDOT:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_DOT));
    }
    break;
  case CC_SHIFT_F1:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F1)));
    }
    break;
  case CC_SHIFT_F2:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F2)));
    }
    break;
  case CC_SHIFT_F3:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F3)));
    }
    break;
  case CC_SHIFT_F4:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F4)));
    }
    break;
  case CC_SHIFT_F5:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F5)));
    }
    break;
  case CC_SHIFT_F6:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F6)));
    }
    break;
  case CC_SHIFT_F7:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F7)));
    }
    break;
  case CC_SHIFT_F8:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F8)));
    }
    break;
  case CC_SHIFT_F9:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F9)));
    }
    break;
  case CC_SHIFT_F10:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F10)));
    }
    break;
  case CC_SHIFT_F11:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F11)));
    }
    break;
  case CC_SHIFT_F12:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F12)));
    }
    break;
  case CC_UP:
    if (record->event.pressed) {
      CC(SS_TAP(X_UP));
    }
    break;
  case CC_LEFT:
    if (record->event.pressed) {
      CC(SS_TAP(X_LEFT));
    }
    break;
  case CC_DOWN:
    if (record->event.pressed) {
      CC(SS_TAP(X_DOWN));
    }
    break;
  case CC_RIGHT:
    if (record->event.pressed) {
      CC(SS_TAP(X_RIGHT));
    }
    break;
  case CC_SHIFT_UP:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_UP)));
    }
    break;
  case CC_SHIFT_LEFT:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_LEFT)));
    }
    break;
  case CC_SHIFT_DOWN:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_DOWN)));
    }
    break;
  case CC_SHIFT_RIGHT:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_RIGHT)));
    }
    break;

  case RGB_SLD:
    if (rawhid_state.rgb_control) {
      return false;
    }
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false;
  }
  return true;
}

typedef struct {
  bool is_press_action;
  uint8_t step;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  DOUBLE_SINGLE_TAP,
  MORE_TAPS
};

static tap dance_state[1];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted)
      return DOUBLE_SINGLE_TAP;
    else if (state->pressed)
      return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    tap_code16(LSFT(KC_ESCAPE));
    tap_code16(LSFT(KC_ESCAPE));
    tap_code16(LSFT(KC_ESCAPE));
  }
  if (state->count > 3) {
    tap_code16(LSFT(KC_ESCAPE));
  }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
  dance_state[0].step = dance_step(state);
  switch (dance_state[0].step) {
  case SINGLE_TAP:
    register_code16(LSFT(KC_ESCAPE));
    break;
  case SINGLE_HOLD:
    layer_on(7);
    break;
  case DOUBLE_TAP:
    register_code16(LSFT(KC_ESCAPE));
    register_code16(LSFT(KC_ESCAPE));
    break;
  case DOUBLE_SINGLE_TAP:
    tap_code16(LSFT(KC_ESCAPE));
    register_code16(LSFT(KC_ESCAPE));
  }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
  wait_ms(10);
  switch (dance_state[0].step) {
  case SINGLE_TAP:
    unregister_code16(LSFT(KC_ESCAPE));
    break;
  case SINGLE_HOLD:
    layer_off(7);
    break;
  case DOUBLE_TAP:
    unregister_code16(LSFT(KC_ESCAPE));
    break;
  case DOUBLE_SINGLE_TAP:
    unregister_code16(LSFT(KC_ESCAPE));
    break;
  }
  dance_state[0].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished,
                                             dance_0_reset),
};
