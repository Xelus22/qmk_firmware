#include "analogModes.h"
#include "analogkey.h"

// settings for when to do calibration and what not


// get mode for a key
uint8_t get_mode(uint8_t row, uint8_t col) {
    return analog_config[row][col].mode;
}

// set mode for a key
void set_mode(uint8_t row, uint8_t col, uint8_t mode) {
    analog_config[row][col].mode = mode;
}

bool process_mode_key(analog_key_mode_t mode, uint8_t row, uint8_t col) {
    switch (mode) {
        case MODE_STATIC_ACTUATION:
            // process static actuation
            break;
        case MODE_DYNAMIC_ACTUATION:
            // process dynamic actuation
            break;
        case MODE_CONTINUOUS_DYNAMIC_ACTUATION:
            // process continuous dynamic actuation
            break;
        case MODE_DYNAMIC_KEY_STROKE:
            // process dynamic key stroke
            break;
        case MODE_ANALOG_HID_OUTPUT:
            // process analog HID output
            break;
        case MODE_CALIBRATION:
            // process calibration
            break;
        default:
            break;
    }

    return false; // key not pressed
}