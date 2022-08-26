#include QMK_KEYBOARD_H
#include "sendstring_colemak.h"

#define L0 0
#define L1 1

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here

  CUSTOM_TEST_KEY,
};

/*
 * A note about alternative keyboard layouts:
 * If you are using an alternative keyboard layout (e.g. colemak)
 * then you will still need to build your hardware layout based on QWERTY
 * since your custom layout is handled in software in your OS.
 * 
 * You can however build a keyboard emulation layer to emulate your
 * keyboard layout in hardware when the keyboard is being used on a
 * PC set to QWERTY.
 * 
 * This could be resolved by using `keymap_colemak.h` but that will make
 * the layout less portable in the end. Thus, this keyboard layout is
 * built for QWERTY despite being used in colemak. A notable excludsion is
 * `sendstring_colemak.h` which is being included in order for the `SEND_STRING`
 * macro to be used with colemak.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* 
  * # Main Layer
  * Keys in square brackets `[L1]` indicate momentary layer switching to
  * The layer in brackets - that layer will be active while the key is
  * being held down.
  * 
  * For full documentation of available options
  * @see https://docs.qmk.fm/#/keycodes
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |   ESC  |   1  |   2  |   3  |   4  |   5  |   6  |           |   6  |   7  |   8  |   9  |   0  |   -  |   =    |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * | Tab    |   Q  |   W  |   E  |   R  |   T  |  F5  |           |  F8  |   Y  |   U  |   I  |   O  |   P  |   \    |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
  * |--------+------+------+------+------+------|      |           |  F7  |------+------+------+------+------+--------|
  * | LShift |   Z  |   X  |   C  |   V  |   B  | F19  |           |      |   N  |   M  |   ,  |   .  |   /  | rShift |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |lCtrl | lWIN | lALT |(none)|  l1  |                                       |  l1  | rAlt |   [  |   ]  | rCtrl  |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        | Home | End  |       | left  | right |
  *                                 ,------|------|------|       |------+--------+------.
  *                                 |      |      | PgUp |       |  up  |        |      |
  *                                 | Space|Space |------|       |------|  lCtrl |Enter |
  *                                 |      |      | PgDn |       | down |        |      |
  *                                 `--------------------'       `----------------------'
  */
  [L0] = LAYOUT_ergodox(
    // left hand
    KC_ESC,     KC_1,      KC_2,     KC_3,      KC_4,       KC_5,     KC_6,
    KC_TAB,     KC_Q,      KC_W,     KC_E,      KC_R,       KC_T,     KC_F5,
    KC_BSPC,    KC_A,      KC_S,     KC_D,      KC_F,       KC_G,
    KC_LSFT,    KC_Z,      KC_X,     KC_C,      KC_V,       KC_B,     KC_F19,
    KC_LCTRL,   KC_LWIN,   KC_LALT,  KC_NO,     MO(L1),

                                                            KC_HOME,  KC_END,
                                                                      KC_PGUP,
                                                KC_SPC,     KC_SPC,   KC_PGDN,

    // right hand
    KC_6,       KC_7,      KC_8,     KC_9,      KC_0,       KC_MINS,  KC_EQUAL,
    KC_F8,      KC_Y,      KC_U,     KC_I,      KC_O,       KC_P,     KC_BSLS,
                KC_H,      KC_J,     KC_K,      KC_L,       KC_SCLN,  KC_QUOT,
    KC_F7,      KC_N,      KC_M,     KC_COMM,   KC_DOT,     KC_SLSH,  KC_RSFT,
                           MO(L1),   KC_RALT,   KC_LBRC,    KC_RBRC,  KC_RCTRL,
        
    KC_LEFT,    KC_RIGHT,
    KC_UP,
    KC_DOWN,    KC_LCTRL,  KC_ENT
  ),

 /*
  * # Layer 1
  * 
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |   `~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F6  |  F7  |  F8  |  F9  | F10  | F11  |  F12   |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |      |  Ms1 | MsUp | Ms2  |      |      |           |      |      | PgUp |  up  | PgDn |      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |MsLeft| Ms1  |MsRght|      |------|           |------|      | left | down | right|      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |MsDown|      |      |      |           |      |      | home |      | end  |      |        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |      |      |      |      |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       | prev | next |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |VolUp |      |      |
  *                                 |      |      |------|       |------| mute | play |
  *                                 |      |      | eject|       |VolDn |      |      |
  *                                 `--------------------'       `--------------------'
  */
[L1] = LAYOUT_ergodox(
       KC_GRAVE,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
       _______,   _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  CUSTOM_TEST_KEY,
       _______,   _______,  KC_MS_L,  KC_BTN1,  KC_MS_R,  _______,
       _______,   _______,  _______,  KC_MS_D,  _______,  _______,  _______,
       _______,   _______,  _______,  _______,  _______,

                                                          _______,  _______,
                                                                    _______,
                                                _______,  _______,  KC_EJCT,
    // right hand
       KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
       _______,   _______,  KC_PGUP,  KC_UP,    KC_PGDN,  _______,  _______,
                  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  KC_MPLY,
       _______,   _______,  KC_HOME,  _______,  KC_END,   _______,  _______,
                            _______,  _______,  _______,  _______,  _______,
       
       KC_MPRV,   KC_MNXT,
       KC_VOLU,
       KC_VOLD,   KC_MUTE,  KC_MPLY
),



// /*
//  * Empty layout below. Copy & paste for quicker layer generation.
//  * 
//  * ,--------------------------------------------------.           ,--------------------------------------------------.
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
//  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
//  *   |      |      |      |      |      |                                       |      |      |      |      |      |
//  *   `----------------------------------'                                       `----------------------------------'
//  *                                        ,-------------.       ,-------------.
//  *                                        |      |      |       |      |      |
//  *                                 ,------|------|------|       |------+------+------.
//  *                                 |      |      |      |       |      |      |      |
//  *                                 |      |      |------|       |------|      |      |
//  *                                 |      |      |      |       |      |      |      |
//  *                                 `--------------------'       `--------------------'
//  */
// [YOUR_LAYER_NAME] = LAYOUT_ergodox(
//     // lefthand
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,

//                                                           _______,  _______,
//                                                                     _______,
//                                                 _______,  _______,  _______,
//     // right hand
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//                   _______,  _______,  _______,  _______,  _______,  _______,
//        _______,   _______,  _______,  _______,  _______,  _______,  _______,
//                             _______,  _______,  _______,  _______,  _______,
       
//        _______,   _______,
//        _______,
//        _______,   _______,  _______
// ),

};

/*
 * This method can be used to add custom macros into the keyboard
 * layout. First, add your custom keycode name into `custom_keycodes`
 * then, you can react to the press event here.
 * 
 * Return `false` to not handle the event further, return `true` if you
 * want qmk to handle the keyboard event.
 * 
 * @see https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CUSTOM_TEST_KEY:
      if (record->event.pressed) {
        SEND_STRING("THIS IS A TEST");
      }
      return false;
  }
  return true;
}


/*
 * Runs just one time when the keyboard initializes.
 */
void matrix_init_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
};

/*
 * Runs constantly in the background, in a loop.
 * 
 * NOTE: LED 1, 2 & 3 refer to optional LEDs that can be soldered to the
 *       microcontroller that aren't there by default - Only the board LED
 *       is there by default.
 */
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case L1:
            ergodox_board_led_on();
            break;
        case L0:
        default:
            ergodox_board_led_off();
            break;
    }

};
