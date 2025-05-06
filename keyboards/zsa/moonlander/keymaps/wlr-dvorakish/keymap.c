#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
  ST_MACRO_6,
  ST_MACRO_7,
  ST_MACRO_8,
  ST_MACRO_9,
  ST_MACRO_10,
  ST_MACRO_11,
  ST_MACRO_12,
  ST_MACRO_13,
  ST_MACRO_14,
  ST_MACRO_15,
  ST_MACRO_16,
  ST_MACRO_17,
  ST_MACRO_18,
  ST_MACRO_19,
  ST_MACRO_20,
  ST_MACRO_21,
  ST_MACRO_22,
  ST_MACRO_23,
  ST_MACRO_24,
  ST_MACRO_25,
  ST_MACRO_26,
  ST_MACRO_27,
  ST_MACRO_28,
  ST_MACRO_29,
  ST_MACRO_30,
  ST_MACRO_31,
  ST_MACRO_32,
  ST_MACRO_33,
  ST_MACRO_34,
  ST_MACRO_35,
  ST_MACRO_36,
  ST_MACRO_37,
  ST_MACRO_38,
  ST_MACRO_39,
  ST_MACRO_40,
  ST_MACRO_41,
  ST_MACRO_42,
  ST_MACRO_43,
  ST_MACRO_44,
  ST_MACRO_45,
  ST_MACRO_46,
  ST_MACRO_47,
  ST_MACRO_48,
  ST_MACRO_49,
  ST_MACRO_50,
  ST_MACRO_51,
  ST_MACRO_52,
  ST_MACRO_53,
  ST_MACRO_54,
  ST_MACRO_55,
  ST_MACRO_56,
  ST_MACRO_57,
  ST_MACRO_58,
  ST_MACRO_59,
  ST_MACRO_60,
  ST_MACRO_61,
  ST_MACRO_62,
  ST_MACRO_63,
  ST_MACRO_64,
  ST_MACRO_65,
  ST_MACRO_66,
  ST_MACRO_67,
  ST_MACRO_68,
  ST_MACRO_69,
  ST_MACRO_70,
  ST_MACRO_71,
  ST_MACRO_72,
  ST_MACRO_73,
  ST_MACRO_74,
  ST_MACRO_75,
  ST_MACRO_76,
  ST_MACRO_77,
  ST_MACRO_78,
  ST_MACRO_79,
  ST_MACRO_80,
  ST_MACRO_81,
  ST_MACRO_82,
  ST_MACRO_83,
  ST_MACRO_84,
  ST_MACRO_85,
  ST_MACRO_86,
  ST_MACRO_87,
  ST_MACRO_88,
  ST_MACRO_89,
  ST_MACRO_90,
  ST_MACRO_91,
  ST_MACRO_92,
  ST_MACRO_93,
  ST_MACRO_94,
};

