#include "analogkey.h"
#pragma once

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);

void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col);

void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_modes mode);

uint8_t get_analog_key_mode(uint8_t row, uint8_t col);