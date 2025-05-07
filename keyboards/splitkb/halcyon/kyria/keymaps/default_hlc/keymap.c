// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _LMIRROR,
    _RMIRROR,
    //_MOUSE,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

enum tap_dance_codes {
    TD_EQLS,
    TD_3_LEFT,
    TD_5_RIGHT,
    TD_6_UP,
    TD_8_DOWN
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define OSM_LALT OSM(MOD_LALT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_RALT OSM(MOD_RALT)
#define OSM_RCTL OSM(MOD_RCTL)

#define MN_Z MT(MOD_LSFT, KC_Z)
#define MN_SLSH MT(MOD_RSFT, KC_SLASH)
#define MN_SPC LT(_NAV, KC_SPACE)
#define MN_ENT LT(_NAV, KC_ENT)
#define MN_1 MT(MOD_LCTL, KC_1)
#define MN_2 MT(MOD_LALT, KC_2)
#define MN_3 TD(TD_3_LEFT)
#define MN_5 TD(TD_5_RIGHT)
#define MN_6 TD(TD_6_UP)
#define MN_8 TD(TD_8_DOWN)
#define MN_9 MT(MOD_RALT, KC_9)
#define MN_0 MT(MOD_RCTL, KC_0)
#define OS_LMIR OSL(_LMIRROR)
#define OS_RMIR OSL(_RMIRROR)

#define WIN_NXT LALT(KC_TAB)
#define WIN_SEL LALT(LCTL(KC_TAB))

#define SYM_EQL TD(TD_EQLS)

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
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : | Ctrl/' |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |LSft/Z|   X  |   C  |   V  |   B  | 3/←  | 5/→  |  |  6/↑ |  8/↓ |   N  |   M  | ,  < | . >  |RSft//| RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  1/  |  2/  |Miror/| Enter|  4   |  |  7   |Space |Miror/|  9/ |  0/  |
 *                        |LCtrl | LAlt | Sym  |      |      |  |      |      | Num  | RAlt| RCtrl|
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_5_hlc(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y  ,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H  ,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
     KC_LSFT , MN_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , MN_3   , MN_5   ,     MN_6   , MN_8  , KC_N  ,   KC_M ,KC_COMM, KC_DOT ,MN_SLSH, KC_RSFT,
                                 MN_1  ,   MN_2 , OS_LMIR, MN_ENT , KC_4   ,     KC_6   , MN_SPC,OS_RMIR,   MN_9 ,  MN_0 ,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * LMirror: Symbols on RH, mirror on LH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Bksp  |  P   |   O  |  I   |   U  |  Y   |                              |  &   |  #   |  [   |  ]   |  @   |   *    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   '    |  ;   |  L   |  K   |  J   |  H   |                              |  !   |  =/^ |  (   |  )   |  $   |   `    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | RShift |RSft//|  .   |  ,   |  M   |  N   |  8/↓ |  6/↑ |  |      |      |  |   |  _   |  {   |  }   |  ~   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |  0/  |  9/  |      |Space |  7   |  |      |      |      |      |      |
 *                        | RCtrl| RAlt |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_LMIRROR] = LAYOUT_split_3x6_5_hlc(
      KC_BSPC,   KC_P ,   KC_O ,   KC_I ,   KC_U ,   KC_Y ,                                         KC_AMPR, KC_HASH, KC_LBRC, KC_RBRC,  KC_AT , KC_ASTR,
      KC_QUOT, KC_SCLN,   KC_L ,   KC_K ,   KC_J ,   KC_H ,                                         KC_EXLM, SYM_EQL, KC_LPRN, KC_RPRN, KC_DLR , KC_GRAVE,
      KC_RSFT, MN_SLSH,  KC_DOT, KC_COMM,   KC_M ,   KC_N ,   MN_8 ,   MN_6 ,     _______, _______, KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_TILD, _______,
                                   MN_0 ,   MN_9 , _______,  MN_SPC,   KC_7 ,     _______, _______, _______, _______, _______,

      _______, _______, _______, _______, _______,                                                           _______, _______, _______, _______, _______
    ),

/*
 * RMirror: Numbers on LH, mirror on RH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  7   |  8   |  9   |  +   |  *   |                              |  T   |  R   |  E   |  W   |  Q   |  Tab   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    %   |  4   |  5   |  6   |  0   |  .   |                              |  G   |  F   |  D   |  S   |  A   |  Esc   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  -   |  /   |      |      |  |  5/→ |  3/← |  B   |  V   |  C   |  X   |LSft/Z| LShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |  4   |Enter |      |  2/  |  1/  |
 *                        |      |      |      |      |      |  |      |      |      | LAlt | LCtrl|
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_RMIRROR] = LAYOUT_split_3x6_5_hlc(
      _______,   KC_7 ,   KC_8 ,   KC_9 , KC_PLUS, KC_ASTR,                                           KC_T ,   KC_R ,   KC_E ,   KC_W ,   KC_Q ,  KC_TAB,
      KC_PERC,   KC_4 ,   KC_5 ,   KC_6 ,   KC_0 , KC_DOT ,                                           KC_G ,   KC_F ,   KC_D ,   KC_S ,   KC_A ,  KC_ESC,
      _______,   KC_1 ,   KC_2 ,   KC_3 , KC_MINS, KC_SLSH, _______, _______,       MN_5 ,   MN_3 ,   KC_B ,   KC_V ,   KC_C ,   KC_X ,   MN_Z , KC_LSFT,
                                 _______, _______, _______, _______, _______,       KC_4 ,  MN_ENT, _______,   MN_2 ,   MN_1 ,

      _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Nav Layer: Navigation, other frequently used keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      | LCtrl| LAlt | BkSpc|      |                              |CpsWrd| Del  | RAlt | RCtrl|      | PrtSc  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |AlCtTb|   →  |  ↑   |   ↓  |  ←   |                              |   ←  |  ↓   |   ↑  |   →  |AlCtTb|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |AltTab|      | PgUp | PgDn |      |      |      |  |      |      |      | PgDn | PgUp |      |AltTab|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
      _______, _______,OSM_LCTL,OSM_LALT, KC_BSPC, _______,                                     CW_TOGG, KC_DEL ,OSM_RALT,OSM_RCTL, _______, KC_PSCR,
      _______, WIN_SEL, KC_RGHT, KC_UP  , KC_DOWN, KC_LEFT,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, WIN_SEL, _______,
      _______, WIN_NXT, _______, KC_PGUP, KC_PGDN, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, WIN_NXT, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_SYM] = LAYOUT_split_3x6_5_hlc(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_FUNCTION] = LAYOUT_split_3x6_5_hlc(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Boot   |      |      |QWERTY|      |      |                              |      |      |      |      |      | Boot   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
      QK_BOOT, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
      _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                      _______, _______, _______, _______, _______
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
};
#endif


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
    [TD_6_UP] = ACTION_TAP_DANCE_TAP_HOLD(KC_6, KC_UP),
    [TD_8_DOWN] = ACTION_TAP_DANCE_TAP_HOLD(KC_8, KC_DOWN),
};
