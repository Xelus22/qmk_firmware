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

#include <stdint.h>
#include "quantum.h"
#include "analogkey.h"

#pragma once

switch_distance_t raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t          distance_to_raw(switch_distance_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
switch_distance_t get_max_distance(void);

// private but should be used if required
switch_scaled_t   raw_to_scaled(switch_scaled_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
switch_distance_t scaled_to_distance(switch_scaled_t scaled);
