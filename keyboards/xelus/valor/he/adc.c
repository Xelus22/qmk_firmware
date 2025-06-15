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

#include "adc.h"
#include "print.h"
#include "stm32f405xx.h"
#include "adc_multi.h"
#include "quantum.h"

#ifndef ALPHA_SHIFT
#    define ALPHA_SHIFT 4 // exponential moving average shift value
#endif

analog_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};
adcsample_t  adcSamples[NUM_SAMPLES]        = {0}; // Buffer for ADC samples
uint8_t      row                            = 0;   // Current row being processed

void matrix_mux_change(uint8_t iteration) {
    // set mux
    switch (iteration) {
        default:
        case 0:
            // 000
            gpio_write_pin_low(B6);
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

__attribute__((used)) void adcCompleteCallback(ADCDriver *adcp) {
    (void)adcp; // Unused parameter
    // Copy the samples to the global buffer
    osalSysLockFromISR();
    for (uint8_t col = 0; col < NUM_SAMPLES; col++) {
        // store the raw ADC sample
        keys[row][col].raw += (adcSamples[col] - keys[row][col].raw) >> ALPHA_SHIFT; // exponential moving average
    }
    row = (row + 1) % MATRIX_ROWS;
    matrix_mux_change(row);
    osalSysUnlockFromISR();
}

__attribute__((used)) void adcErrorCallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp; // Unused parameter
    osalSysLockFromISR();
    switch (err) {
        case ADC_ERR_DMAFAILURE:
            uprintf("ADC ERROR: DMA failure.\n");
            break;
        case ADC_ERR_OVERFLOW:
            uprintf("ADC ERROR: Overflow.\n");
            break;
        case ADC_ERR_AWD:
            uprintf("ADC ERROR: Watchdog 1 triggered.\n");
            break;
        default:
            uprintf("ADC ERROR: Unknown error.\n");
            break;
    }
    osalSysUnlockFromISR();
}

// turn off clang-format
// clang-format off
// static const ADCConversionGroup adc1Config = {
//     .circular     = false,
//     .num_channels = ADC_NUM_CHANNELS,
//     .end_cb       = adcCompleteCallback,
//     .error_cb     = adcErrorCallback,
//     .cr1 = ADC_CR1_SCAN,
//     .cr2 = ADC_CR2_SWSTART | ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_ADON | ADC_CR2_CONT,
//     .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
//              ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
//              ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
//     .smpr2 = ADC_SMPR2_SMP_AN4(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN6(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN7(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
//     .sqr1 = 0U,
//     .sqr2 = ADC_SQR2_SQ7_N(ADC_CHANNEL_IN0) |
//             ADC_SQR2_SQ8_N(ADC_CHANNEL_IN1) |
//             ADC_SQR2_SQ9_N(ADC_CHANNEL_IN2),
//     .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
//             ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
//             ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7) |
//             ADC_SQR3_SQ4_N(ADC_CHANNEL_IN11) |
//             ADC_SQR3_SQ5_N(ADC_CHANNEL_IN14) |
//             ADC_SQR3_SQ6_N(ADC_CHANNEL_IN15),
// };

static const ADCConversionGroup adc1Config = {
    .circular     = true,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = 0U,
    .cr2 = ADC_CR2_SWSTART,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN4(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN6(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN7(ADC_SAMPLE_3),
    .sqr1 = ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7)
};

static const ADCConversionGroup adc2Config = {
    .circular     = true,
    .num_channels = 0U,
    .end_cb       = NULL,
    .error_cb     = NULL,
    .cr1 = 0,
    .cr2 = 0,
    .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
    .smpr2 = 0U,
    .sqr1 = ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN15)
};

static const ADCConversionGroup adc3Config = {
    .circular     = true,
    .num_channels = 0,
    .end_cb       = NULL,
    .error_cb     = NULL,
    .cr1 = 0,
    .cr2 = 0,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
    .sqr1 = ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2)
};

void adc_init(void) {
    uprintf("ADC Init\n");
    // setup the ADC pins
    // ADC input channel - MUX NUMBER
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG); // 4 - 4 - 0
    palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_ANALOG); // 6 - 3 - 1
    palSetPadMode(GPIOA, 7, PAL_MODE_INPUT_ANALOG); // 7 - 2 - 2
    palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG); // 11 - 8 - 3
    palSetPadMode(GPIOC, 5, PAL_MODE_INPUT_ANALOG); // 14 - 1 - 4
    palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_ANALOG); // 15 - 0 - 5
    palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_ANALOG); // 0 - 7 - 6
    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG); // 1 - 6 - 7
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_ANALOG); // 2 - 5 - 8

    // Initialize the ADC conversion groups
    adcMultiStart();
    adcMultiStartConversion(&adc1Config, &adc2Config, &adc3Config, adcSamples, 1);
}

