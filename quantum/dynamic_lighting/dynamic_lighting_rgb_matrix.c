/* Copyright 2024 Harrison Chan (Xelus)
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

#include "dynamic_lighting_rgb_matrix.h"

hsv_t g_dynamic_lighting_rgb_matrix_leds[RGB_MATRIX_LED_COUNT] = {0};

bool dynamic_lighting_rgb_matrix_enabled(void) {
    return true;
}

void dynamic_lighting_rgb_matrix_set_led_hsv(int index, hsv_t hsv) {
    if (index < 0 || index >= RGB_MATRIX_LED_COUNT) {
        return;
    }
    g_dynamic_lighting_rgb_matrix_leds[index] = hsv;
}

void dynamic_lighting_rgb_matrix_set_led_range_hsv(int index, int range, hsv_t hsv) {
    if (index < 0 || index + range >= RGB_MATRIX_LED_COUNT) {
        return;
    }

    for (int i = index; i < index + range; i++) {
        g_dynamic_lighting_rgb_matrix_leds[i] = hsv;
    }
}

hsv_t dynamic_lighting_rgb_matrix_get_led_hsv(int index) {
    if (index < 0 || index >= RGB_MATRIX_LED_COUNT) {
        return (hsv_t){0, 0, 0};
    }
    return g_dynamic_lighting_rgb_matrix_leds[index];
}
