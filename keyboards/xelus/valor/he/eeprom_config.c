// EEPROM configuration for saving hysteresis values etc
#include "eeprom_config.h"

per_key_analog_config analog_config[MATRIX_ROWS][MATRIX_COLS] = {0};

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(&analog_config[row][col], config, sizeof(per_key_analog_config));
}

void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(config, &analog_config[row][col], sizeof(per_key_analog_config));
}

void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_modes mode) {
    keys[row][col].mode = mode;
}

uint8_t get_analog_key_mode(uint8_t row, uint8_t col) {
    return keys[row][col].mode;
}

