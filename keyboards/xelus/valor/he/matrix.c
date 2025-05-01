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
#include "lib/eeprom_config.h"

// mux
// B6, B7, B8
// SEL 2,1,0

#define MUX_CHANNELS MATRIX_COLS
#define NMUX MATRIX_ROWS

analog_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

matrix_row_t previous_matrix[MATRIX_ROWS];

// process adc reading
static void process_adc_readings(uint8_t ch, const ADCManager *snapshot) {
    for (int mux = 0; mux < NMUX; mux++) {
        analog_key_t *key = &keys[mux][ch];
        key->raw          = getADCSample(snapshot, mux);
        // key->value =  use LUT to convert raw to value
        // LUT for value to distance
        uint8_t mode = get_analog_key_mode(mux, ch);
        switch (mode) {
            case dynamic_actuation:
                break;
            case continuous_dynamic_actuation:
                break;
            case static_actuation:
                break;
            case flashing:
            default:
                bootloader_jump();
                break;
        }
    }
}

// grey code
// 000
// 001
// 011
// 010
// 110
// 111
// 101
// 100

void matrix_mux_change(uint8_t iteration) {
    // set mux
    switch (iteration) {
        default:
        case 0:
            // 000
            gpio_write_pin_low(B6);
            gpio_write_pin_low(B7);
            gpio_write_pin_low(B8);
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
    gpio_set_pin_output_push_pull(B6);
    gpio_set_pin_output_push_pull(B7);
    gpio_set_pin_output_push_pull(B8);

    // output 000 to all pins
    gpio_write_pin_low(B6);
    gpio_write_pin_low(B7);
    gpio_write_pin_low(B8);

    // init adc
    adc_init();

    //
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // copy matrix to compare
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));

    // do first ADC scan (3 keys)

    // start adc read
    // wait for ADC conversion

    // loop through each bundle of keys
    for (uint8_t ch = 0; ch < MUX_CHANNELS; ch++) {
        matrix_mux_change(ch);

        // start adc read
        // process previous adc read
        process_adc_readings(ch, getAdcManagerSnapshot());
        // wait for ADC conversion
    }

    // process last adc read

    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
