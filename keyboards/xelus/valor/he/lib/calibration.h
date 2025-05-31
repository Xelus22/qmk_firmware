#include <stdint.h>

#pragma once

// calibrate top out
// aka noise floor
void calibrate_top_out(void);
// calibrate bottom out
void calibrate_bottom_out(uint8_t row, uint8_t col);
