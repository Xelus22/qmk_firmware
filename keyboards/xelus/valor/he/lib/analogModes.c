#include "analogModes.h"
#include "analogkey.h"

// get mode for a key
uint8_t get_mode(uint8_t row, uint8_t col) {
    return analog_config[row][col].mode;
}

// set mode for a key
void set_mode(uint8_t row, uint8_t col, uint8_t mode) {
    analog_config[row][col].mode = mode;
}

