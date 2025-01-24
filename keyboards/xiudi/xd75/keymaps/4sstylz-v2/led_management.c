
void led_set_user(uint8_t usb_led) {
    if (IS_LAYER_ON(_FN)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
}

/**
 * Défault led state and colors
 */
void setDefaultDisplay(void) {
    _delay_ms(10);
    rgblight_setrgb_at(180, 35, 0, 0);
    _delay_ms(10);
    rgblight_setrgb_at(200, 35, 0, 1);
    _delay_ms(10);
    rgblight_setrgb_at(220, 35, 0, 2);
    _delay_ms(10);
    rgblight_setrgb_at(220, 35, 0, 3);
    _delay_ms(10);
    rgblight_setrgb_at(200, 35, 0, 4);
    _delay_ms(10);
    rgblight_setrgb_at(180, 35, 0, 5);
}

/**
 * Colors for the FN layer
 */
void setFNDisplay(void) {
    _delay_ms(10);
    rgblight_setrgb_at(145, 45, 0, 0);
    _delay_ms(10);
    rgblight_setrgb_at(160, 45, 0, 1);
    _delay_ms(10);
    rgblight_setrgb_at(175, 45, 0, 2);
    _delay_ms(10);
    rgblight_setrgb_at(190, 45, 0, 3);
    _delay_ms(10);
    rgblight_setrgb_at(205, 45, 0, 4);
    _delay_ms(10);
    rgblight_setrgb_at(220, 45, 0, 5);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FN:
        setFNDisplay();
        break;

    default: //  for any other layers, or the default layer
        setDefaultDisplay();
        break;
    }
  return state;
}
