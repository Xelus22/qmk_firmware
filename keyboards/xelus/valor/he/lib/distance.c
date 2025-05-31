#include "distance.h"
#pragma once



// returns a raw value based on the distance and calibration values
uint16_t distance_to_raw(uint16_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Calculate the raw value based on the distance and calibration values

    // distance is in units of 0.0001mm - this is to allow for high precision
    // 1 distance unit = 0.0001mm
    // max 65535 distance units = 6.5535mm
    // we obviously cant use the full range, but its here just incase

    // need some stupid formula to convert distance to raw value
    // some weird log curve would probs work best
    if (distance < top_out_calibration) {
        return 0; // Below top out calibration
    } else if (distance > bottom_out_calibration) {
        return UINT16_MAX; // Above bottom out calibration
    } else {
        return (distance - top_out_calibration) * UINT16_MAX / (bottom_out_calibration - top_out_calibration);
    }
}

// returns a hysteresis value based on the distance and calibration values
uint16_t distance_to_hysteresis(uint16_t raw, uint16_t top_calib_hysteresis, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Calculate the hysteresis value based on the distance and calibration values
    // Hysteresis is the difference between the top and bottom out calibration values
    // scaled by the distance

    if (raw < top_out_calibration - top_calib_hysteresis || raw > bottom_out_calibration) {
        return 0; // No hysteresis if outside calibration range
    }

    // temp
    return 1000;
}