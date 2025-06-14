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

#include <stdbool.h>
#include <stdint.h>
#pragma once
// create an enum of hall effect key modes
typedef enum {
    MODE_STATIC_ACTUATION = 0,
    MODE_DYNAMIC_ACTUATION,
    MODE_CONTINUOUS_DYNAMIC_ACTUATION,
    MODE_DYNAMIC_KEY_STROKE,
    // MODE_ANALOG_HID_OUTPUT,  // not implemented yet
    MODE_CALIBRATION_BOTTOM_OUT,
} analog_key_mode_t;

// run time struct for when is what
typedef struct {
    bool is_calibrating;
    bool is_calibrated;
} calibration_config_t;

bool process_mode_key(analog_key_mode_t mode, bool bPrevState, uint8_t row, uint8_t col);