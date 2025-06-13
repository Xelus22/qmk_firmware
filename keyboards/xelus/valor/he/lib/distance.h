#include <stdint.h>
#include "quantum.h"

#pragma once

uint16_t raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t distance_to_raw(uint16_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration);

// private but should be used if required
uint16_t scale_raw_to_distance(uint16_t raw, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t scaled_to_distance(uint16_t scaled);
