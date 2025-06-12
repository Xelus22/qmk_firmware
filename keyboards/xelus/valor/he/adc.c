#include "adc.h"
#include "print.h"
#include "stm32f405xx.h"

volatile uint32_t numConversions          = 0; // Number of conversions done
semaphore_t       sem                     = {0};
adcsample_t       adcSamples[NUM_SAMPLES] = {0}; // Buffer for ADC samples

uint32_t getNumConversions(void) {
    osalSysLock();
    uint32_t nConversions = numConversions;
    osalSysUnlock();
    return nConversions;
}

__attribute__((used)) void adcCompleteCallback(ADCDriver *adcp) {
    (void)adcp;
    osalSysLockFromISR();
    numConversions++;
    if (numConversions >= ADC_GROUPS) {
        numConversions = 0; // Reset the conversion count
        chSemSignalI(&sem);
    }
    osalSysUnlockFromISR();
}

bool waitForAdcConversion(void) {
    // uprintf("Waiting for ADC conversion to complete...\n");
    chSemWait(&sem); // Wait for the semaphore to be signalled
    return true;
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

// turn off clang-format
// clang-format off
static const ADCConversionGroup adc1Config = {
    .circular     = false,
    .num_channels = ADC_NUM_CHANNELS,
    .end_cb       = adcCompleteCallback,
    .error_cb     = adcErrorCallback,
    .cr1 = ADC_CR1_SCAN,
    .cr2 = ADC_CR2_SWSTART | ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_ADON | ADC_CR2_CONT,
    .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
             ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
    .smpr2 = ADC_SMPR2_SMP_AN4(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN6(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN7(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
             ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
    .sqr1 = 0U,
    .sqr2 = ADC_SQR2_SQ7_N(ADC_CHANNEL_IN11) |
            ADC_SQR2_SQ8_N(ADC_CHANNEL_IN14) |
            ADC_SQR2_SQ9_N(ADC_CHANNEL_IN15),
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4) |
            ADC_SQR3_SQ2_N(ADC_CHANNEL_IN6) |
            ADC_SQR3_SQ3_N(ADC_CHANNEL_IN7) |
            ADC_SQR3_SQ4_N(ADC_CHANNEL_IN0) |
            ADC_SQR3_SQ5_N(ADC_CHANNEL_IN1) |
            ADC_SQR3_SQ6_N(ADC_CHANNEL_IN2),
};

// static const ADCConversionGroup adc2Config = {
//     .circular     = false,
//     .num_channels = ADC_NUM_CHANNELS,
//     .end_cb       = adcCompleteCallback,
//     .error_cb     = adcErrorCallback,
//     .cr1 = ADC_CR1_SCAN,
//     .cr2 = ADC_CR2_SWSTART | ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_ADON | ADC_CR2_CONT,
//     .smpr1 = ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3) |
//              ADC_SMPR1_SMP_AN14(ADC_SAMPLE_3) |
//              ADC_SMPR1_SMP_AN15(ADC_SAMPLE_3),
//     .smpr2 = 0U,
//     .sqr1 = 0U,
//     .sqr2 = 0U,
//     .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11) |
//             ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14) |
//             ADC_SQR3_SQ3_N(ADC_CHANNEL_IN15)
// };

// static const ADCConversionGroup adc3Config = {
//     .circular     = false,
//     .num_channels = ADC_NUM_CHANNELS,
//     .end_cb       = adcCompleteCallback,
//     .error_cb     = adcErrorCallback,
//     .cr1 = ADC_CR1_SCAN,
//     .cr2 = ADC_CR2_SWSTART | ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_ADON | ADC_CR2_CONT,
//     .smpr1 = 0U,
//     .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) |
//              ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
//     .sqr1 = 0U,
//     .sqr2 = 0U,
//     .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0) |
//             ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) |
//             ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2)
// };
// clang-format on
// turn on clang-format

void setup_adc_registers(ADCDriver *adcp, const ADCConversionGroup *grpp, adcsample_t *samples) {
    adcp->samples = samples;
    adcp->depth   = 1;
    adcp->grpp    = grpp;

    adcp->adc->SMPR1 = grpp->smpr1;
    adcp->adc->SMPR2 = grpp->smpr2;
    adcp->adc->HTR   = grpp->htr;
    adcp->adc->LTR   = grpp->ltr;
    adcp->adc->SQR1  = grpp->sqr1 | ADC_SQR1_NUM_CH(grpp->num_channels);
    adcp->adc->SQR2  = grpp->sqr2;
    adcp->adc->SQR3  = grpp->sqr3;
    adcp->adc->CR1   = 0;
    adcp->adc->CR2   = 0;
}

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

    // PCLK2 divided by 4
    // DMA mode 1 enabled (2 / 3 half-words one by one - 1 then 2 then 3)
    // DMA requests are issued as long as data are converted and DMA = 01, 10 or 11.
    // ADC->CCR |= ADC_CCR_ADCPRE_0 | ADC_CCR_DMA_0 | ADC_CCR_DDS;

    // // 10110: Regular simultaneous mode only
    // ADC->CCR |= ADC_CCR_MULTI_4 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_1;

    adcStart(&ADCD1, NULL); // Start ADC1
    // adcStart(&ADCD2, NULL); // Start ADC2
    // adcStart(&ADCD3, NULL); // Start ADC3

    chSemObjectInit(&sem, 0);
    uprintf("Complete semaphore\n");
    numConversions = 0; // Reset the number of conversions

    // Initialize the ADC conversion groups
    chSysLock();
    setup_adc_registers(&ADCD1, &adc1Config, adcSamples);
    // setup_adc_registers(&ADCD2, &adc2Config, &adcSamples[3]);
    // setup_adc_registers(&ADCD3, &adc3Config, &adcSamples[6]);
    chSysUnlock();
}

void adc_start(void) {
    chSysLock();
    // ADC1
    uint32_t cr2 = adc1Config.cr2;
    dmaStreamSetMemory0(ADCD1.dmastp, adcSamples);
    dmaStreamSetTransactionSize(ADCD1.dmastp, (uint32_t)ADC_NUM_CHANNELS);
    dmaStreamSetMode(ADCD1.dmastp, ADCD1.dmamode);
    dmaStreamEnable(ADCD1.dmastp);
    ADCD1.state     = ADC_ACTIVE; // Set the state to active
    ADCD1.grpp      = &adc1Config;
    ADCD1.adc->SR   = 0;
    ADCD1.adc->SQR2 = adc1Config.sqr2;
    ADCD1.adc->SQR3 = adc1Config.sqr3;
    ADCD1.adc->CR1  = adc1Config.cr1;
    ADCD1.adc->CR2  = (cr2) & ~ADC_CR2_SWSTART;
    ADCD1.adc->CR2  = (cr2);

    // ADC2
    // dmaStreamSetMemory0(ADCD2.dmastp, &adcSamples[3]);
    // dmaStreamSetTransactionSize(ADCD2.dmastp, (uint32_t)ADC_NUM_CHANNELS);
    // dmaStreamSetMode(ADCD2.dmastp, ADCD2.dmamode);
    // dmaStreamEnable(ADCD2.dmastp);
    // ADCD2.state = ADC_ACTIVE; // Set the state to active
    // ADCD2.grpp  = &adc2Config;
    // ADCD2.adc->SR   = 0;
    // ADCD2.adc->SQR3 = adc2Config.sqr3;
    // ADCD2.adc->CR1  = adc2Config.cr1;
    // ADCD2.adc->CR2  = (cr2) & ~ADC_CR2_SWSTART;
    // ADCD2.adc->CR2  = (cr2);

    // dmaStreamSetMemory0(ADCD3.dmastp, &adcSamples[6]);
    // dmaStreamSetTransactionSize(ADCD3.dmastp, (uint32_t)ADC_NUM_CHANNELS);
    // dmaStreamSetMode(ADCD3.dmastp, ADCD3.dmamode);
    // dmaStreamEnable(ADCD3.dmastp);
    // ADCD3.state = ADC_ACTIVE; // Set the state to active
    // ADCD3.grpp  = &adc3Config;
    // ADCD3.adc->SR   = 0;
    // ADCD3.adc->SQR3 = adc3Config.sqr3;
    // ADCD3.adc->CR1  = adc3Config.cr1;
    // ADCD3.adc->CR2  = (cr2) & ~ADC_CR2_SWSTART;
    // ADCD3.adc->CR2  = (cr2);

    // normal ChibiOS way to start conversion
    // adcStartConversionI(&ADCD1, &adc1Config, adcSamples, 1);
    // adcStartConversionI(&ADCD2, &adc2Config, &adcSamples[3], 1);
    // adcStartConversionI(&ADCD3, &adc3Config, &adcSamples[6], 1);
    chSysUnlock();
}
