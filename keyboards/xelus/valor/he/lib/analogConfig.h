#include "analogkey.h"
#include "analogModes.h"
#pragma once

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);
void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);

void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode);
uint8_t get_analog_key_mode(uint8_t row, uint8_t col);

void set_analog_key_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point);
uint16_t get_analog_key_actuation_point(uint8_t row, uint8_t col);

void set_analog_key_press_sensitivity(uint8_t row, uint8_t col, uint16_t press_sensitivity);
uint16_t get_analog_key_press_sensitivity(uint8_t row, uint8_t col);

void set_analog_key_release_sensitivity(uint8_t row, uint8_t col, uint16_t release_sensitivity);
uint16_t get_analog_key_release_sensitivity(uint8_t row, uint8_t col);

void set_analog_key_actuation_hysteresis(uint8_t row, uint8_t col, uint16_t actuation_hysteresis);
uint16_t get_analog_key_actuation_hysteresis(uint8_t row, uint8_t col);

void set_analog_key_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis);
uint16_t get_analog_key_press_hysteresis(uint8_t row, uint8_t col);

void set_analog_key_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis);
uint16_t get_analog_key_release_hysteresis(uint8_t row, uint8_t col);
