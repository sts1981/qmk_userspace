// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LMIRROR,
    _RMIRROR,
    _MOUSE,
    _NAV,
    _SWAY,
    _ADJUST,
    _SCROLL
};

enum tap_dance_codes {
    TD_EQLS,
    TD_3_LEFT,
    TD_5_RIGHT,
    TD_6_DOWN,
    TD_8_UP,
    TD_SWAYW_1,
    TD_SWAYW_2,
    TD_SWAYW_3,
    TD_SWAYW_4,
    TD_SWAYW_5,
    TD_SCROLL_PGDN
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define MAIN     TO(_QWERTY)
//#define NAV      MO(_NAV)
#define ADJUST   TO(_ADJUST)

//#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
//#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
//#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
//#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define OSM_LALT OSM(MOD_LALT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_RSFT OSM(MOD_RSFT)

#define MN_Z MT(MOD_LSFT, KC_Z)
#define MN_SLSH MT(MOD_RSFT, KC_SLASH)
#define MN_SPC LT(_NAV, KC_SPACE)
#define MN_ENT LT(_NAV, KC_ENT)
#define MN_ESC LGUI_T(KC_ESC) // TODO: replace these with Sway layer?
#define MN_QUOT RGUI_T(KC_QUOTE)
#define MN_1 MT(MOD_LCTL, KC_1)
#define MN_2 MT(MOD_LALT, KC_2)
#define MN_3 TD(TD_3_LEFT)
#define MN_4 LT(_SWAY, KC_4)
#define MN_5 TD(TD_5_RIGHT)
#define MN_6 TD(TD_6_DOWN)
#define MN_7 LT(_SWAY, KC_7)
#define MN_8 TD(TD_8_UP)
#define MN_9 MT(MOD_RALT, KC_9)
#define MN_0 MT(MOD_RCTL, KC_0)
#define OS_LMIR OSL(_LMIRROR)
#define OS_RMIR OSL(_RMIRROR)

#define WIN_NXT LALT(KC_TAB)
#define WIN_SEL LALT(LCTL(KC_TAB))

#define SYM_EQL TD(TD_EQLS)

#define MSE_OFF TG(_MOUSE)

#define SWAYW_1 TD(TD_SWAYW_1)
#define SWAYW_2 TD(TD_SWAYW_2)
#define SWAYW_3 TD(TD_SWAYW_3)
#define SWAYW_4 TD(TD_SWAYW_4)
#define SWAYW_5 TD(TD_SWAYW_5)

#define SCL_PGD TD(TD_SCROLL_PGDN)
#define SCL_SSPC LSFT(KC_SPC)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Meta/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : | Meta/' |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |LSft/Z|   X  |   C  |   V  |   B  | 3/←  | 5/→  |  |  6/↑ |  8/↓ |   N  |   M  | ,  < | . >  |RSft//| RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  1/  |  2/  |Miror/| Enter|  4/  |  |  7/  |Space |Miror/|  9/ |  0/  |
 *                        |LCtrl | LAlt | Sym  |      | Sway |  | Sway |      | Num  | RAlt| RCtrl|
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_5_hlc(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y  ,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
      MN_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H  ,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, MN_QUOT,
     OSM_LSFT, MN_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , MN_3   , MN_5   ,     MN_6   , MN_8  , KC_N  ,   KC_M ,KC_COMM, KC_DOT ,MN_SLSH,OSM_RSFT,
                                 MN_1  ,   MN_2 , OS_LMIR, MN_ENT , MN_4   ,     MN_7   , MN_SPC,OS_RMIR,   MN_9 ,  MN_0 ,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * LMirror: Symbols on RH, mirror on LH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Bksp  |  P   |   O  |  I   |   U  |  Y   |                              |  &   |  #   |  [   |  ]   |  @   |   \    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Meta/' |  ;   |  L   |  K   |  J   |  H   |                              |  !   |  =/^ |  (   |  )   |  $   |   `    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | RShift |RSft//|  .   |  ,   |  M   |  N   |  8/↓ |  6/↑ |  |      | MAIN |  |   |  _   |  {   |  }   |  ~   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  0/  |  9/  |      |Space |  7/  |  |      |      |      |      |      |
 *                        | RCtrl| RAlt |      |      | Sway |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_LMIRROR] = LAYOUT_split_3x6_5_hlc(
      KC_BSPC,   KC_P ,   KC_O ,   KC_I ,   KC_U ,   KC_Y ,                                         KC_AMPR, KC_HASH, KC_LBRC, KC_RBRC,  KC_AT , KC_BSLS,
      MN_QUOT, KC_SCLN,   KC_L ,   KC_K ,   KC_J ,   KC_H ,                                         KC_EXLM, SYM_EQL, KC_LPRN, KC_RPRN, KC_DLR , KC_GRAVE,
     OSM_RSFT, MN_SLSH,  KC_DOT, KC_COMM,   KC_M ,   KC_N ,   MN_8 ,   MN_6 ,     _______,   MAIN , KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_TILD, _______,
                                   MN_0 ,   MN_9 , _______,  MN_SPC,   MN_7 ,     _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                           _______, _______, _______, _______, _______
    ),

/*
 * RMirror: Numbers on LH, mirror on RH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Bksp  |  7   |  8   |  9   |  +   |  *   |                              |  T   |  R   |  E   |  W   |  Q   |  Tab   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    %   |  4   |  5   |  6   |  0   |  .   |                              |  G   |  F   |  D   |  S   |  A   |Meta/Esc|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  -   |  /   | MAIN |      |  |  5/→ |  3/← |  B   |  V   |  C   |  X   |LSft/Z| LShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |  4/  |Enter |      |  2/  |  1/  |
 *                        |      |      |      |      |      |  | Sway |      |      | LAlt | LCtrl|
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_RMIRROR] = LAYOUT_split_3x6_5_hlc(
      KC_BSPC,   KC_7 ,   KC_8 ,   KC_9 , KC_PLUS, KC_ASTR,                                           KC_T ,   KC_R ,   KC_E ,   KC_W ,   KC_Q ,  KC_TAB,
      KC_PERC,   KC_4 ,   KC_5 ,   KC_6 ,   KC_0 , KC_DOT ,                                           KC_G ,   KC_F ,   KC_D ,   KC_S ,   KC_A ,  MN_ESC,
      _______,   KC_1 ,   KC_2 ,   KC_3 , KC_MINS, KC_SLSH,   MAIN , _______,       MN_5 ,   MN_3 ,   KC_B ,   KC_V ,   KC_C ,   KC_X ,   MN_Z ,OSM_LSFT,
                                 _______, _______, _______, _______, _______,       MN_4 ,  MN_ENT, _______,   MN_2 ,   MN_1 ,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

 /*
  * Mouse layer: Mouse movement and function keys
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |  F11   |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  |  F10 |  F12   |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |LYR OFF |      |MouseR|MouseU|MouseD|MouseL|                              |MouseL|MouseD|MouseU|MouseR|      |LYR OFF |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |  MAIN  |Click |      |WheelU|WheelD|      |      |      |  |      |      |      |WheelD|WheelU|      |Click | MAIN   |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |RClick|Click |      |  |      | Click|RClick|      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  * ,-----------------------------------.                                              ,-----------------------------------.
  * |      |      |       |      |      |                                              |      |      |       |      |      |
  * `-----------------------------------'                                              `-----------------------------------'
  */
     [_MOUSE] = LAYOUT_split_3x6_5_hlc(
        KC_F11,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,                                            KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10,  KC_F12,
       MSE_OFF, _______, MS_RGHT,  MS_UP , MS_DOWN, MS_LEFT,                                           MS_LEFT, MS_DOWN,  MS_UP , MS_RGHT, _______, MSE_OFF,
         MAIN , MS_BTN1, _______, MS_WHLU, MS_WHLD, _______, _______, _______,       _______, _______, _______, MS_WHLD, MS_WHLU, _______, MS_BTN1,   MAIN ,
                                  _______, _______, MS_BTN2, MS_BTN1, _______,       _______, MS_BTN1, MS_BTN2, _______, _______,

       _______, _______, _______, _______, _______,                                                             _______, _______, _______, _______, _______
     ),

/*
 * Nav Layer: Navigation, other frequently used keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | BkSpc  | Del  | LCtrl| LAlt | BkSpc|PrtSc |                              |CpsWrd|CpsWrd| RAlt | RCtrl| Del  |  BkSpc |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | MAIN   |AlCtTb|   →  |  ↑   |   ↓  |  ←   |                              |   ←  |  ↓   |   ↑  |   →  |AlCtTb|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |AltTab| End  | PgUp | PgDn | Home |      |      |  |      |      | Home | PgDn | PgUp | End  |AltTab|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
      KC_BSPC, KC_DEL ,OSM_LCTL,OSM_LALT, KC_BSPC, KC_PSCR,                                     CW_TOGG, CW_TOGG,OSM_RALT,OSM_RCTL, KC_DEL , KC_BSPC,
        MAIN , WIN_SEL, KC_RGHT, KC_UP  , KC_DOWN, KC_LEFT,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, WIN_SEL, _______,
      _______, WIN_NXT,  KC_END, KC_PGUP, KC_PGDN, KC_HOME, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, WIN_NXT, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

 /*
  * Sway: window switching/navigation, should be reached with Meta modifier on
  *
  * ,-------------------------------------------.                              ,-------------------------------------------.
  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  * |  MAIN  |      |   L  |  K   |  J   |  H   |                              |  H   |  J   |  K   |  L   |      |        |
  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  * |        | 1/0  | 2/9  | 3/8  | 4/7  | 5/6  |      |      |  |      |      | 5/6  | 4/7  | 3/8  | 2/9  | 1/0  |        |
  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        |      |      |      |      |      |  |      |      |      |      |      |
  *                        `----------------------------------'  `----------------------------------'
  * ,-----------------------------------.                                              ,-----------------------------------.
  * |      |      |       |      |      |                                              |      |      |       |      |      |
  * `-----------------------------------'                                              `-----------------------------------'
  */
     [_SWAY] = LAYOUT_split_3x6_5_hlc(
       _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
         MAIN , _______, G(KC_L), G(KC_K), G(KC_J), G(KC_H),                                             G(KC_H), G(KC_J), G(KC_K), G(KC_L), _______, _______,
       _______, SWAYW_1, SWAYW_2, SWAYW_3, SWAYW_4, SWAYW_5, _______, _______,         _______, _______, SWAYW_5, SWAYW_4, SWAYW_3, SWAYW_2, SWAYW_1, _______,
                                  _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,

       _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______
     ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|TermUp|      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | MAIN   |      |      |      |TermPt|      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |TermDn|      |      | Boot |  | Boot |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, QWERTY ,  DT_UP , _______,                                             _______, _______, _______, _______, _______, _______,
        MAIN , _______, _______, _______, DT_PRNT, _______,                                             RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
      _______, _______, _______, _______, DT_DOWN, _______, _______, QK_BOOT,         QK_BOOT, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                                 _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                               _______, _______, _______, _______, _______
    ),

/*
 * Scroll Layer: for scrolling while keyboard tray is pushed in
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | MAIN   |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | MAIN   |WhlRgt|WhlLft|WhlUp |WhlDn | PgUp |  K   |  J   |  |  J   |  K   | PgUp |WhlDn |WhlUp |WhlLft|WhlRgt|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  L   |  H   |ShiftP|Shift+|Space |  |Space |Shift+|ShiftP|  H   |  L   |
 *                        |      |      |/PgDn |Space |      |  |      |Space |/PgDn |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_SCROLL] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
        MAIN , _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
        MAIN , MS_WHLR, MS_WHLL, MS_WHLU, MS_WHLD, KC_PGUP,   KC_K ,   KC_J ,           KC_J ,   KC_K , KC_PGUP, MS_WHLD, MS_WHLU, MS_WHLL, MS_WHLR, _______,
                                   KC_L ,   KC_H , SCL_PGD,SCL_SSPC, KC_SPC ,          KC_SPC,SCL_SSPC, SCL_PGD,   KC_H ,   KC_L ,

      _______, _______, _______, _______, _______,                                                               _______, _______, _______, _______, _______
    ),

// /*
//  * Halcyon Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  * ,-----------------------------------.                                              ,-----------------------------------.
//  * |      |      |       |      |      |                                              |      |      |       |      |      |
//  * `-----------------------------------'                                              `-----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_split_3x6_5_hlc(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//
//       _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
//     ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [5] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [6] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [7] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

const uint16_t PROGMEM combo_lctl[] = { KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_rctl[] = { KC_DOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo_lalt[] = { KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_ralt[] = { KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo_zoom_in[] = { MN_Z, KC_V, COMBO_END};
const uint16_t PROGMEM combo_zoom_out[] = { KC_M, MN_SLSH, COMBO_END};
const uint16_t PROGMEM combo_lmouse[] = { MN_ENT, MN_3, COMBO_END};
const uint16_t PROGMEM combo_rmouse[] = { MN_SPC, MN_8, COMBO_END};
const uint16_t PROGMEM combo_lnumpad[] = { MN_4, MN_5, COMBO_END};
const uint16_t PROGMEM combo_light[] = { MN_6, MN_8, COMBO_END};
const uint16_t PROGMEM combo_lleader[] = { MN_Z, KC_B, COMBO_END};
const uint16_t PROGMEM combo_rleader[] = { MN_SLSH, KC_N, COMBO_END};
const uint16_t PROGMEM combo_scroll[] = { MN_4, MN_7, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_lctl, KC_LCTL),
    COMBO(combo_rctl, KC_RCTL),
    COMBO(combo_lalt, KC_LALT),
    COMBO(combo_ralt, KC_RALT),
    COMBO(combo_zoom_in, LCTL(KC_PLUS)),
    COMBO(combo_zoom_out, LCTL(KC_MINUS)),
    COMBO(combo_lmouse, TT(_MOUSE)),
    COMBO(combo_rmouse, TT(_MOUSE)),
    COMBO(combo_lnumpad, TT(_RMIRROR)),
    COMBO(combo_light, RM_TOGG),
    COMBO(combo_lleader, QK_LEAD),
    COMBO(combo_rleader, QK_LEAD),
    COMBO(combo_scroll, TO(_SCROLL))
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_released(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    // if we're "holding" key, do nothing - reset function will release the key
    // otherwise, perform tap action
    if(!tap_hold->held) {
        tap_code16(tap_hold->tap);
    }
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    // if state is pressed, the tapping term has ended, but the key is still being pressed
    if (state->pressed) {
        register_code16(tap_hold->hold);
        tap_hold->held = tap_hold->hold;
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    // if we're performing hold action, release held key
    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset, tap_dance_tap_hold_released}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_EQLS] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQUAL, KC_CIRCUMFLEX),
    [TD_3_LEFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_3, KC_LEFT),
    [TD_5_RIGHT] = ACTION_TAP_DANCE_TAP_HOLD(KC_5, KC_RIGHT),
    [TD_6_DOWN] = ACTION_TAP_DANCE_TAP_HOLD(KC_6, KC_DOWN),
    [TD_8_UP] = ACTION_TAP_DANCE_TAP_HOLD(KC_8, KC_UP),
    [TD_SWAYW_1] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_1), LGUI(KC_0)),
    [TD_SWAYW_2] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_2), LGUI(KC_9)),
    [TD_SWAYW_3] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_3), LGUI(KC_8)),
    [TD_SWAYW_4] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_4), LGUI(KC_7)),
    [TD_SWAYW_5] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_5), LGUI(KC_6)),
    [TD_SCROLL_PGDN] = ACTION_TAP_DANCE_TAP_HOLD(LSFT(KC_P), KC_PGDN)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MN_ESC:
            return g_tapping_term + 50;
        case MN_QUOT:
            return g_tapping_term + 50;
        default:
            return g_tapping_term;
    }
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_L, KC_A)) {
        layer_move(_ADJUST);
    }
}
