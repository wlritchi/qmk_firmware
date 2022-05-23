#include QMK_KEYBOARD_H
#include "keymap_belgian.h"
#include "keymap_bepo.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_contributions.h"
#include "keymap_croatian.h"
#include "keymap_czech.h"
#include "keymap_danish.h"
#include "keymap_estonian.h"
#include "keymap_french.h"
#include "keymap_german.h"
#include "keymap_german_ch.h"
#include "keymap_hungarian.h"
#include "keymap_italian.h"
#include "keymap_jp.h"
#include "keymap_korean.h"
#include "keymap_lithuanian_azerty.h"
#include "keymap_nordic.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#include "keymap_romanian.h"
#include "keymap_russian.h"
#include "keymap_slovak.h"
#include "keymap_slovenian.h"
#include "keymap_spanish.h"
#include "keymap_swedish.h"
#include "keymap_turkish_q.h"
#include "keymap_uk.h"
#include "keymap_us_international.h"
#include "version.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_moonlander(
        KC_ESCAPE, KC_AMPR, KC_LBRACKET, KC_LCBR, KC_LPRN, KC_PLUS,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRACKET,
        KC_EXLM, KC_HASH, KC_TAB, KC_QUOTE, KC_COMMA, KC_DOT, KC_P, KC_Y, MO(4),
        KC_TRANSPARENT, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLASH, KC_LCTRL, KC_A,
        KC_O, KC_E, KC_U, KC_I, MO(2), KC_TRANSPARENT, KC_D, KC_H, KC_T, KC_N,
        KC_S, KC_EQUAL, MO(1), KC_SCOLON, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M,
        KC_W, KC_V, KC_Z, KC_RSHIFT, MOON_LED_LEVEL, WEBUSB_PAIR,
        LALT(KC_LSHIFT), KC_TRANSPARENT, MO(4), KC_LALT,
        MT(MOD_LCTL, KC_ESCAPE), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_SPACE, MO(1), KC_LCTRL, KC_TAB,
        KC_BSPACE, KC_ENTER),
    [1] = LAYOUT_moonlander(
        LSFT(KC_ESCAPE), KC_0, KC_1, KC_2, KC_3, KC_4, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_5, KC_6, KC_7, KC_8, KC_9, KC_GRAVE, LSFT(KC_TAB),
        KC_DQUO, KC_LABK, KC_RABK, LSFT(KC_P), LSFT(KC_Y), MO(5),
        KC_TRANSPARENT, LSFT(KC_F), LSFT(KC_G), LSFT(KC_C), LSFT(KC_R),
        LSFT(KC_L), KC_QUES, KC_TRANSPARENT, LSFT(KC_A), LSFT(KC_O), LSFT(KC_E),
        LSFT(KC_U), LSFT(KC_I), MO(3), KC_TRANSPARENT, LSFT(KC_D), LSFT(KC_H),
        LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), ST_MACRO_0, KC_TRANSPARENT, KC_COLN,
        LSFT(KC_Q), LSFT(KC_J), LSFT(KC_K), LSFT(KC_X), LSFT(KC_B), LSFT(KC_M),
        LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(5), KC_TRANSPARENT,
        LSFT(KC_ESCAPE), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, LSFT(KC_TAB), LSFT(KC_BSPACE), LSFT(KC_ENTER)),
    [2] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_KP_ASTERISK, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO,
        KC_F11, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_UNDS, KC_KP_4, KC_KP_5, KC_KP_6,
        KC_NO, KC_F12, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_KP_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_0, KC_KP_DOT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(3), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [3] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_F1), LSFT(KC_F2), LSFT(KC_F3),
        LSFT(KC_F4), KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_F5), LSFT(KC_F6),
        LSFT(KC_F7), LSFT(KC_F8), LSFT(KC_F9), LSFT(KC_F10), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_KP_SLASH, KC_D, KC_E, KC_F,
        KC_NO, LSFT(KC_F11), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_A, KC_B, KC_C, KC_NO, LSFT(KC_F12),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_MINUS, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_1,
        KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT),
    [4] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PGUP, KC_UP,
        KC_PGDOWN, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT, KC_DOWN,
        KC_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(5),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [5] = LAYOUT_moonlander(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_PGUP),
        LSFT(KC_UP), LSFT(KC_PGDOWN), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT,
        LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RIGHT), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) { rgb_matrix_enable(); }

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = {{126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {43, 255, 255},  {43, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [1] = {{126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
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
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [2] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {220, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {220, 255, 255}, {220, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255}},

    [3] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {43, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {43, 255, 255},  {43, 255, 255},  {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {43, 255, 255},  {43, 255, 255},  {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [4] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [5] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
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

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) {
    return;
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
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_1)) SS_DELAY(100) SS_TAP(X_EQUAL));
    }
    break;
  case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_X));
    }
    break;
  case RGB_SLD:
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false;
  }
  return true;
}
