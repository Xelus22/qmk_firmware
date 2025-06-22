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

#define TIM8_TRGO_EVT (ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1) // TIM8 TRGO event

semaphore_t sem                     = {0};
adcsample_t adcSamples[NUM_SAMPLES] = {0}; // Buffer for ADC samples

__attribute__((used)) void adcCompleteCallback(ADCDriver *adcp) {
    (void)adcp;
    chSemSignalI(&sem);
}

void waitForAdcConversion(void) {
    osalSysLockFromISR();
    chSemWait(&sem); // Wait for the semaphore to be signalled
    osalSysUnlockFromISR();
}

adcsample_t *adc_get_samples(void) {
    // Return the pointer to the ADC samples buffer
    return adcSamples;
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

static const GPTConfig gpt8cfg = {
    .frequency = 1000000, // 1 MHz timer clock (adjust as needed)
    .callback  = NULL,    // No callback needed for TRGO use
    .cr2       = 0,       // We'll override this manually below
    .dier      = 0        // No interrupts
};

void init_tim8_trgo(void) {
    gptStart(&GPTD8, &gpt8cfg); // Init GPT driver (TIM8)
    gptStopTimer(&GPTD8);       // Make sure it's not counting

    // Setup TIM8->CR2 MMS to generate TRGO on update event
    TIM8->CR2 = (TIM8->CR2 & ~TIM_CR2_MMS) | TIM_CR2_MMS_1;

    // Optionally enable auto-reload preload
    TIM8->CR1 |= TIM_CR1_ARPE;

    // Enable update events
    TIM8->EGR |= TIM_EGR_UG;
}

// clang-format off
static const ADCConversionGroup adc1Config = {
    .circular     = true,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_EXTEN_0 | TIM8_TRGO_EVT,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN4(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN6(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN7(ADC_SAMPLE_3),
    .sqr1 = 0U,
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7)
};

static const ADCConversionGroup adc2Config = {
    .circular     = true,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = NULL,
    .error_cb     = NULL,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_EXTEN_0 | TIM8_TRGO_EVT,
    .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
    .smpr2 = 0U,
    .sqr1 = 0U,
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN15)
};

static const ADCConversionGroup adc3Config = {
    .circular     = true,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = NULL,
    .error_cb     = NULL,
    .cr1 = ADC_CR1_SCAN,
    .cr2 =  ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_EXTEN_0 | TIM8_TRGO_EVT,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
    .sqr1 = 0U,
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2)
};
//clang-format on

void adc_init(void) {
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

    chSemObjectInit(&sem, 0);
    init_tim8_trgo();
    
    adcStart(&ADCD1, NULL); // Start ADC1
    adcStart(&ADCD2, NULL); // Start ADC1
    adcStart(&ADCD3, NULL); // Start ADC1
    adcStartConversionI(&ADCD1, &adc1Config, adcSamples, 1);
    adcStartConversionI(&ADCD2, &adc2Config, &adcSamples[3], 1);
    adcStartConversionI(&ADCD3, &adc3Config, &adcSamples[6], 1);
}

void adc_start(void) {
    // place the trigger timer code here 
    TIM8->EGR |= TIM_EGR_UG; // Software trigger (TRGO fires immediately)
}
