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

#include "hal.h"
#include "hal_adc_lld.h"

#pragma once

#define ADC_GROUPS 1

#define ADC_NUM_CHANNELS 9 // Number of ADC channels

#define NUM_SAMPLES (ADC_GROUPS * ADC_NUM_CHANNELS)

adcsample_t *adc_get_samples(void);
void adc_init(void);
void adc_start(void);
bool waitForAdcConversion(void);
