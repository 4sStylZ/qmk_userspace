/*
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2020 4sStylZ <4sstylz@protonmail.ch>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include QMK_KEYBOARD_H
#include <keycodes.h>

// Implement Super-alt↯tab
// See https://docs.qmk.fm/#/feature_macros?id=super-alt↯tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Defining all the custom keycodes.
enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  SLC_ROW,
  SLC_ALL,
  SLC_WRD
};

// Lock Windows with a 4 key combinaison.
const uint16_t PROGMEM lock_combo[] = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(lock_combo, LGUI(KC_O))};

// Define the keycodes for one qwerty layer and one Fn layer.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
   * │ ` Esc│   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │  -   │  =   │ Bksp │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │   [  │  ]   │Enter │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤      │
   * │  FN  │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │   ;  │   '  │   #  │      │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ Shift│  \   │   Z  │   X  │   C  │   V  │   B  │   N  │   M  │   ,  │   .  │   /  │ Shift│ PGUP │
   * ├──────┼──────┼──────┼──────┴──────┴──────┴──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┤
   * │ CTRL │ Gui  │ Alt  │                      Space                     │ Gui  │ App  │ Alt  │ CTRL │
   * └──────┴──────┴──────┴────────────────────────────────────────────────┴──────┴──────┴──────┴──────┘
   *
   * Hidden features : 
   *  - Left Shift is also Home on a single tap.
   *  - Left Ctrl is also End on a single tap.
   *  - Right Shift is also page-up on a single tap.
   *  - Right Ctrl is also page-down on a single tap.
   *  - Press JKLM for Windows + L (Session lock)
   */
  [0] = LAYOUT( \
    KC_GESC, KC_1   , KC_2  , KC_3   , KC_4 , KC_5   , KC_6 , KC_7 , KC_8  , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
    KC_TAB , KC_Q   , KC_W  , KC_E   , KC_R , KC_T   , KC_Y , KC_U , KC_I  , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_ENT ,
    MO(1)  , KC_A   , KC_S  ,          KC_D , KC_F   , KC_G , KC_H , KC_J  , KC_K   , KC_L   , KC_SCLN, KC_QUOT         ,
    KC_LSPO         , KC_Z  ,          KC_X , KC_C   , KC_V , KC_B , KC_N  , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
    KC_LCPO, KC_LGUI,KC_LALT,                 KC_NUBS,               KC_SPC, KC_NUHS, KC_RGUI, KC_APP , KC_RALT, KC_RCPC
  ),

  /* 1
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
   * │ALT F4│  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │  Del │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │      │      │SLCALL│SLCROW│SLCWRD│      │ Bksp │ Home │  Up  │  End │ Brt+ │ Brt- │PrtScn│      │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤      │
   * │      │      │ CUT  │ COPY │PASTE │ Del. │Enter │ Left │ Down │ Right│BL Tog│BL Stp│BL Brt│      │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │      │      │ Mute │ Vol- │ Vol+ │↯ATab │      │      │      │      │      │ Reset│      │      │
   * ├──────┼──────┼──────┼──────┴──────┴──────┴──────┴──────┴──────┴──────┼──────┼──────┼──────┼──────┤
   * │      │      │      │                                                │      │      │      │      │
   * └──────┴──────┴──────┴────────────────────────────────────────────────┴──────┴──────┴──────┴──────┘
   */
  [1] = LAYOUT( \
    LALT(KC_F4), KC_F1  , KC_F2       , KC_F3       , KC_F4       , KC_F5       , KC_F6  , KC_F7  , KC_F8   , KC_F9   , KC_F10  , KC_F11 , KC_F12 , KC_DEL ,
    _______    , _______, SLC_ALL     , SLC_ROW     , SLC_WRD     , _______     , KC_BSPC, KC_HOME, KC_UP   , KC_END  , KC_BRIU , KC_BRID, KC_PSCR, _______,
    _______    , _______, LSFT(KC_DEL),               LCTL(KC_INS), LSFT(KC_INS), KC_DEL , KC_ENT , KC_LEFT , KC_DOWN , KC_RIGHT, BL_TOGG, BL_STEP         ,
    _______             , KC_MUTE     ,               KC_VOLD     , KC_VOLU     , ALT_TAB, _______, _______ , _______ , _______ , _______, RESET  , _______,
    _______    , _______, _______     ,                             _______     ,                   _______ , _______ , _______ , _______, _______, _______
  )
};

// Processing all the key pressed.
// Alt+tab.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Depending keycodes…
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case SLC_ALL:
      select_all(record);
      break;
    case SLC_ROW:
      select_row(record);
      break;
    case SLC_WRD:
      select_word(record);
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
