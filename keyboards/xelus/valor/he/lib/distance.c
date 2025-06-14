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

#include "distance.h"
#include "switchLUT.h"

// returns a raw value based on the distance and calibration values
switch_scaled_t raw_to_scaled(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Calculate the raw value based on the distance and calibration values

    // distance is in units of 0.0001mm - this is to allow for high precision
    // 1 distance unit = 0.0001mm
    // max 65535 distance units = 6.5535mm
    // we obviously cant use the full range, but its here just incase

    // need some stupid formula to convert distance to raw value
    // some weird log curve would probs work best
    if (raw < top_out_calibration) {
        return 0; // Below top out calibration
    } else if (raw > bottom_out_calibration) {
        return LUT_SIZE; // Above bottom out calibration
    } else {
        // can safely scale the value by multiplying first since my max range is about only 1000,
        // so we can multiply by LUT_SIZE and then divide by the range
        // to get the raw value in the range of 0 to LUT_SIZE
        // will not be larger than 2^16
        uint32_t calculated_value = (uint32_t)(raw - top_out_calibration) * LUT_SIZE;
        calculated_value /= (bottom_out_calibration - top_out_calibration);
        return (switch_scaled_t)calculated_value; // Return the scaled raw value
    }
}

switch_distance_t get_max_distance(void) {
    // Get the maximum distance based on the selected switch LUT
    return get_switch_max_distance(); // Return the max distance from the switch LUT
}

switch_distance_t scaled_to_distance(uint16_t scaled) {
    return get_switch_distance_value(scaled); // Get the distance from the switch LUT based on the scaled value
}

switch_distance_t raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Convert the raw value to a distance using the scale function
    uint16_t scaled_value = raw_to_scaled(raw, top_out_calibration, bottom_out_calibration);
    return scaled_to_distance(scaled_value); // Convert the scaled value to a distance
}

uint16_t distance_to_raw(switch_distance_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Convert the distance to a scaled value
    uint16_t scaled_value = get_switch_scaled_value(distance);
    uint32_t raw_value = (uint32_t)(scaled_value * (bottom_out_calibration - top_out_calibration)) / LUT_SIZE;
    return (uint16_t)(raw_value + top_out_calibration); // Return the scaled value based on the distance and calibration values
}