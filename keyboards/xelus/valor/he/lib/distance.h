#include <stdint.h>
#include "quantum.h"

// uint16_t distanceToRawMatrix[MATRIX_ROWS][MATRIX_COLS][4096]; // distance in 0.001mm units

uint16_t distance_to_raw(uint16_t distance, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
uint16_t distance_to_hysteresis(uint16_t raw, uint16_t top_calib_hysteresis, uint16_t top_out_calibration, uint16_t bottom_out_calibration);
