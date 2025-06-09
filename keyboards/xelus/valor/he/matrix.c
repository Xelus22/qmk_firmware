// matrix
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
analog_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};
matrix_row_t previous_matrix[MATRIX_ROWS]   = {0};

// process adc reading
static void process_adc_readings(matrix_row_t *prev_matrix, matrix_row_t *current_matrix, uint8_t ch) {
    uint8_t      row               = ch;
    matrix_row_t current_row_value = 0;
    matrix_row_t row_shifter       = MATRIX_ROW_SHIFTER;

    for (int mux = 0; mux < NMUX; mux++, row_shifter <<= 1) {
        uint8_t col = mux;
        // skip specific rows and columns if they are not used
        if ((row == 4 && col == 1) || (row == 7 && (col == 0 || col == 1 || col == 2 || col == 4))) {
            continue;
        }

        uint8_t mode         = get_analog_key_mode(row, col);
        bool    bPrevPressed = prev_matrix[row] & row_shifter; // check if the key was pressed before
        bool    bNewPressed  = process_mode_key(mode, bPrevPressed, row, col);
        current_row_value |= bNewPressed ? row_shifter : 0; // toggle the bit for the current key
    }

    current_matrix[row] = current_row_value; // update the current matrix row
}

void matrix_mux_change(uint8_t iteration) {
    // set mux
    switch (iteration) {
        default:
        case 0:
            // 000
            gpio_write_pin_low(B6);
            // gpio_write_pin_low(B7);
            // gpio_write_pin_low(B8);
            break;
        case 1:
            // 001
            gpio_write_pin_high(B8);
            break;
        case 2:
            // 011
            gpio_write_pin_high(B7);
            break;
        case 3:
            // 010
            gpio_write_pin_low(B8);
            break;
        case 4:
            // 110
            gpio_write_pin_high(B6);
            break;
        case 5:
            // 111
            gpio_write_pin_high(B8);
            break;
        case 6:
            // 101
            gpio_write_pin_low(B7);
            break;
        case 7:
            // 100
            gpio_write_pin_low(B8);
            break;
    }
}

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

// helper function to copy the current samples to the correct row and col
void copy_adc_samples_to_matrix(adcsample_t *samples, uint8_t row) {
    for (uint8_t col = 0; col < NUM_SAMPLES; col++) {
        // store the raw ADC sample
        keys[row][col].raw += (samples[col] - keys[row][col].raw) >> ALPHA_SHIFT; // exponential moving average
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // copy matrix to compare
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    // start ADC Conversion so that we can do processing during reads
    // only the first one we cant process
    matrix_mux_change(0);
    adc_start();            // start ADC conversion
    waitForAdcConversion(); // wait for ADC conversion to complete
    copy_adc_samples_to_matrix(adc_get_samples(), 0);

    for (uint8_t ch = 1; ch < MUX_CHANNELS; ch++) {
        matrix_mux_change(ch);
        adc_start(); // start ADC conversion

        process_adc_readings(previous_matrix, current_matrix, ch - 1);

        waitForAdcConversion(); // wait for ADC conversion to complete
        copy_adc_samples_to_matrix(adc_get_samples(), ch);
    }
    process_adc_readings(previous_matrix, current_matrix, MUX_CHANNELS - 1);

    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
