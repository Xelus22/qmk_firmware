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
#include "rgblight.h"

extern hsv_t g_dynamic_lighting_rgblight_leds[RGBLIGHT_LED_COUNT];

bool  dynamic_lighting_rgblight_enabled(void);
void  dynamic_lighting_rgblight_set_led_hsv(int index, hsv_t hsv);
void  dynamic_lighting_rgblight_set_led_range_hsv(int index, int range, hsv_t hsv);
hsv_t dynamic_lighting_rgblight_get_led_hsv(int index);
