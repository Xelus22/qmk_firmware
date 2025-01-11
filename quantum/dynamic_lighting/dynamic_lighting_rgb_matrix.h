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

#include "../color.h"
#include "rgb_matrix.h"

extern hsv_t g_rgb_matrix_leds[RGB_MATRIX_LED_COUNT];

bool dynamic_lighting_rgb_matrix_enabled(void);
void dynamic_lighting_rgb_matrix_set_led_hsv(int index, hsv_t hsv);
void dynamic_lighting_rgb_matrix_set_led_range_hsv(int index, int range, hsv_t hsv);
hsv_t dynamic_lighting_rgb_matrix_get_led_hsv(int index);
