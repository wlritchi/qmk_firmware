#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_moonlander(
        KC_DLR, KC_AMPR, KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS, KC_EQUAL, KC_EQUAL,
        KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_EXLM, KC_HASH, KC_TAB, KC_QUOTE,
        KC_COMMA, KC_DOT, KC_P, KC_Y, MO(4), KC_BSLS, KC_F, KC_G, KC_C, KC_R,
        KC_L, KC_SLASH, MT(MOD_LCTL, KC_ESCAPE), KC_A, KC_O, KC_E, KC_U, KC_I,
        MO(2), KC_AT, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINUS, MO(1), KC_SCLN,
        KC_Q, KC_X, KC_J, KC_K, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RIGHT_SHIFT,
        MOON_LED_LEVEL, KC_LEFT_GUI, KC_LEFT_ALT, MO(5), MO(4), KC_LEFT_ALT,
        MT(MOD_LCTL, KC_ESCAPE), MO(4), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_SPACE, MO(1),
        MT(MOD_LCTL, KC_ESCAPE), KC_TAB, KC_BSPC, KC_ENTER),
    [1] = LAYOUT_moonlander(
        KC_TILD, KC_0, KC_1, KC_2, KC_3, KC_4, KC_TRANSPARENT, KC_PERC, KC_5,
        KC_6, KC_7, KC_8, KC_9, KC_GRAVE, LSFT(KC_TAB), KC_DQUO, KC_LABK,
        KC_RABK, LSFT(KC_P), LSFT(KC_Y), MO(5), KC_PIPE, LSFT(KC_F), LSFT(KC_G),
        LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), KC_QUES, KC_TRANSPARENT, LSFT(KC_A),
        LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), MO(3), KC_CIRC,
        LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS,
        KC_TRANSPARENT, KC_COLN, LSFT(KC_Q), LSFT(KC_X), LSFT(KC_J), LSFT(KC_K),
        LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, MO(5), KC_TRANSPARENT, LSFT(KC_ESCAPE), MO(5),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_TAB),
        LSFT(KC_BSPC), LSFT(KC_ENTER)),
    [2] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_KP_ASTERISK, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO,
        KC_F11, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_PLUS, KC_KP_4, KC_KP_5, KC_KP_6,
        KC_NO, KC_F12, MO(3), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQUAL,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_KP_0, KC_KP_DOT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, MO(3), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT),
    [3] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_F1), LSFT(KC_F2), LSFT(KC_F3),
        LSFT(KC_F4), KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_F5), LSFT(KC_F6),
        LSFT(KC_F7), LSFT(KC_F8), LSFT(KC_F9), LSFT(KC_F10), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_KP_SLASH, KC_D, KC_E, KC_F,
        KC_NO, LSFT(KC_F11), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_KP_MINUS, KC_A, KC_B, KC_C, KC_NO, LSFT(KC_F12),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
        KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_0, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT),
    [4] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PAGE_UP, KC_UP,
        KC_PGDN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
        KC_TRANSPARENT, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,
        KC_TRANSPARENT, MO(5), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, MO(5), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT),
    [5] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_PAGE_UP),
        LSFT(KC_UP), LSFT(KC_PGDN), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, LSFT(KC_HOME),
        LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RIGHT), LSFT(KC_END),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {{126, 255, 255}, {126, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {43, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {43, 255, 255},  {43, 255, 255},
           {126, 255, 255}, {43, 255, 255},  {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255}},

    [1] = {{126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {43, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {43, 255, 255},  {43, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [2] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {43, 255, 255},  {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {43, 255, 255},  {43, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [3] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {220, 255, 255}, {43, 255, 255},  {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [4] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {43, 255, 255},  {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [5] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
        .h = pgm_read_byte(&ledmap[layer][i][0]),
        .s = pgm_read_byte(&ledmap[layer][i][1]),
        .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
      rgb_matrix_set_color(i, 0, 0, 0);
    } else {
      RGB rgb = hsv_to_rgb(hsv);
      float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
      rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
    }
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
  switch (keycode) {
  case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_X));
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
