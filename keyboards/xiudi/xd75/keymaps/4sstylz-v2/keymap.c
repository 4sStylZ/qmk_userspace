/*
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2024 4sStylZ <4sstylz@protonmail.ch>
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
// #include "action_util.h"

// Implement Super-alt↯tab
// See https://docs.qmk.fm/#/feature_macros?id=super-alt↯tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_screen_lock_triggered = false;
uint16_t screen_lock_timer = 0;

// Defining all the custom keycodes.
enum custom_keycodes {
  ALT_TAB  = SAFE_RANGE,
  KC_00  ,
  SLC_ROW,
  SLC_ALL,
  SLC_WRD
};

// Screen lock feature
enum combo_events {
  SCR_LCK
};
const uint16_t PROGMEM lock_combo[] = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
combo_t key_combos[] = {COMBO(lock_combo, SCR_LCK)};

// Layer shorthand
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │` Esc │   1  │   2  │   3  │   4  │   5  │  Del │   6  │   7  │   8  │   9  │   0  │  -   │  =   │PrtScn│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │ Bksp │   Y  │   U  │   I  │   O  │   P  │  [   │  ]   │ Home │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ FN   │   A  │   S  │   D  │   F  │   G  │Enter │   H  │   J  │   K  │   L  │   ;  │   '  │   #  │  End │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Shft │   Z  │   X  │   C  │   V  │   B  │ALTTAB│   N  │   M  │   ,  │   .  │   /  │ Shft │ FN   │ PgUp │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │ Gui  │ Alt  │ Back │ Frwd │Space │ App  │Space │ Left │  Up  │ Down │ Right│ Alt  │ Ctrl │ PgDn │
 * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
 */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    QK_GESC, KC_1   , KC_2   , KC_3   , KC_4        , KC_5  , KC_DEL , KC_6  , KC_7   , KC_8   , KC_9   , KC_0    , KC_MINUS, KC_EQUAL, KC_PSCR,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R        , KC_T  , KC_BSPC, KC_Y  , KC_U   , KC_I   , KC_O   , KC_P    , KC_LBRC , KC_RBRC , KC_HOME,
    MO(_FN), KC_A   , KC_S   , KC_D   , KC_F        , KC_G  , KC_ENT , KC_H  , KC_J   , KC_K   , KC_L   , KC_SCLN , KC_QUOT , KC_NUHS , KC_END ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V        , KC_B  , ALT_TAB, KC_N  , KC_M   , KC_COMM, KC_DOT , KC_SLSH , KC_RSFT , MO(_FN) , KC_PGUP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_WBAK, KC_KP_MINUS , KC_SPC, KC_APP , KC_SPC, KC_LEFT, KC_UP  , KC_DOWN, KC_RIGHT, KC_RALT , KC_RCTL , KC_PGDN
  ),

/* FUNCTION
 * NB :  My OS  layout (Bépo) don't have direct access to numbers, so that's why I use « LSFT » mod for the keypad.
 * You need to remove LSFT(KC) for using this layout with Qwerty. Also the use of KC_8, 7, and V are some specific Bépo
 * things.
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │Alt F4│  F1  │  F2  │  F3  │  F4  │  F5  │BL Tog│  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │ # Lk │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │SltAll│SltRow│SltRow│ Brt+ │BL Stp│      │      │ KP 7 │ KP 8 │ KP 9 │   8  │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ Cut  │ Copy │Paste │ Brt- │BL Brt│      │      │ KP 4 │ KP 5 │ KP 6 │   7  │      │Reset │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ Mute │ Vol- │ Vol+ │ Play │Ld Tog│      │      │ KP 1 │ KP 2 │ KP 3 │Enter │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │Ld M+ │      │      │ KP 0 │KC 00 │  V   │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    LALT(KC_F4), KC_F1  , KC_F2       , KC_F3       , KC_F4       , KC_F5  , BL_TOGG, KC_F6  , KC_F7  , KC_F8      , KC_F9      , KC_F10    , KC_F11  , KC_F12 , KC_NUM,
    _______    , _______, SLC_ALL     , SLC_ROW     , SLC_WRD     , KC_BRIU, BL_STEP, _______, _______, LSFT(KC_7) , LSFT(KC_8) , LSFT(KC_9), KC_8    , _______, _______,
    _______    , _______, LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), KC_BRID, BL_BRTG, _______, _______, LSFT(KC_4) , LSFT(KC_5) , LSFT(KC_6), KC_7    , _______, QK_BOOT,
    _______    , _______, KC_MUTE     , KC_VOLD     , KC_VOLU     , KC_MPLY, RGB_TOG, _______, _______, LSFT(KC_1) , LSFT(KC_2) , LSFT(KC_3), KC_ENT  , _______, _______,
    _______    , _______, _______     , KC_WBAK     , KC_WFWD     , _______, RGB_MOD, _______, _______, LSFT(KC_0) , KC_00      , KC_V      , _______ , _______, _______
  )
};

#include "custom_features.c"

// Processing all the key pressed.
// Alt+tab.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Depending keycodes…
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          gp100_led_on();
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case KC_00:
      insert_00(record);
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

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SCR_LCK:
      if (pressed) {
          is_screen_lock_triggered = true;
          gp103_led_on();
          windows_lock();
        screen_lock_timer = timer_read();
      }
      break;
  }
}

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      gp100_led_off();
      is_alt_tab_active = false;
    }
  }
  if (is_screen_lock_triggered) {
    if (timer_elapsed(screen_lock_timer) > 750) {
      gp103_led_off();
      is_screen_lock_triggered = false;
    }
  }
}

#include "led_management.c"

void keyboard_post_init_user (void) {
  debug_enable=true;
  debug_matrix=true;
  setDefaultDisplay();
}

#pragma once

/* Enable the space-cadet options */
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_PGUP
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_PGDN
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_HOME
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_END

#define BACKLIGHT_BREATHING
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
