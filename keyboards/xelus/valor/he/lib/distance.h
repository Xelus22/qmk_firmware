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

#pragma once

uint16_t raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t distance_to_raw(uint16_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration);

// private but should be used if required
uint16_t scale_raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t scaled_to_distance(uint16_t scaled);
