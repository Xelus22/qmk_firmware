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
    analog_config[row][col].topOutCalibration = top_out_calibration;
}
uint16_t get_top_out_calibration(uint8_t row, uint8_t col) {
    return analog_config[row][col].topOutCalibration;
}
void set_bottom_out_calibration(uint8_t row, uint8_t col, uint16_t bottom_out_calibration) {
    analog_config[row][col].bottomOutCalibration = bottom_out_calibration;
}
uint16_t get_bottom_out_calibration(uint8_t row, uint8_t col) {
    return analog_config[row][col].bottomOutCalibration;
}
void set_top_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t top_out_hysteresis) {
    analog_config[row][col].topOutHysteresis = top_out_hysteresis;
}
uint16_t get_top_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].topOutHysteresis;
}
void set_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col, uint16_t bottom_out_hysteresis) {
    analog_config[row][col].bottomOutHysteresis = bottom_out_hysteresis;
}
uint16_t get_bottom_out_calibration_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].bottomOutHysteresis;
}

// static actuation
void set_static_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].staticActuationPoint = actuation_point;
}
uint16_t get_static_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].staticActuationPoint;
}
void set_static_actuation_hysteresis(uint8_t row, uint8_t col, uint16_t actuation_hysteresis) {
    analog_config[row][col].staticActuationHysteresis = actuation_hysteresis;
}
uint16_t get_static_actuation_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].staticActuationHysteresis;
}

// dynamic actuation
void set_dynamic_activate_threshold(uint8_t row, uint8_t col, uint16_t activate_threshold) {
    analog_config[row][col].dynamicActivateThreshold = activate_threshold;
}
uint16_t get_dynamic_activate_threshold(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamicActivateThreshold;
}
void set_dynamic_press_hysteresis(uint8_t row, uint8_t col, uint16_t press_hysteresis) {
    analog_config[row][col].dynamicPressHysteresis = press_hysteresis;
}
uint16_t get_dynamic_press_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamicPressHysteresis;
}
void set_dynamic_release_hysteresis(uint8_t row, uint8_t col, uint16_t release_hysteresis) {
    analog_config[row][col].dynamicReleaseHysteresis = release_hysteresis;
}
uint16_t get_dynamic_release_hysteresis(uint8_t row, uint8_t col) {
    return analog_config[row][col].dynamicReleaseHysteresis;
}

// dks actuation
void set_dks_top_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].dksTopActuationPoint = actuation_point;
}
uint16_t get_dks_top_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].dksTopActuationPoint;
}
void set_dks_bot_actuation_point(uint8_t row, uint8_t col, uint16_t actuation_point) {
    analog_config[row][col].dksBotActuationPoint = actuation_point;
}
uint16_t get_dks_bot_actuation_point(uint8_t row, uint8_t col) {
    return analog_config[row][col].dksBotActuationPoint;
}


