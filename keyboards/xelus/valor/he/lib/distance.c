#include "distance.h"
#include "switchLUT/switchLUT.h"

// returns a raw value based on the distance and calibration values
uint16_t scale_raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Calculate the raw value based on the distance and calibration values

    // distance is in units of 0.0001mm - this is to allow for high precision
    // 1 distance unit = 0.0001mm
    // max 65535 distance units = 6.5535mm
    // we obviously cant use the full range, but its here just incase

    // need some stupid formula to convert distance to raw value
    // some weird log curve would probs work best
    if (raw < top_out_calibration) {
        return 0; // Below top out calibration
    } else if (raw > bottom_out_calibration) {
        return UINT16_MAX; // Above bottom out calibration
    } else {
        // can safely scale the value by multiplying first since my max range is about only 1000,
        // so we can multiply by UINT16_MAX and then divide by the range
        // to get the raw value in the range of 0 to UINT16_MAX
        // will not be larger than 2^16
        uint32_t calculated_value = (uint32_t)(raw - top_out_calibration) * UINT16_MAX;
        calculated_value /= (bottom_out_calibration - top_out_calibration);
        return (uint16_t)calculated_value; // Return the scaled raw value
    }
}

uint16_t scaled_to_distance(uint16_t scaled) {
    return get_switch_distance_value(scaled); // Get the distance from the switch LUT based on the scaled value
}

uint16_t raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Convert the raw value to a distance using the scale function
    uint16_t scaled_value = scale_raw_to_distance(raw, top_out_calibration, bottom_out_calibration);
    return scaled_to_distance(scaled_value); // Convert the scaled value to a distance
}

uint16_t distance_to_raw(uint16_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration) {
    // Convert the distance to a scaled value
    uint16_t scaled_value = get_switch_scaled_value(distance);
    uint32_t raw_value = (uint32_t)(scaled_value * (bottom_out_calibration - top_out_calibration)) / UINT16_MAX;
    return (uint16_t)(raw_value + top_out_calibration); // Return the scaled value based on the distance and calibration values
}