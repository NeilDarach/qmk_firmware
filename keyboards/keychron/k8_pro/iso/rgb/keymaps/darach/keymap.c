/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "print.h"
#include "os_detection.h"
#define KC_MS1 KC_MS_BTN1
#define KC_MS2 KC_MS_BTN2
#define KC_MS3 KC_MS_BTN3
#define KC_MS4 KC_MS_BTN4
#define KC_MS5 KC_MS_BTN5

int init_called = 0;




// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  ARROWS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[WIN_BASE] = LAYOUT_tkl_iso(
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,            KC_PSCR,  KC_CTANA, RGB_MOD,
     KC_NUHS, KC_A,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,           KC_DEL,   KC_END,   KC_PGDN,
     CW_TOGG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,  KC_BSLS, KC_ENT,
     KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,           KC_RSFT,            KC_UP,
     KC_LCTL, KC_LGUI, KC_LALT,                                LT(ARROWS,KC_SPC),                         KC_RALT,  KC_RGUI, MO(WIN_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_tkl_iso(
     QK_BOOT, KC_BRID, KC_BRIU, KC_TASK, KC_A   , RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,           _______,  _______,  RGB_TOG,
     _______, BT_HST1, BT_HST1, BT_HST1, _______, _______,  _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,  _______,  _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,           _______,  _______,  _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,           _______,            _______,
     _______, _______, _______,                               _______,                         _______,  _______,  _______, _______,  RGB_SAD,  _______,  RGB_SAI),

[MAC_BASE] = LAYOUT_tkl_iso(
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,             KC_A   ,  KC_SIRI,  RGB_MOD,
     KC_GRV,  KC_B,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_INS,   KC_HOME,  KC_PGUP,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,            KC_DEL,   KC_END,   KC_PGDN,
     CW_TOGG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,  KC_BSLS, KC_ENT,
     KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,           KC_RSFT,             KC_UP,
     KC_LCTL, KC_LOPTN,KC_LCMMD,                              LT(ARROWS,KC_SPC),                          KC_RCMMD, KC_ROPTN, MO(MAC_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_tkl_iso(
     QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,             _______,  _______,  RGB_TOG,
     _______, BT_HST1, BT_HST2, BT_HST3, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,
     RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,  _______,            _______,  _______,  _______,
     _______, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______,  _______,  _______,  _______,
     _______, _______, _______, _______, _______, _______, BAT_LVL, NK_TOGG, _______, _______, _______,  _______,            _______,            _______,
     _______, _______, _______,                                _______,                        _______,  _______,  _______,  _______,  _______,  _______,  _______),


[ARROWS] = LAYOUT_tkl_iso(
     XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,
     XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX,  XXXXXXX,           XXXXXXX,   XXXXXXX,   XXXXXXX,
     XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,   XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,
     KC_LSFT, XXXXXXX, XXXXXXX,    XXXXXXX,    KC_MS1,    KC_MS2,    KC_MS3,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,   XXXXXXX,           XXXXXXX,            XXXXXXX,
     KC_LCTL, KC_LGUI, KC_LALT,                                XXXXXXX,                         KC_RALT,  KC_RGUI, MO(WIN_FN),KC_RCTL, XXXXXXX,  XXXXXXX,  XXXXXXX)

};



/*
bool dip_switch_update_user(uint8_t index, bool active){
  printf("dip switch updated %d", index);
  switch(index){
    case 0:
      if(active) { // Mac mode
          layer_move(MAC_BASE);
      } else { // Windows mode
          layer_move(WIN_BASE);
      }
      return false;
    case 1:
      if(active){ //Cable mode
        // do stuff
      }
      else{ //BT mode
        // do stuff
      }
      break;
  }

  return true;
}
*/
bool dip_switch_update_mask_user(uint32_t state) {
  switch(state){
    case 0:
          layer_move(MAC_BASE);
          printf("Dip switch %ld - mac init(%d)\n",state,init_called);
        break;
    default:
          layer_move(WIN_BASE);
          printf("Dip switch %ld - windows init(%d)\n",state,init_called);
    }
    printf("Detected host os is %d, of unsure(%d),linux(%d),windows(%d),macos(%d),ios(%d)\n",detected_host_os(),OS_UNSURE,OS_LINUX,OS_WINDOWS,OS_MACOS,OS_IOS);
    return true;
}


uint32_t osid_callback(uint32_t trigger_time, void *cb_arg) {
  switch(detected_host_os()) {
    case OS_IOS:
    case OS_MACOS:
        layer_move(MAC_BASE);
        printf("Detected mac\n");
        break;
    default:
        layer_move(WIN_BASE);
        printf("Detected windows\n");
    }
        return 0;
}


void keyboard_post_init_user(void) { // Customise these values to desired behaviour
  init_called = 1;
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
	rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
    printf("Local init\n");
    /*
  switch(detected_host_os()) {
    case OS_IOS:
    case OS_MACOS:
        layer_move(MAC_BASE);
        printf("Detected mac\n");
    default:
        layer_move(WIN_BASE);
        printf("Detected windows\n");
    }
*/
    defer_exec(1000,osid_callback,NULL);

}


// Swap @ and " for windows
//const key_override_t quote_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, LSFT(KC_QUOT),(1<<WIN_BASE));
//const key_override_t at_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_2),(1<<WIN_BASE));


// Swap @ and " for all
const key_override_t quote_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, LSFT(KC_QUOT),(1<<WIN_BASE)||(1<<MAC_BASE));
const key_override_t at_key_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, LSFT(KC_2),(1<<WIN_BASE)||(1<<MAC_BASE));

// Swap ` for # for Mac
const key_override_t hash_key_override = ko_make_with_layers_negmods_and_options(0, KC_GRV, LOPT(KC_3),(1<<MAC_BASE),MOD_MASK_SHIFT,0);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&quote_key_override,
	&at_key_override,
	&hash_key_override,
	NULL // Null terminate the array of overrides!
};


bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    if (!process_caps_word(keycode,record)) { return false; }
    return true;
}


bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

            // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_DOT:
            return true;

        default:
            return false;
        // Deactivate Caps Word.
    }
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_2:
        case KC_QUOT:
            return true;
        default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_QUOT:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
                register_code16(KC_2);
            } else {
                register_code16(KC_QUOT);
            }
            break;
        case KC_2:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
                register_code16(KC_QUOT);
            } else {
                register_code16(KC_2);
            }
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_QUOT:
            if (shifted) {
                unregister_code16(KC_2);
            } else {
                unregister_code16(KC_QUOT);
            }
            break;
        case KC_2:
            if (shifted) {
                unregister_code16(KC_QUOT);
            } else {
                unregister_code16(KC_2);
            }
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}
