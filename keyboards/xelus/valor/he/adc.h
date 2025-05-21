// adc.h

#include "hal.h"
#include "hal_adc_lld.h"

#pragma once

#define ADC_GROUPS 3

#define ADC_NUM_CHANNELS 3 // Number of ADC channels

typedef struct {
    adcsample_t sampleBuffer1[ADC_NUM_CHANNELS];
    adcsample_t sampleBuffer2[ADC_NUM_CHANNELS];
    adcsample_t sampleBuffer3[ADC_NUM_CHANNELS];
} ADCValues;

// Type Definitions
typedef struct {
    ADCValues values;
    volatile int completedConversions;
    semaphore_t sem;
} ADCManager;

bool scanActive;

const ADCManager *getAdcManagerSnapshot(void);

void initADCGroups(void);
msg_t adcStartAllConversions(void);
void adcErrorCallback(ADCDriver *adcp, adcerror_t err);
static inline adcsample_t getADCSample(const ADCManager *m, uint8_t muxIndex) {
    if (muxIndex < 3)
    return m->values.sampleBuffer1[muxIndex];
    else if (muxIndex < 6)
    return m->values.sampleBuffer2[muxIndex - 2];
    else if (muxIndex < 9)
    return m->values.sampleBuffer3[muxIndex - 6]; // swaps order for ADC4
    return 0;
}
bool waitForAdcConversion(void);

void adc_init(void);
void adc_start(void);
