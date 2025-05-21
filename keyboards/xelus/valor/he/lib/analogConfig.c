// EEPROM configuration for saving hysteresis values etc
#include "analogConfig.h"
#include <string.h>

per_key_analog_config analog_config[MATRIX_ROWS][MATRIX_COLS] = {0};

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(&analog_config[row][col], config, sizeof(per_key_analog_config));
}

void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(config, &analog_config[row][col], sizeof(per_key_analog_config));
}

void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode) {
    analog_config[row][col].mode = mode;
}

uint8_t get_analog_key_mode(uint8_t row, uint8_t col) {
    return analog_config[row][col].mode;
}

void set_analog_key_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].actuation_point = actuation_point;
}
uint16_t get_analog_key_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].actuation_point;
}

void set_analog_key_press_sensitivity(uint8_t row, uint8_t col, uint16_t press_sensitivity) {
    analog_config[row][col].press_sensitivity = press_sensitivity;
}
uint16_t get_analog_key_press_sensitivity(uint8_t row, uint8_t col) {
    return analog_config[row][col].press_sensitivity;
}

void set_analog_key_release_sensitivity(uint8_t row, uint8_t col, uint16_t release_sensitivity) {
    analog_config[row][col].release_sensitivity = release_sensitivity;
}
uint16_t get_analog_key_release_sensitivity(uint8_t row, uint8_t col) {
    return analog_config[row][col].release_sensitivity;
}

void set_analog_key_actuation_hysteresis(uint8_t row, uint8_t col, uint16_t actuation_hysteresis) {
    analog_config[row][col].actuation_hysteresis = actuation_hysteresis;
}
uint16_t get_analog_key_actuation_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].actuation_hysteresis;
}

void set_analog_key_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis) {
    analog_config[row][col].press_hysteresis = press_hysteresis;
}
uint16_t get_analog_key_press_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].press_hysteresis;
}

void set_analog_key_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis) {
    analog_config[row][col].release_hysteresis = release_hysteresis;
}
uint16_t get_analog_key_release_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].release_hysteresis;
}
