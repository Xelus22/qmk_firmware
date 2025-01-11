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

#include "dynamic_lighting.h"

void dynamic_lighting_init(void) {
    // Initialize the dynamic lighting subsystems

#ifdef DYNAMIC_LIGHTING_GPIO_LEDS_ENABLE
    dynamic_lighting_led_init();
#endif

#ifdef DYNAMIC_LIGHTING_RGBLIGHT_ENABLE
    dynamic_lighting_rgblight_init();
#endif

#ifdef DYNAMIC_LIGHTING_RGB_MATRIX_ENABLE
    dynamic_lighting_rgb_matrix_init();
#endif
}

bool dynamic_lighting_type_enabled(dynamic_lighting_type_t type) {
    switch (type) {
#ifdef DYNAMIC_LIGHTING_GPIO_LEDS_ENABLE
        case DYNAMIC_LIGHTING_TYPE_LED:
            return dynamic_lighting_led_enabled();
#endif
#ifdef DYNAMIC_LIGHTING_RGBLIGHT_ENABLE
        case DYNAMIC_LIGHTING_TYPE_RGBLIGHT:
            return dynamic_lighting_rgblight_enabled();
#endif
#ifdef DYNAMIC_LIGHTING_RGB_MATRIX_ENABLE
        case DYNAMIC_LIGHTING_TYPE_RGB_MATRIX:
            return dynamic_lighting_rgb_matrix_enabled();
#endif
        default:
            return false;
    }
};
