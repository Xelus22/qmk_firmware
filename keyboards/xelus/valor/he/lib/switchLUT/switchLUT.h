#pragma once

#include <stdint.h>

#define LUT_SIZE 1024 // Size of the LUT, adjust as necessary

typedef enum {
    SWITCH_LUT_DUHUK_HERZ,
    // add in here
    SWITCH_LUT_END
} switch_lut_picker_t;

void set_switch_lut(switch_lut_picker_t lut);

// get the pointer to the switch LUT
uint16_t *get_switch_lut(switch_lut_picker_t lut);