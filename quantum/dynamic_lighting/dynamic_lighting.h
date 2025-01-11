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

// probably need a bit in EEPROM to store the dynamic lighting override
// for each subsystem

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DYNAMIC_LIGHTING_TYPE_LED = 0,
    DYNAMIC_LIGHTING_TYPE_RGBLIGHT,
    DYNAMIC_LIGHTING_TYPE_RGB_MATRIX,
} dynamic_lighting_type_t;

// Direct LED GPIO control
#ifdef DYNAMIC_LIGHTING_GPIO_LEDS_ENABLE
#    include "dynamic_lighting_gpio_leds.h"
#endif

// RGB Light
#ifdef DYNAMIC_LIGHTING_RGBLIGHT_ENABLE
#    include "dynamic_lighting_rgblight.h"
#endif

// RGB Matrix
#ifdef DYNAMIC_LIGHTING_RGB_MATRIX_ENABLE
#    include "dynamic_lighting_rgb_matrix.h"
#endif

void dynamic_lighting_init(void);

bool dynamic_lighting_type_enabled(dynamic_lighting_type_t type);

// Set the LED state for the given subsystem
#if defined(DYNAMIC_LIGHTING_RGBLIGHT_ENABLE) || defined(DYNAMIC_LIGHTING_RGB_MATRIX_ENABLE)
#    include "color.h"
void  dynamic_lighting_set_led_hsv(dynamic_lighting_type_t type, int index, hsv_t hsv);
void  dynamic_lighting_set_led_range_hsv(dynamic_lighting_type_t type, int index, int range, hsv_t hsv);
void  dynamic_lighting_set_all_hsv(dynamic_lighting_type_t type, hsv_t hsv);
hsv_t dynamic_lighting_get_led_hsv(dynamic_lighting_type_t type, int index);
#endif

#if defined(DYNAMIC_LIGHTING_GPIO_LEDS_ENABLE)
void dynamic_lighting_set_led(dynamic_lighting_type_t type, int index, bool state);
bool dynamic_lighting_get_led(dynamic_lighting_type_t type, int index);
#endif
