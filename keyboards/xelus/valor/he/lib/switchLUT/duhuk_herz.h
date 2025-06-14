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

// LUT for duhuk herz switch

#pragma once

#include <stdint.h>
#include <math.h>
#include "switchLUT.h"
#include "progmem.h"

#define FUNC(x) (117.39 * log(0.0001215 * x) - 110.43)

// 1 distance unit = 0.0001mm
// 1000 distance units = 0.1mm
// 10000 distance units = 1mm
// 35000 distance units = 3.5mm

// basically non-linear mapping 0 - 1024 -> 0mm - 3.3mm

const uint16_t calculate_duhuk_herz(uint16_t raw_value) {
    // 0 raw value = 0 distance
    // 10000 raw value = 1mm distance
    // Calculate the value based on the raw value using the function
    // The function is derived from the characteristics of the duhuk herz switch
    return (uint16_t)(FUNC(raw_value));
}