enum tap_dance_codes {
  DANCE_0,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_moonlander(
        KC_DLR, KC_AMPR, KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS, KC_EQUAL, KC_EQUAL,
        KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_EXLM, KC_HASH, KC_TAB, KC_QUOTE,
        KC_COMMA, KC_DOT, KC_P, KC_Y, MO(4), KC_PIPE, KC_F, KC_G, KC_C, KC_R,
        KC_L, KC_SLASH, LT(6, KC_ESCAPE), KC_A, KC_O, KC_E, KC_U, KC_I, MO(2),
        KC_AT, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINUS, LM(1, MOD_LSFT), KC_SCLN,
        KC_Q, KC_X, KC_J, KC_K, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RIGHT_SHIFT,
        MOON_LED_LEVEL, KC_LEFT_GUI, KC_LEFT_ALT, MO(5), MO(4), KC_TRANSPARENT,
        KC_TRANSPARENT, MO(4), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_SPACE, LM(1, MOD_LSFT), KC_LEFT_ALT, KC_TAB, KC_BSPC,
        KC_ENTER),
    [1] = LAYOUT_moonlander(
        KC_TILD, KC_0, KC_1, KC_2, KC_3, KC_4, KC_NO, KC_PERC, KC_5, KC_6, KC_7,
        KC_8, KC_9, KC_GRAVE, LSFT(KC_TAB), KC_DQUO, KC_LABK, KC_RABK,
        LSFT(KC_P), LSFT(KC_Y), MO(5), KC_BSLS, LSFT(KC_F), LSFT(KC_G),
        LSFT(KC_C), LSFT(KC_R), LSFT(KC_L), KC_QUES, TD(DANCE_0), LSFT(KC_A),
        LSFT(KC_O), LSFT(KC_E), LSFT(KC_U), LSFT(KC_I), MO(3), KC_CIRC,
        LSFT(KC_D), LSFT(KC_H), LSFT(KC_T), LSFT(KC_N), LSFT(KC_S), KC_UNDS,
        KC_TRANSPARENT, KC_COLN, LSFT(KC_Q), LSFT(KC_X), LSFT(KC_J), LSFT(KC_K),
        LSFT(KC_B), LSFT(KC_M), LSFT(KC_W), LSFT(KC_V), LSFT(KC_Z),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, MO(5), KC_TRANSPARENT, KC_TRANSPARENT, MO(5),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        LSFT(KC_SPACE), KC_TRANSPARENT, KC_TRANSPARENT, LSFT(KC_TAB),
        LSFT(KC_BSPC), LSFT(KC_ENTER)),
    [2] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_F5, KC_F6,
        KC_F7, KC_F8, KC_F9, KC_F10, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_KP_ASTERISK, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO,
        KC_F11, LT(8, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_KP_PLUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_NO,
        KC_F12, MO(3), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQUAL, KC_KP_1,
        KC_KP_2, KC_KP_3, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_0,
        KC_KP_DOT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, MO(3), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT),
    [3] = LAYOUT_moonlander(
        KC_NO, KC_NO, LSFT(KC_F1), LSFT(KC_F2), LSFT(KC_F3), LSFT(KC_F4),
        KC_NO, KC_NO, LSFT(KC_F5), LSFT(KC_F6), LSFT(KC_F7), LSFT(KC_F8),
        LSFT(KC_F9), LSFT(KC_F10), KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_KP_SLASH, KC_D, KC_E, KC_F, KC_NO, LSFT(KC_F11),
        LT(9, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_KP_MINUS, KC_A, KC_B, KC_C, KC_NO, LSFT(KC_F12),
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT,
        ST_MACRO_0, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT),
    [4] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_PAGE_UP, KC_UP, KC_PGDN, KC_NO, KC_NO,
        LT(10, KC_ESCAPE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, KC_NO, MO(5), KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, MO(5), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT),
    [5] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_TRANSPARENT, KC_NO, KC_NO, LSFT(KC_PAGE_UP), LSFT(KC_UP),
        LSFT(KC_PGDN), KC_NO, KC_NO, LT(11, KC_ESCAPE), KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_HOME), LSFT(KC_LEFT), LSFT(KC_DOWN),
        LSFT(KC_RIGHT), LSFT(KC_END), KC_NO, KC_TRANSPARENT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT),
    [6] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ST_MACRO_1,
        ST_MACRO_2, MO(10), KC_NO, ST_MACRO_12, ST_MACRO_13, ST_MACRO_14,
        ST_MACRO_15, ST_MACRO_16, KC_NO, KC_TRANSPARENT, ST_MACRO_3, ST_MACRO_4,
        ST_MACRO_5, ST_MACRO_6, ST_MACRO_7, MO(8), KC_NO, ST_MACRO_17,
        ST_MACRO_18, LGUI(KC_T), LGUI(KC_N), ST_MACRO_19, ST_MACRO_20, MO(7),
        KC_NO, ST_MACRO_8, ST_MACRO_9, ST_MACRO_10, ST_MACRO_11, ST_MACRO_21,
        ST_MACRO_22, LGUI(KC_W), ST_MACRO_23, ST_MACRO_24, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(11), MO(10),
        KC_TRANSPARENT, KC_TRANSPARENT, MO(10), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(7), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [7] = LAYOUT_moonlander(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ST_MACRO_25,
        ST_MACRO_26, MO(11), KC_NO, ST_MACRO_36, ST_MACRO_37, ST_MACRO_38,
        ST_MACRO_39, ST_MACRO_40, KC_NO, KC_TRANSPARENT, ST_MACRO_27,
        ST_MACRO_28, ST_MACRO_29, ST_MACRO_30, ST_MACRO_31, MO(9), KC_NO,
        ST_MACRO_41, ST_MACRO_42, ST_MACRO_43, ST_MACRO_44, ST_MACRO_45,
        ST_MACRO_46, KC_TRANSPARENT, KC_NO, ST_MACRO_32, ST_MACRO_33,
        ST_MACRO_34, ST_MACRO_35, ST_MACRO_47, ST_MACRO_48, ST_MACRO_49,
        ST_MACRO_50, ST_MACRO_51, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, MO(11), MO(11), KC_TRANSPARENT,
        KC_TRANSPARENT, MO(11), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [8] = LAYOUT_moonlander(
        KC_NO, KC_NO, ST_MACRO_52, ST_MACRO_53, ST_MACRO_54, ST_MACRO_55,
        KC_NO, KC_NO, ST_MACRO_56, ST_MACRO_57, ST_MACRO_58, ST_MACRO_59,
        ST_MACRO_60, ST_MACRO_61, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, ST_MACRO_62, ST_MACRO_63, ST_MACRO_64,
        KC_NO, ST_MACRO_65, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_NO, ST_MACRO_66, ST_MACRO_67, ST_MACRO_68,
        KC_NO, ST_MACRO_69, MO(9), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        ST_MACRO_70, ST_MACRO_71, ST_MACRO_72, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_73, ST_MACRO_74,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(9),
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [9] = LAYOUT_moonlander(
        KC_NO, KC_NO, ST_MACRO_75, ST_MACRO_76, ST_MACRO_77, ST_MACRO_78,
        KC_NO, KC_NO, ST_MACRO_79, ST_MACRO_80, ST_MACRO_81, ST_MACRO_82,
        ST_MACRO_83, ST_MACRO_84, KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ST_MACRO_85,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, ST_MACRO_86, KC_TRANSPARENT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,
        KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [10] = LAYOUT_moonlander(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_TRANSPARENT, KC_NO, KC_NO, LCTL(KC_PAGE_UP),
                             ST_MACRO_87, LCTL(KC_PGDN), KC_NO, KC_NO,
                             KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, LCTL(KC_HOME), ST_MACRO_88,
                             ST_MACRO_89, ST_MACRO_90, LCTL(KC_END), KC_NO,
                             MO(11), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                             KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
                             KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                             MO(11), KC_TRANSPARENT, KC_TRANSPARENT,
                             KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                             KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                             KC_TRANSPARENT, MO(11), KC_TRANSPARENT,
                             KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [11] =
        LAYOUT_moonlander(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_TRANSPARENT, KC_NO, KC_NO, LCTL(LSFT(KC_PAGE_UP)),
                          ST_MACRO_91, LCTL(LSFT(KC_PGDN)), KC_NO, KC_NO,
                          KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_NO, KC_NO, LCTL(LSFT(KC_HOME)), ST_MACRO_92,
                          ST_MACRO_93, ST_MACRO_94, LCTL(LSFT(KC_END)), KC_NO,
                          KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
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
           {126, 255, 255}, {43, 255, 255},  {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [1] = {{126, 255, 255}, {126, 255, 255}, {220, 255, 255}, {0, 0, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {43, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {43, 255, 255},  {43, 255, 255},
           {126, 255, 255}, {0, 0, 255},     {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [2] = {{0, 0, 0},       {126, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
           {126, 255, 255}, {43, 255, 255},  {0, 0, 0},       {126, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {43, 255, 255},  {43, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [3] = {{0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
           {126, 255, 255}, {0, 0, 255},     {0, 0, 0},       {126, 255, 255},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {126, 255, 255}, {220, 255, 255}, {43, 255, 255},  {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [4] = {{0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 0},
           {126, 255, 255}, {43, 255, 255},  {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [5] = {{0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 0},
           {126, 255, 255}, {0, 0, 255},     {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
           {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0}},

    [6] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {43, 255, 255},  {43, 255, 255},
           {0, 0, 0},       {43, 255, 255},  {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [7] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {43, 255, 255},  {43, 255, 255},
           {0, 0, 0},       {0, 0, 255},     {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {43, 255, 255},  {0, 0, 0},       {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [8] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {43, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
           {0, 0, 0},       {43, 255, 255},  {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {0, 0, 0},       {220, 255, 255},
           {126, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {220, 255, 255}, {126, 255, 255}, {126, 255, 255}, {126, 255, 255},
           {126, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [9] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
           {0, 0, 0},       {0, 0, 255},     {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {220, 255, 255}, {220, 255, 255}, {43, 255, 255},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {220, 255, 255}, {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
           {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [10] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 0},
            {0, 0, 0},       {43, 255, 255},  {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
            {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

    [11] = {{0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 255},     {0, 0, 0},
            {0, 0, 0},       {0, 0, 255},     {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {220, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {220, 255, 255}, {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {220, 255, 255}, {220, 255, 255}, {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {43, 255, 255},  {220, 255, 255}, {0, 0, 0},
            {0, 0, 255},     {0, 0, 0},       {0, 0, 0},       {43, 255, 255},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0},
            {0, 0, 0},       {0, 0, 0},       {0, 0, 0},       {0, 0, 0}},

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

#define CC(x) SEND_STRING(detected_host_os() == OS_MACOS ? SS_LGUI(x) : SS_LCTL(x))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_X));
    }
    break;
  case ST_MACRO_1:
    if (record->event.pressed) {
      CC(SS_TAP(X_P));
    }
    break;
  case ST_MACRO_2:
    if (record->event.pressed) {
      CC(SS_TAP(X_Y));
    }
    break;
  case ST_MACRO_3:
    if (record->event.pressed) {
      CC(SS_TAP(X_A));
    }
    break;
  case ST_MACRO_4:
    if (record->event.pressed) {
      CC(SS_TAP(X_O));
    }
    break;
  case ST_MACRO_5:
    if (record->event.pressed) {
      CC(SS_TAP(X_E));
    }
    break;
  case ST_MACRO_6:
    if (record->event.pressed) {
      CC(SS_TAP(X_U));
    }
    break;
  case ST_MACRO_7:
    if (record->event.pressed) {
      CC(SS_TAP(X_I));
    }
    break;
  case ST_MACRO_8:
    if (record->event.pressed) {
      CC(SS_TAP(X_Q));
    }
    break;
  case ST_MACRO_9:
    if (record->event.pressed) {
      CC(SS_TAP(X_X));
    }
    break;
  case ST_MACRO_10:
    if (record->event.pressed) {
      CC(SS_TAP(X_J));
    }
    break;
  case ST_MACRO_11:
    if (record->event.pressed) {
      CC(SS_TAP(X_K));
    }
    break;
  case ST_MACRO_12:
    if (record->event.pressed) {
      CC(SS_TAP(X_F));
    }
    break;
  case ST_MACRO_13:
    if (record->event.pressed) {
      CC(SS_TAP(X_G));
    }
    break;
  case ST_MACRO_14:
    if (record->event.pressed) {
      CC(SS_TAP(X_C));
    }
    break;
  case ST_MACRO_15:
    if (record->event.pressed) {
      CC(SS_TAP(X_R));
    }
    break;
  case ST_MACRO_16:
    if (record->event.pressed) {
      CC(SS_TAP(X_L));
    }
    break;
  case ST_MACRO_17:
    if (record->event.pressed) {
      CC(SS_TAP(X_D));
    }
    break;
  case ST_MACRO_18:
    if (record->event.pressed) {
      CC(SS_TAP(X_H));
    }
    break;
  case ST_MACRO_19:
    if (record->event.pressed) {
      CC(SS_TAP(X_S));
    }
    break;
  case ST_MACRO_20:
    if (record->event.pressed) {
      CC(SS_TAP(X_MINUS));
    }
    break;
  case ST_MACRO_21:
    if (record->event.pressed) {
      CC(SS_TAP(X_B));
    }
    break;
  case ST_MACRO_22:
    if (record->event.pressed) {
      CC(SS_TAP(X_M));
    }
    break;
  case ST_MACRO_23:
    if (record->event.pressed) {
      CC(SS_TAP(X_V));
    }
    break;
  case ST_MACRO_24:
    if (record->event.pressed) {
      CC(SS_TAP(X_Z));
    }
    break;
  case ST_MACRO_25:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_P)));
    }
    break;
  case ST_MACRO_26:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Y)));
    }
    break;
  case ST_MACRO_27:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_A)));
    }
    break;
  case ST_MACRO_28:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_O)));
    }
    break;
  case ST_MACRO_29:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_E)));
    }
    break;
  case ST_MACRO_30:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_U)));
    }
    break;
  case ST_MACRO_31:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_I)));
    }
    break;
  case ST_MACRO_32:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Q)));
    }
    break;
  case ST_MACRO_33:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_X)));
    }
    break;
  case ST_MACRO_34:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_J)));
    }
    break;
  case ST_MACRO_35:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_K)));
    }
    break;
  case ST_MACRO_36:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F)));
    }
    break;
  case ST_MACRO_37:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_G)));
    }
    break;
  case ST_MACRO_38:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_C)));
    }
    break;
  case ST_MACRO_39:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_R)));
    }
    break;
  case ST_MACRO_40:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_L)));
    }
    break;
  case ST_MACRO_41:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_D)));
    }
    break;
  case ST_MACRO_42:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_H)));
    }
    break;
  case ST_MACRO_43:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_T)));
    }
    break;
  case ST_MACRO_44:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_N)));
    }
    break;
  case ST_MACRO_45:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_S)));
    }
    break;
  case ST_MACRO_46:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_MINUS)));
    }
    break;
  case ST_MACRO_47:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_B)));
    }
    break;
  case ST_MACRO_48:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_M)));
    }
    break;
  case ST_MACRO_49:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_W)));
    }
    break;
  case ST_MACRO_50:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_V)));
    }
    break;
  case ST_MACRO_51:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_Z)));
    }
    break;
  case ST_MACRO_52:
    if (record->event.pressed) {
      CC(SS_TAP(X_F1));
    }
    break;
  case ST_MACRO_53:
    if (record->event.pressed) {
      CC(SS_TAP(X_F2));
    }
    break;
  case ST_MACRO_54:
    if (record->event.pressed) {
      CC(SS_TAP(X_F3));
    }
    break;
  case ST_MACRO_55:
    if (record->event.pressed) {
      CC(SS_TAP(X_F4));
    }
    break;
  case ST_MACRO_56:
    if (record->event.pressed) {
      CC(SS_TAP(X_F5));
    }
    break;
  case ST_MACRO_57:
    if (record->event.pressed) {
      CC(SS_TAP(X_F6));
    }
    break;
  case ST_MACRO_58:
    if (record->event.pressed) {
      CC(SS_TAP(X_F7));
    }
    break;
  case ST_MACRO_59:
    if (record->event.pressed) {
      CC(SS_TAP(X_F8));
    }
    break;
  case ST_MACRO_60:
    if (record->event.pressed) {
      CC(SS_TAP(X_F9));
    }
    break;
  case ST_MACRO_61:
    if (record->event.pressed) {
      CC(SS_TAP(X_F10));
    }
    break;
  case ST_MACRO_62:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_7));
    }
    break;
  case ST_MACRO_63:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_8));
    }
    break;
  case ST_MACRO_64:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_9));
    }
    break;
  case ST_MACRO_65:
    if (record->event.pressed) {
      CC(SS_TAP(X_F11));
    }
    break;
  case ST_MACRO_66:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_4));
    }
    break;
  case ST_MACRO_67:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_5));
    }
    break;
  case ST_MACRO_68:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_6));
    }
    break;
  case ST_MACRO_69:
    if (record->event.pressed) {
      CC(SS_TAP(X_F12));
    }
    break;
  case ST_MACRO_70:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_1));
    }
    break;
  case ST_MACRO_71:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_2));
    }
    break;
  case ST_MACRO_72:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_3));
    }
    break;
  case ST_MACRO_73:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_0));
    }
    break;
  case ST_MACRO_74:
    if (record->event.pressed) {
      CC(SS_TAP(X_KP_DOT));
    }
    break;
  case ST_MACRO_75:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F1)));
    }
    break;
  case ST_MACRO_76:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F2)));
    }
    break;
  case ST_MACRO_77:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F3)));
    }
    break;
  case ST_MACRO_78:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F4)));
    }
    break;
  case ST_MACRO_79:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F5)));
    }
    break;
  case ST_MACRO_80:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F6)));
    }
    break;
  case ST_MACRO_81:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F7)));
    }
    break;
  case ST_MACRO_82:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F8)));
    }
    break;
  case ST_MACRO_83:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F9)));
    }
    break;
  case ST_MACRO_84:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F10)));
    }
    break;
  case ST_MACRO_85:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F11)));
    }
    break;
  case ST_MACRO_86:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_F12)));
    }
    break;
  case ST_MACRO_87:
    if (record->event.pressed) {
      CC(SS_TAP(X_UP));
    }
    break;
  case ST_MACRO_88:
    if (record->event.pressed) {
      CC(SS_TAP(X_LEFT));
    }
    break;
  case ST_MACRO_89:
    if (record->event.pressed) {
      CC(SS_TAP(X_DOWN));
    }
    break;
  case ST_MACRO_90:
    if (record->event.pressed) {
      CC(SS_TAP(X_RIGHT));
    }
    break;
  case ST_MACRO_91:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_UP)));
    }
    break;
  case ST_MACRO_92:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_LEFT)));
    }
    break;
  case ST_MACRO_93:
    if (record->event.pressed) {
      CC(SS_LSFT(SS_TAP(X_DOWN)));
    }
    break;
  case ST_MACRO_94:
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
