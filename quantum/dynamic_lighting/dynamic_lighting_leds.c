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

#include "dynamic_lighting_leds.h"

led_t g_dynamic_lighting_led_state;

void dynamic_lighting_led_init(void) {

}

bool dynamic_lighting_led_enabled() {
    return true;
}

void dynamic_lighting_led_set_value(int bit, bool state) {
    if (state) {
        g_dynamic_lighting_led_state.raw |= (1 << bit);
    } else {
        g_dynamic_lighting_led_state.raw &= ~(1 << bit);
    }
}

bool dynamic_lighting_led_get_value(int bit) {
    return g_dynamic_lighting_led_state.raw & (1 << bit);
}
