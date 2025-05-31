#include "calibration.h"
#include "analogConfig.h"
#include "analogkey.h"
#include "quantum.h"

#ifndef NUM_CALIBRATION_SAMPLES
#    define NUM_CALIBRATION_SAMPLES 100
#endif

#ifndef TOP_OUT_CALIBRATION_THRESHOLD
#    define TOP_OUT_CALIBRATION_THRESHOLD 2300 // threshold for top out calibration, adjust as needed
#endif

#ifndef BOTTOM_OUT_CALIBRATION_THRESHOLD
#    define BOTTOM_OUT_CALIBRATION_THRESHOLD 2900 // threshold for bottom out calibration, adjust as needed
#endif

void calibrate_top_out(void) {
    // read matrix a few times and then average the values

    // should be fast enough. at an 8khz scan rate.
    // 100 * (9 rows * 8 cols) = 7200, 7200 * 128us = 921.6ms required
    // if its too slow you change the scan to lower the number of samples
    // or you can use the above EMA method which may be less accurate but faster
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            // sum should hold the total of all samples
            // will never go above 2^32-1 anyway... right???
            uint32_t sum = 0;
            uint16_t min = UINT16_MAX; // minimum value for the key, used to check if the key is pressed
            uint16_t max = 0;          // maximum value for the key, used to check if the key is pressed
            for (int i = 0; i < NUM_CALIBRATION_SAMPLES; i++) {
                matrix_scan();
                sum += keys[row][col].raw;

                min = MIN(min, keys[row][col].raw);
                max = MAX(max, keys[row][col].raw);
            }
            // calculate the average
            uint16_t average = sum / NUM_CALIBRATION_SAMPLES;

            // check if the calibration is less than the threshold
            average = MIN(average, TOP_OUT_CALIBRATION_THRESHOLD);
            set_top_out_calibration(row, col, average);

            // noise from experimentation seems to be pretty much the seems
            // consistent despite top or bottom out values
            set_top_out_calibration_hysteresis(row, col, (max - min) / 2); // set the hysteresis to half the difference between max and min
            set_bottom_out_calibration_hysteresis(row, col, (max - min) / 2);
        }
    }
}

// calibrate bottom out
void calibrate_bottom_out(uint8_t row, uint8_t col) {
    // check if it is the maximum number found
    // assumes that further pressed (magnet closer to sensor), mean larger raw value
    // must be larger than the threshold to be considered a valid bottom out calibration
    uint32_t calibration_value = MAX(keys[row][col].raw, BOTTOM_OUT_CALIBRATION_THRESHOLD);

    // since we're always getting the max we want to get the "average" rather than the abs max
    set_bottom_out_calibration(row, col, calibration_value - (get_bottom_out_calibration_hysteresis(row, col) + 1) / 2);
}