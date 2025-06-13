// EEPROM configuration for saving hysteresis values etc
#include "quantum/eeconfig.h"
#include "analogConfig.h"
#include <string.h>

analog_config_t analog_config = {0};

void analog_config_init(void) {
    // Initialize the analog configuration structure
    memset(&analog_config, 0, sizeof(analog_config_t));
}

void reset_analog_config(void) {
    // Reset all analog configurations to default values
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // Set default values using functions
            set_dks_num(row, col, 255); // No DKS by default
            set_analog_key_mode(row, col, DEFAULT_ANALOG_MODE);

            // Set default calibration values
            set_top_out_calibration(row, col, DEFAULT_TOP_OUT_CALIBRATION);
            set_top_out_calibration_hysteresis(row, col, DEFAULT_TOP_OUT_CALIBRATION_HYSTERESIS);
            set_bottom_out_calibration(row, col, DEFAULT_BOTTOM_OUT_CALIBRATION);
            set_bottom_out_calibration_hysteresis(row, col, DEFAULT_BOTTOM_OUT_CALIBRATION_HYSTERESIS);

            // Set static actuation defaults
            set_static_actuation_release_point(row, col, DEFAULT_STATIC_RELEASE_POINT);
            set_static_actuation_press_point(row, col, DEFAULT_STATIC_PRESS_POINT);

            // Set dynamic actuation defaults
            set_dynamic_activate_threshold(row, col, DEFAULT_DYNAMIC_ACTIVATE_THRESHOLD);
            set_dynamic_press_hysteresis(row, col, DEFAULT_DYNAMIC_PRESS_HYSTERESIS);
            set_dynamic_release_hysteresis(row, col, DEFAULT_DYNAMIC_PRESS_HYSTERESIS);

            // Set DKS actuation points
            set_dks_top_actuation_point(row, col, DEFAULT_DKS_TOP_ACTUATION_POINT);
            set_dks_bot_actuation_point(row, col, DEFAULT_DKS_TOP_ACTUATION_POINT);
        }
    }
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
void set_static_actuation_release_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config.key_config[row][col].static_actuation_release_point = actuation_point;
}
uint16_t get_static_actuation_release_point(uint8_t row, uint8_t col) {
    return analog_config.key_config[row][col].static_actuation_release_point;
}
void set_static_actuation_press_point(uint8_t row, uint8_t col, uint16_t actuation_hysteresis) {
    analog_config.key_config[row][col].static_actuation_press_point = actuation_hysteresis;
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
