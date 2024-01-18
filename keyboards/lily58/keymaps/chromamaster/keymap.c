#include QMK_KEYBOARD_H

#include "layers.h"
#include "oled.c"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \ |      |      |      |
 *                   `---------------------------'            '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  XXXXXXX,     XXXXXXX,    
  KC_N,     KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC,      KC_ENT, MO(_RAISE), KC_BSPC, KC_RALT
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   <  |   [  |   {  |   (  |   +  |                    |   -  |   )  |   }  |   ]  |   >  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   |  |   &  |   *  |   ^  |   ?  |      |
 * |------+------+------+------+------+------|  DEL  |    | Enter |------+------+------+------+------+------|
 * |LCTRL |      |      |      |   `  |   /  |-------|    |-------|   \  |   ~  |   =  |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \ |      |      |      |
 *                   `---------------------------'            '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,       KC_F12,
  _______, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS,                   KC_MINS, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT,        _______,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PIPE, KC_AMPR, KC_ASTR, KC_CIRC, KC_QUESTION,  XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_SLSH, _______, _______, KC_BSLS, KC_TILD, KC_EQL,  XXXXXXX, XXXXXXX,      XXXXXXX,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   1  |   2  |   3  |   4  |   5  |                    | HOME | PGDN | PGUP | END  |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|  DEL  |    | Enter |------+------+------+------+------+------|
 * |LCTRL |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |      |      |   \  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \ Enter\  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \ |      |      |      |
 *                   `---------------------------'            '------''--------------------'
 */

[_RAISE] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, KC_DEL,
  _______,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  _______,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Vol- | Mute | Vol+ |      |                    |      |Brigh+|      |Brigh-|      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CAPS |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space /        \BackSP\  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/      /          \      \ |      |      |      |
 *                   `---------------------------'            '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                   XXXXXXX, KC_BRIU, XXXXXXX, KC_BRID, XXXXXXX, XXXXXXX,
  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______, _______, _______, _______
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
