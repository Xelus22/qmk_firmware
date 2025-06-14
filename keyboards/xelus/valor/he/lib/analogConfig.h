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

#include "analogkey.h"
#include "analogModes.h"
#include "keymodes/dks.h"
#include "switchLUT.h"

#pragma once

#ifndef DEFAULT_DKS_NUM
#    define DEFAULT_DKS_NUM 255 // No DKS by default
#endif

#ifndef DEFAULT_ANALOG_MODE
#    define DEFAULT_ANALOG_MODE MODE_STATIC_ACTUATION // Default mode is static actuation
#endif

#ifndef DEFAULT_TOP_OUT_CALIBRATION
#    define DEFAULT_TOP_OUT_CALIBRATION 2300 // Default top out calibration value
#endif

#ifndef DEFAULT_TOP_OUT_CALIBRATION_HYSTERESIS
#    define DEFAULT_TOP_OUT_CALIBRATION_HYSTERESIS 50 // Default top out calibration hysteresis
#endif

#ifndef DEFAULT_BOTTOM_OUT_CALIBRATION
#    define DEFAULT_BOTTOM_OUT_CALIBRATION 2900 // Default bottom out calibration value
#endif

#ifndef DEFAULT_BOTTOM_OUT_CALIBRATION_HYSTERESIS
#    define DEFAULT_BOTTOM_OUT_CALIBRATION_HYSTERESIS 50 // Default bottom out calibration hysteresis
#endif

#ifndef DEFAULT_STATIC_RELEASE_POINT_MM
#    define DEFAULT_STATIC_RELEASE_POINT_MM (1.5 * DISTANCE_MM_MULTIPLIER)  // Default static actuation point
#endif

#ifndef DEFAULT_STATIC_PRESS_POINT_MM
#    define DEFAULT_STATIC_PRESS_POINT_MM (1.6 * DISTANCE_MM_MULTIPLIER) // Default static actuation point
#endif

#ifndef DEFAULT_DYNAMIC_ACTIVATE_THRESHOLD_MM
#    define DEFAULT_DYNAMIC_ACTIVATE_THRESHOLD_MM (0.5 * DISTANCE_MM_MULTIPLIER) // Default dynamic activate threshold
#endif

#ifndef DEFAULT_DYNAMIC_PRESS_HYSTERESIS_MM
#    define DEFAULT_DYNAMIC_PRESS_HYSTERESIS_MM (0.2 * DISTANCE_MM_MULTIPLIER) // Default dynamic press hysteresis
#endif

#ifndef DEFAULT_DYNAMIC_RELEASE_HYSTERESIS_MM
#    define DEFAULT_DYNAMIC_RELEASE_HYSTERESIS_MM (0.2 * DISTANCE_MM_MULTIPLIER) // Default dynamic release hysteresis
#endif

#ifndef DEFAULT_DKS_TOP_ACTUATION_POINT
#    define DEFAULT_DKS_TOP_ACTUATION_POINT 2500 // Default DKS top actuation point
#endif

#ifndef DEFAULT_DKS_BOT_ACTUATION_POINT
#    define DEFAULT_DKS_BOT_ACTUATION_POINT 2900 // Default DKS bottom actuation point
#endif

typedef struct PACKED {
    per_key_analog_config key_config[MATRIX_ROWS][MATRIX_COLS]; // per key analog configuration
    dks_key_t             dks_keys[MAX_DKS_KEYS];               // DKS key configurations
    uint8_t               selectedSwitchLUT;                    // selected switch LUT for analog keys
} analog_config_t;

STATIC_ASSERT(sizeof(analog_config_t) == EECONFIG_KB_DATA_SIZE, "Size mismatch for analog_config_t");

extern analog_config_t analog_config;

void analog_config_init(void);
void reset_analog_config(void);

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);
void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);

void    set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode);
uint8_t get_analog_key_mode(uint8_t row, uint8_t col);

// calibration
void     set_top_out_calibration(uint8_t row, uint8_t col, uint16_t top_out_calibration);
uint16_t get_top_out_calibration(uint8_t row, uint8_t col);
void     set_bottom_out_calibration(uint8_t row, uint8_t col, uint16_t bottom_out_calibration);
uint16_t get_bottom_out_calibration(uint8_t row, uint8_t col);
void     set_top_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t top_out_hysteresis);
uint16_t get_top_out_calibration_hysteresis(uint8_t row, uint8_t col);
void     set_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis);
uint16_t get_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col);

// static actuation
void     set_static_actuation_release_point(uint8_t row, uint8_t col, uint16_t actuation_point);
uint16_t get_static_actuation_release_point(uint8_t row, uint8_t col);
void     set_static_actuation_press_point(uint8_t row, uint8_t col, uint16_t actuation_hysteresis);
uint16_t get_static_actuation_press_point(uint8_t row, uint8_t col);

// dynamic actuation
void     set_dynamic_activate_threshold(uint8_t row, uint8_t col, uint16_t activate_threshold);
uint16_t get_dynamic_activate_threshold(uint8_t row, uint8_t col);
void     set_dynamic_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis);
uint16_t get_dynamic_press_hysteresis(uint8_t row, uint8_t col);
void     set_dynamic_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis);
uint16_t get_dynamic_release_hysteresis(uint8_t row, uint8_t col);

// dks actuation
void     set_dks_top_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point);
uint16_t get_dks_top_actuation_point(uint8_t row, uint8_t col);
void     set_dks_bot_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point);
uint16_t get_dks_bot_actuation_point(uint8_t row, uint8_t col);

// set dks number
void    set_dks_num(uint8_t row, uint8_t col, uint8_t dks_num);
uint8_t get_dks_num(uint8_t row, uint8_t col);
