#include "adc.h"
#include "print.h"
#include "stm32f405xx.h"

semaphore_t sem;

static uint32_t numConversions                = 0; // Number of conversions done
// adcsample_t     adcSamples1[ADC_NUM_CHANNELS] = {0};
// adcsample_t     adcSamples2[ADC_NUM_CHANNELS] = {0};
// adcsample_t     adcSamples3[ADC_NUM_CHANNELS] = {0};
adcsample_t adcSamples[NUM_SAMPLES] = {0}; // Buffer for ADC samples

uint32_t getNumConversions(void) {
    return numConversions;
}

static void adcCompleteCallback(ADCDriver *adcp) {
    (void)adcp;
    numConversions++;
    if (numConversions >= ADC_GROUPS) {
        chSemSignalI(&sem);
    }
}

bool waitForAdcConversion(void) {
    uprintf("Waiting for ADC conversion to complete...\n");
    chSemWait(&sem); // Wait for the semaphore to be signalled
    return true;
}

adcsample_t *adc_get_samples(void) {
    // Return the pointer to the ADC samples buffer
    return adcSamples;
}
// adcsample_t *adc_get_samples2(void) {
//     // Return the pointer to the ADC samples buffer
//     return adcSamples2;
// }
// adcsample_t *adc_get_samples3(void) {
//     // Return the pointer to the ADC samples buffer
//     return adcSamples3;
// }

void adcErrorCallback(ADCDriver *adcp, adcerror_t err) {
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
static const ADCConversionGroup adc1Config = {
    .circular     = false,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN4(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN6(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN7(ADC_SAMPLE_3),
    .sqr1 = ADC_SQR1_NUM_CH(3),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7)
};

static const ADCConversionGroup adc2Config = {
    .circular     = false,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART,
    .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
    .smpr2 = 0U,
    .sqr1 = ADC_SQR1_NUM_CH(3),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN15)
};

static const ADCConversionGroup adc3Config = {
    .circular     = false,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART,
    .smpr1 = 0U,
    .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
    .sqr1 = ADC_SQR1_NUM_CH(3),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2)
};
// clang-format on
// turn on clang-format

void adc_init(void) {
    uprintf("ADC Init\n");
    // setup the ADC pins
    palSetPadMode(GPIOC, 5, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 7, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);

    // PCLK2 divided by 4
    // DMA mode 1 enabled (2 / 3 half-words one by one - 1 then 2 then 3)
    // DMA requests are issued as long as data are converted and DMA = 01, 10 or 11.
    // ADC->CCR |= ADC_CCR_ADCPRE_0 | ADC_CCR_DMA_0 | ADC_CCR_DDS;

    // // 10110: Regular simultaneous mode only
    // ADC->CCR |= ADC_CCR_MULTI_4 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1;

    adcStart(&ADCD1, NULL); // Start ADC1
    adcStart(&ADCD2, NULL); // Start ADC2
    adcStart(&ADCD3, NULL); // Start ADC3

    chSemObjectInit(&sem, 0);
    uprintf("Complete semaphore\n");
    numConversions = 0; // Reset the number of conversions
}

void adc_start(void) {
    numConversions = 0; // Reset the number of conversions
    // adcStartConversionI(&ADCD1, &adc1Config, adcSamples1, 1);
    // adcStartConversionI(&ADCD2, &adc2Config, adcSamples2, 1);
    // adcStartConversionI(&ADCD3, &adc3Config, adcSamples3, 1);
    adcConvert(&ADCD1, &adc1Config, adcSamples, 1);
    adcConvert(&ADCD2, &adc2Config, &adcSamples[3], 1);
    adcConvert(&ADCD3, &adc3Config, &adcSamples[6], 1);
}
