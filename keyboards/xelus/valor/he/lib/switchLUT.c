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

#include "switchLUT.h"

#include "switchLUT/duhuk_herz.h" // Include the specific switch LUT header

uint8_t selectedSwitchLUT = DEFAULT_SWITCH_LUT;

// copy of the current switch LUT in RAM
// index is the scaled value
// output is the distance in 0.0001mm increments
uint16_t switch_lut[LUT_SIZE] = {0};

void switch_lut_init(void) {
    // Initialize the switch LUT with the selected LUT
    set_switch_lut(DEFAULT_SWITCH_LUT);
}

void set_switch_lut(switch_lut_picker_t lut) {
    if (lut >= SWITCH_LUT_END) {
        lut = DEFAULT_SWITCH_LUT; // Fallback to default if invalid LUT is selected
    }

    selectedSwitchLUT = lut;

    for (switch_scaled_t i = 0; i < LUT_SIZE; i++) {
        switch (lut) {
            case SWITCH_LUT_DUHUK_HERZ:
                switch_lut[i] = calculate_duhuk_herz(i); // Calculate the value for duhuk herz switch
                break;
            default:
                break;
        }
    }
}

switch_lut_picker_t get_switch_lut(void) {
    return selectedSwitchLUT; // Return the currently selected switch LUT
}

const char *get_switch_lut_name(switch_lut_picker_t lut) {
    switch (lut) {
        case SWITCH_LUT_DUHUK_HERZ:
            return DUHUK_HERZ_NAME; // Return the name for duhuk herz switch
        default:
            return "Unknown"; // Return a default name for unknown switches
    }
}

switch_distance_t get_switch_max_distance(void) {
    switch (selectedSwitchLUT) {
        case SWITCH_LUT_DUHUK_HERZ:
            return DUHUK_HERZ_MAX_DISTANCE; // Return the max distance for duhuk herz switch
        default:
            return 0; // Return 0 or handle other cases
    }
}

switch_distance_t get_switch_distance_value(switch_scaled_t scaled_value) {
    if (scaled_value >= LUT_SIZE) {
        return 0;
    }
    return switch_lut[scaled_value]; // Return the value from the LUT based on the raw value
}

switch_scaled_t get_switch_scaled_value(switch_distance_t distance) {
    // Find the closest value in the LUT to the given distance
    for (switch_scaled_t i = 0; i < LUT_SIZE; i++) {
        // switch_lut should be strictly increasing
        if (switch_lut[i] >= distance) {
            return i; // Return the index if found
        }
    }
    return 0; // Return 0 or handle not found case
}