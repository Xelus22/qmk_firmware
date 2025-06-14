/* Copyright 2023 RephlexZero (@RephlexZero)
 * Copyright 2025 Harrison Chan (Xelus)
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
#include <stdbool.h>
#include "util.h"

#pragma once

// for saving to eeprom
typedef struct PACKED {
    // key number for DKS mapping - max 256 - limited to 10 atm anyway
    uint8_t dks_num;
    uint8_t mode;
    // calibration values
    uint16_t top_out_calibration;
    uint16_t top_out_hysteresis;
    uint16_t bottom_out_calibration;
    uint16_t bottom_out_hysteresis;
    // static actuation values
    uint16_t static_actuation_release_point; // in raw value
    uint16_t static_actuation_press_point;   // in raw value
    // dynamic actuation values
    uint16_t dynamic_activate_threshold; // in raw value
    uint16_t dynamic_press_hysteresis;   // in mm
    uint16_t dynamic_release_hysteresis; // in mm
    // dks actuation points
    uint16_t dks_top_actuation_point;
    uint16_t dks_bot_actuation_point;
    // re-use press-hysteresis and release-hysteresis for top/bottom actuation
} per_key_analog_config; /* 24 bytes */
_Static_assert(sizeof(per_key_analog_config) == 24, "Size mismatch");

// for use in RAM
typedef struct PACKED {
    /* For individual analog key data */
    uint16_t raw;
    uint16_t prev;
    uint16_t lastChangeRaw; // for use in dynamic actuation
} analog_key_t;
extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];
