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


#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
#define MANUFACTURER    4sStylZ and others makers
#define PRODUCT         ASK60
#define DESCRIPTION     QMK keyboard firmware for ASK60 handwired

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// Originally made for a Teensy 2++
#define MATRIX_COL_PINS { D7, E7, D5, D4, C7, C6, C5, C4, C3, C2, C1, C0, E1, E0 }
#define MATRIX_ROW_PINS { D3, D2, D1, D0, B7 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Enable the space-cadet options */
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_PGUP
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_PGDOWN
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_HOME
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_END

/* Enable double tab */
#define TAPPING_TERM 175

#define COMBO_COUNT 1