#include "analogkey.h"
#include "analogModes.h"
#pragma once

extern per_key_analog_config analog_config[MATRIX_ROWS][MATRIX_COLS];

// void load_analog_config(void);
// void save_analog_config(void);

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);
void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);

void    set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode);
uint8_t get_analog_key_mode(uint8_t row, uint8_t col);

//calibration
void     set_top_out_calibration(uint8_t row, uint8_t col, uint16_t top_out_calibration);
uint16_t get_top_out_calibration(uint8_t row, uint8_t col);
void     set_bottom_out_calibration(uint8_t row, uint8_t col, uint16_t bottom_out_calibration);
uint16_t get_bottom_out_calibration(uint8_t row, uint8_t col);
void     set_top_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t top_out_hysteresis);
uint16_t get_top_out_calibration_hysteresis(uint8_t row, uint8_t col);
void     set_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis);
uint16_t get_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col);

// static actuation
void     set_static_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point);
uint16_t get_static_actuation_point(uint8_t row, uint8_t col);
void     set_static_actuation_hysteresis(uint8_t row, uint8_t col, uint16_t actuation_hysteresis);
uint16_t get_static_actuation_hysteresis(uint8_t row, uint8_t col);

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

