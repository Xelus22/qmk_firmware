#pragma once

#include <stdint.h>

#define LUT_SIZE 1024 // Size of the LUT, adjust as necessary

#define DISTANCE_1MM_MULTIPLIER 10000 // 1mm = 10000 distance units

typedef enum {
    SWITCH_LUT_DUHUK_HERZ,
    // add in here
    SWITCH_LUT_END
} switch_lut_picker_t;

#ifndef DEFAULT_SWITCH_LUT
#define DEFAULT_SWITCH_LUT SWITCH_LUT_DUHUK_HERZ // Default switch LUT
#endif

void set_switch_lut(switch_lut_picker_t lut);

// get the pointer to the switch LUT
uint16_t get_switch_distance_value(uint16_t raw_value);

uint16_t get_switch_scaled_value(uint16_t distance);