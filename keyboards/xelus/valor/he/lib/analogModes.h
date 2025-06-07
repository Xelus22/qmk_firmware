#include <stdbool.h>
#include <stdint.h>
#pragma once
// create an enum of hall effect key modes
typedef enum {
    MODE_STATIC_ACTUATION = 0,
    MODE_DYNAMIC_ACTUATION,
    MODE_CONTINUOUS_DYNAMIC_ACTUATION,
    MODE_DYNAMIC_KEY_STROKE,
    // MODE_ANALOG_HID_OUTPUT,  // not implemented yet
    MODE_CALIBRATION_BOTTOM_OUT,
} analog_key_mode_t;

// run time struct for when is what
typedef struct {
    bool is_calibrating;
    bool is_calibrated;
} calibration_config_t;

bool process_mode_key(analog_key_mode_t mode, bool bPrevState, uint8_t row, uint8_t col);