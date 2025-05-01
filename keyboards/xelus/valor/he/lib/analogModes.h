
#pragma once
// create an enum of hall effect key modes
typedef enum {
    STATIC_ACTUATION = 0,
    DYNAMIC_ACTUATION,
    CONTINUOUS_DYNAMIC_ACTUATION,
    DYNAMIC_KEY_STROKE,
    ANALOG_HID_OUTPUT,
} hall_effect_key_mode_t;