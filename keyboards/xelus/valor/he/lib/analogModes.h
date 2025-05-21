#include <stdbool.h>
#pragma once
// create an enum of hall effect key modes
typedef enum {
    MODE_STATIC_ACTUATION = 0,
    MODE_DYNAMIC_ACTUATION,
    MODE_CONTINUOUS_DYNAMIC_ACTUATION,
    MODE_DYNAMIC_KEY_STROKE,
    MODE_ANALOG_HID_OUTPUT,
    MODE_CALIBRATION
} analog_key_mode_t;

// run time struct for when is what
typedef struct {
    bool is_calibrating;
    bool is_calibrated;
} anlog_config_t;

void process_mode_key(analog_key_mode_t mode, uint8_t row, uint8_t col);