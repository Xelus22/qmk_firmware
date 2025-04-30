#include "adc.h"
#include "print.h"
#include "stm32f405xx.h"

// Define the global ADC manager instance
ADCManager adcManager;

static void adcCompleteCallback(ADCDriver *adcp) {
    (void)adcp;
    if (++adcManager.completedConversions >= ADC_GROUPS) {
        adcManager.completedConversions = 0;
        chSemSignalI(&adcManager.sem);
    }
}

bool waitForAdcConversion(void) {
    chSemWait(&adcManager.sem); // Wait for the semaphore to be signalled
    // copy values from local buffer to ADCValues struct
    memcpy(&adcManager.values, &adcBuffers, sizeof(ADCValues));
    return true;
}

void adcErrorCallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp; // Unused parameter
    switch (err) {
        case ADC_ERR_DMAFAILURE:
            uprintf("ADC ERROR: DMA failure.\n");
            break;
        case ADC_ERR_OVERFLOW:
            uprintf("ADC ERROR: Overflow.\n");
            break;
        case ADC_ERR_AWD1:
            uprintf("ADC ERROR: Watchdog 1 triggered.\n");
            break;
        case ADC_ERR_AWD2:
            uprintf("ADC ERROR: Watchdog 2 triggered.\n");
            break;
        case ADC_ERR_AWD3:
            uprintf("ADC ERROR: Watchdog 3 triggered.\n");
            break;
        default:
            uprintf("ADC ERROR: Unknown error.\n");
            break;
    }
}

static ADCValues adcBuffers;

// turn off clang-format
// clang-format off
static const ADCConversionGroup adc1Config = {
    .circular     = false,
    .num_channels = 3U,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_DMA | ADC_CR2_EXTSEL_SRC(ADC_EXTSEL_TIM3_TRGO) | ADC_CR2_EXTEN_RISING,
    .smpr1 = ADC_SMPR1_SMP_AN4(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN6(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN7(ADC_SAMPLE_3),
    .smpr2 = 0U,
    .sqr1 = ADC_SQR1_NUM_CH(3),
    .sqr2 = 0U,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7)
};

static const ADCConversionGroup adc2Config = {
    .circular     = false,
    .num_channels = 3U,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_DMA | ADC_CR2_EXTSEL_SRC(ADC_EXTSEL_TIM3_TRGO) | ADC_CR2_EXTEN_RISING,
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
    .num_channels = 3U,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_DMA | ADC_CR2_EXTSEL_SRC(ADC_EXTSEL_TIM3_TRGO) | ADC_CR2_EXTEN_RISING,
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

void initADCGroups() {
    adcManager.completedConversions = 0;
    chSemObjectInit(&adcManager.sem, 0); // Initialize semaphore with a count of 0

    ADC->CCR = ADC_CCR_MULTI_RegularSimult | ADC_CCR_DMA_2; // Enable Multi-ADC mode with DMA

    adcStart(&ADCD1, NULL); // Start ADC1
    adcStart(&ADCD2, NULL); // Start ADC2
    adcStart(&ADCD3, NULL); // Start ADC3
}

msg_t adcStartAllConversions() {
    adcManager.completedConversions = 0;

    // Start conversions on multiple ADCs
    adcStartConversion(&ADCD1, &adcBuffers.sampleBuffer1, adc1Buffer, 1);
    adcStartConversion(&ADCD2, &adcBuffers.sampleBuffer2, adc2Buffer, 1);
    adcStartConversion(&ADCD3, &adcBuffers.sampleBuffer3, adc3Buffer, 1);

    return MSG_OK;
}

// Snapshot accessor.
const ADCManager *getAdcManagerSnapshot(void) {
    return &adcManager;
}
