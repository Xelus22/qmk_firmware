// adc.h

#include "hal.h"
#include "hal_adc_lld.h"

#pragma once

#define ADC_GROUPS 3

#define ADC_NUM_CHANNELS 3 // Number of ADC channels

#define NUM_SAMPLES (ADC_GROUPS * ADC_NUM_CHANNELS)

uint32_t getNumConversions(void);
adcsample_t *adc_get_samples(void);
void adc_init(void);
void adc_start(void);
bool waitForAdcConversion(void);
