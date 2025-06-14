/* Copyright 2025 Harrison Chan (Xelus)
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

#pragma once

#include <stdint.h>
#include "analogkey.h"

#define LUT_SIZE 1024 // Size of the LUT, adjust as necessary

#define DISTANCE_MM_MULTIPLIER 10000.0 // 1mm = 10000 distance units

#define DEFAULT_MAX_DISTANCE (4.0 * DISTANCE_MM_MULTIPLIER) // Default maximum distance in distance units (0.0001mm increments)

typedef enum {
    SWITCH_LUT_DUHUK_HERZ,
    // add in here
    SWITCH_LUT_END
} switch_lut_picker_t;

#ifndef DEFAULT_SWITCH_LUT
#    define DEFAULT_SWITCH_LUT SWITCH_LUT_DUHUK_HERZ // Default switch LUT
#endif

void     switch_lut_init(void);
void     set_switch_lut(switch_lut_picker_t lut);
switch_distance_t get_switch_max_distance(void);

// get the pointer to the switch LUT
switch_distance_t get_switch_distance_value(switch_scaled_t scaled_value);

switch_scaled_t get_switch_scaled_value(switch_distance_t distance);