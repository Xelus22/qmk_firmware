// EEPROM configuration for saving hysteresis values etc
#include "quantum/eeconfig.h"
#include "analogConfig.h"
#include <string.h>

per_key_analog_config analog_config[MATRIX_ROWS][MATRIX_COLS] = {0};

// void load_analog_config(void) {
//     // load the analog config from eeprom
//     eeconfig_read_kb_datablock(&analog_config);
// }

// void save_analog_config(void) {
//     // save the analog config to eeprom
//     eeconfig_update_kb_datablock(&analog_config);
// }

void set_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(&analog_config[row][col], config, sizeof(per_key_analog_config));
}

void get_analog_config(per_key_analog_config *config, uint8_t row, uint8_t col) {
    memcpy(config, &analog_config[row][col], sizeof(per_key_analog_config));
}

// mode
void set_analog_key_mode(uint8_t row, uint8_t col, analog_key_mode_t mode) {
    analog_config[row][col].mode = mode;
}
uint8_t get_analog_key_mode(uint8_t row, uint8_t col) {
    return analog_config[row][col].mode;
}

// calibration
void set_top_out_calibration(uint8_t row, uint8_t col, uint16_t top_out_calibration) {
    analog_config[row][col].top_out_calibration = top_out_calibration;
}
uint16_t get_top_out_calibration(uint8_t row, uint8_t col) {
    return analog_config[row][col].top_out_calibration;
}
void set_bottom_out_calibration(uint8_t row, uint8_t col, uint16_t bottom_out_calibration) {
    analog_config[row][col].bottom_out_calibration = bottom_out_calibration;
}
uint16_t get_bottom_out_calibration(uint8_t row, uint8_t col) {
    return analog_config[row][col].bottom_out_calibration;
}
void set_top_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t top_out_hysteresis) {
    analog_config[row][col].top_out_hysteresis = top_out_hysteresis;
}
uint16_t get_top_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].top_out_hysteresis;
}
void set_bot_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis) {
    analog_config[row][col].bottom_out_hysteresis = bottom_out_hysteresis;
}
uint16_t get_bot_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].bottom_out_hysteresis;
}
void set_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis) {
    analog_config[row][col].bottom_out_hysteresis = bottom_out_hysteresis;
}
uint16_t get_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].bottom_out_hysteresis;
}

// static actuation
void set_static_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].static_actuation_point = actuation_point;
}
uint16_t get_static_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].static_actuation_point;
}
void set_static_actuation_hysteresis(uint8_t row, uint8_t col, uint16_t actuation_hysteresis) {
    analog_config[row][col].static_actuation_hysteresis = actuation_hysteresis;
}
uint16_t get_static_actuation_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].static_actuation_hysteresis;
}

// dynamic actuation
void set_dynamic_activate_threshold(uint8_t row, uint8_t col, uint16_t activate_threshold) {
    analog_config[row][col].dynamic_activate_threshold = activate_threshold;
}
uint16_t get_dynamic_activate_threshold(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamic_activate_threshold;
}
void set_dynamic_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis) {
    analog_config[row][col].dynamic_press_hysteresis = press_hysteresis;
}
uint16_t get_dynamic_press_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamic_press_hysteresis;
}
void set_dynamic_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis) {
    analog_config[row][col].dynamic_release_hysteresis = release_hysteresis;
}
uint16_t get_dynamic_release_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamic_release_hysteresis;
}

// dks actuation
void set_dks_top_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].dks_top_actuation_point = actuation_point;
}
uint16_t get_dks_top_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].dks_top_actuation_point;
}
void set_dks_bot_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].dks_bot_actuation_point = actuation_point;
}
uint16_t get_dks_bot_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].dks_bot_actuation_point;
}


