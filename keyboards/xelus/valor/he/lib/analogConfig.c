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

// EEPROM configuration for saving hysteresis values etc
#include "quantum/eeconfig.h"
#include "analogConfig.h"
#include "keymodes/dks.h"
#include "switchLUT.h"
#include "distance.h"
#include <string.h>

analog_config_t analog_config = {0};

void analog_config_init(void) {
    // Initialize the analog configuration structure
    memset(&analog_config, 0, sizeof(analog_config_t));
}

void reset_analog_config(void) {
    // set the selected switch LUT to default
    switch_lut_init();
    dks_init();

    // Reset all analog configurations to default values
    reset_calibration();
    reset_static_actuation();
    reset_dynamic_actuation();
    reset_dks_actuation();
    reset_analog_key_mode();
}

void reset_analog_key_mode(void) {
    // Reset all analog key modes to default
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            set_analog_key_mode(row, col, DEFAULT_ANALOG_MODE);
        }
    }
}

void reset_calibration(void) {
    // Reset all calibration values to default
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            set_top_out_calibration(row, col, DEFAULT_TOP_OUT_CALIBRATION);
            set_top_out_calibration_hysteresis(row, col, DEFAULT_TOP_OUT_CALIBRATION_HYSTERESIS);
            set_bottom_out_calibration(row, col, DEFAULT_BOTTOM_OUT_CALIBRATION);
            set_bottom_out_calibration_hysteresis(row, col, DEFAULT_BOTTOM_OUT_CALIBRATION_HYSTERESIS);
        }
    }
}

void reset_static_actuation(void) {
    // Reset all static actuation values to default
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t act_release_point = 2500;
            uint16_t act_press_point   = 2600;
            set_static_actuation_press_point(row, col, act_press_point);
            set_static_actuation_release_point(row, col, act_release_point);
        }
    }
}

void reset_dynamic_actuation(void) {
    // Reset all dynamic actuation values to default
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint16_t act_threshold = distance_to_raw(DEFAULT_DYNAMIC_ACTIVATE_THRESHOLD_MM, DEFAULT_TOP_OUT_CALIBRATION, DEFAULT_BOTTOM_OUT_CALIBRATION);
            set_dynamic_activate_threshold(row, col, act_threshold);
            set_dynamic_press_hysteresis(row, col, DEFAULT_DYNAMIC_PRESS_HYSTERESIS_MM);
            set_dynamic_release_hysteresis(row, col, DEFAULT_DYNAMIC_RELEASE_HYSTERESIS_MM);
        }
    }
}

void reset_dks_actuation(void) {
    // Reset all DKS actuation points to default
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            set_dks_num(row, col, 255); // No DKS by default
            set_dks_top_actuation_point(row, col, DEFAULT_DKS_TOP_ACTUATION_POINT);
            set_dks_bot_actuation_point(row, col, DEFAULT_DKS_BOT_ACTUATION_POINT);
        }
    }
}

void save_config_to_eeprom(void) {
    // Save the analog configuration to EEPROM
    eeconfig_update_kb_datablock(&analog_config, 0, EECONFIG_KB_DATA_SIZE);
}

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(&(analog_config.key_config[row][col]), config, sizeof(per_key_analog_config) * MATRIX_ROWS * MATRIX_COLS);
}

void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(config, &(analog_config.key_config[row][col]), sizeof(per_key_analog_config) * MATRIX_ROWS * MATRIX_COLS);
}

// mode
void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode) {
    analog_config.key_config[row][col].mode = mode;
}
uint8_t get_analog_key_mode(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].mode;
}

// calibration
void set_top_out_calibration(uint8_t row, uint8_t col, uint16_t top_out_calibration) {
    analog_config.key_config[row][col].top_out_calibration = top_out_calibration;
}
uint16_t get_top_out_calibration(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].top_out_calibration;
}
void set_bottom_out_calibration(uint8_t row, uint8_t col, uint16_t bottom_out_calibration) {
    analog_config.key_config[row][col].bottom_out_calibration = bottom_out_calibration;
}
uint16_t get_bottom_out_calibration(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].bottom_out_calibration;
}
void set_top_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t top_out_hysteresis) {
    analog_config.key_config[row][col].top_out_hysteresis = top_out_hysteresis;
}
uint16_t get_top_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].top_out_hysteresis;
}
void set_bot_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis) {
    analog_config.key_config[row][col].bottom_out_hysteresis = bottom_out_hysteresis;
}
uint16_t get_bot_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].bottom_out_hysteresis;
}
void set_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis) {
    analog_config.key_config[row][col].bottom_out_hysteresis = bottom_out_hysteresis;
}
uint16_t get_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].bottom_out_hysteresis;
}

// static actuation
void set_static_actuation_release_point(uint8_t row, uint8_t col, uint16_t release_point) {
    analog_config.key_config[row][col].static_actuation_release_point = release_point;
}
uint16_t get_static_actuation_release_point(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].static_actuation_release_point;
}
void set_static_actuation_press_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config.key_config[row][col].static_actuation_press_point = actuation_point;
}
uint16_t get_static_actuation_press_point(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].static_actuation_press_point;
}

// dynamic actuation
void set_dynamic_activate_threshold(uint8_t row, uint8_t col, uint16_t activate_threshold) {
    analog_config.key_config[row][col].dynamic_activate_threshold = activate_threshold;
}
uint16_t get_dynamic_activate_threshold(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dynamic_activate_threshold;
}
void set_dynamic_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis) {
    analog_config.key_config[row][col].dynamic_press_hysteresis = press_hysteresis;
}
uint16_t get_dynamic_press_hysteresis(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dynamic_press_hysteresis;
}
void set_dynamic_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis) {
    analog_config.key_config[row][col].dynamic_release_hysteresis = release_hysteresis;
}
uint16_t get_dynamic_release_hysteresis(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dynamic_release_hysteresis;
}

// dks actuation
void set_dks_top_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config.key_config[row][col].dks_top_actuation_point = actuation_point;
}
uint16_t get_dks_top_actuation_point(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dks_top_actuation_point;
}
void set_dks_bot_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config.key_config[row][col].dks_bot_actuation_point = actuation_point;
}
uint16_t get_dks_bot_actuation_point(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dks_bot_actuation_point;
}

void set_dks_num(uint8_t row, uint8_t col, uint8_t dks_num) {
    analog_config.key_config[row][col].dks_num = dks_num;
}
uint8_t get_dks_num(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].dks_num;
}
