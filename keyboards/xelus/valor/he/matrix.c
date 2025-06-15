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
#include "matrix.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "quantum.h"
#include <ch.h>
#include <hal.h>
#include "gpio.h"
#include "adc.h"

// libraries
#include "lib/analogkey.h"
#include "lib/analogConfig.h"
#include "adc.h"

// can be changed to 2 maybe if required for speed
#ifndef ALPHA_SHIFT
#    define ALPHA_SHIFT 4 // exponential moving average shift value
#endif

#define MUX_CHANNELS MATRIX_ROWS
#define NMUX MATRIX_COLS

STATIC_ASSERT(MATRIX_ROWS == 8, "MATRIX_ROWS must be 8");
STATIC_ASSERT(MATRIX_COLS == 9, "MATRIX_COLS must be 8");

// has to be the same
STATIC_ASSERT(NMUX == NUM_SAMPLES, "NMUX and NUMSAMPLES Size mismatch");

// global variables required for key scanning
matrix_row_t previous_matrix[MATRIX_ROWS] = {0};

void matrix_init_custom(void) {
    // init mux
    gpio_set_pin_output(B6);
    gpio_set_pin_output(B7);
    gpio_set_pin_output(B8);

    // output 000 to all pins
    gpio_write_pin_low(B6);
    gpio_write_pin_low(B7);
    gpio_write_pin_low(B8);

    // init adc
    adc_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // copy matrix to compare
    // memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     matrix_row_t current_row_value = 0;
    //     matrix_row_t row_shifter       = MATRIX_ROW_SHIFTER;
    //     for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    //         if ((row == 4 && col == 1) || (row == 7 && (col == 0 || col == 1 || col == 2 || col == 4))) {
    //             continue;
    //         }

    //         uint8_t mode         = get_analog_key_mode(row, col);
    //         bool    bPrevPressed = previous_matrix[row] & row_shifter; // check if the key was pressed before
    //         bool    bNewPressed  = process_mode_key(mode, bPrevPressed, row, col);
    //         current_row_value |= bNewPressed ? row_shifter : 0; // toggle the bit for the current key
    //     }
    //     current_matrix[row] = current_row_value;
    // }

    return false;
    // return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
