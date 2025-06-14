/* Copyright 2025 Harrison Chan (Xelus)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

analog_key_mode_t restore_mode[MATRIX_ROWS][MATRIX_COLS] = {0};

void calibration_sequence_top_out(void) {
    // This function is called to set the top out calibration sequence
    // It can be used to set the top out calibration value for all keys

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            // save the current mode
            restore_mode[row][col] = get_analog_key_mode(row, col);
            set_analog_key_mode(row, col, MODE_CALIBRATION); // set the mode to calibration bottom out
        }
    }

    calibrate_top_out();

    // restore the modes
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            set_analog_key_mode(row, col, restore_mode[row][col]); // restore the mode
        }
    }
}

void calibration_sequence_bottom_out(bool bStart) {
    // This function is called to set the bottom out calibration sequence
    // It can be used to set the bottom out calibration value for a specific key

    // save the current mode
    if (bStart) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int col = 0; col < MATRIX_COLS; col++) {
                restore_mode[row][col] = get_analog_key_mode(row, col);
                set_analog_key_mode(row, col, MODE_CALIBRATION); // set the mode to calibration bottom out
            }
        }
    } else {
        // restores the mode for the specific key
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int col = 0; col < MATRIX_COLS; col++) {
                if (get_analog_key_mode(row, col) == MODE_CALIBRATION) {
                    // if the mode is calibration, restore it
                    set_analog_key_mode(row, col, restore_mode[row][col]);
                }
            }
        }
    }
}

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