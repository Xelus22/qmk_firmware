#if defined(RGB_MATRIX_PER_KEY_COLOUR) && defined(ENABLE_RGB_MATRIX_CUSTOM_PER_KEY)
RGB_MATRIX_EFFECT(CUSTOM_PER_KEY)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool CUSTOM_PER_KEY(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // for now simply set the colour of each key to the colour in the g_hsv_per_key_colour array
    rgb_t rgb;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb = rgb_matrix_hsv_to_rgb(g_hsv_per_key_colour[i]);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_CUSTOM_PER_KEY
