#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
  BASE,
  SHIFT,
  NUM,
  SHIFTNUM,
  NAV,
  SHIFTNAV,
};

enum custom_keycodes {
  MACRO_0X = SAFE_RANGE,
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
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

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
        {RGB_BLACK}
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
  default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
  if ((get_mods() & MOD_MASK_CTRL) && (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS)) {
    if (
      (keycode < QK_MOMENTARY || keycode > QK_MOMENTARY_MAX)
      && (keycode < QK_MOD_TAP || keycode > QK_MOD_TAP_MAX)
      && (keycode < QK_LAYER_TAP || keycode > QK_LAYER_TAP_MAX)
    ) {
      unset_mods |= MOD_MASK_CTRL;
      force_mods |= MOD_MASK_GUI;
    }
  }
  switch (keycode) {
  case KC_GRAVE:
  case KC_BSLS:
    unset_mods |= MOD_MASK_SHIFT;
  }
  if (unset_mods || force_mods) {
    uint8_t real_mods = get_mods();
    set_mods((real_mods & ~unset_mods) | force_mods);
    register_code(keycode);
    unregister_code(keycode);
    set_mods(real_mods);
    return false;
  }
  return true;
}
