/* Copyright 2021 QMK
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

#pragma once

#include_next <mcuconf.h>

#undef STM32_GPT_USE_TIM3
#define STM32_GPT_USE_TIM3 TRUE

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

#undef STM32_SPI_USE_SPI3
#define STM32_SPI_USE_SPI3 TRUE

#undef STM32_USB_USE_OTG1
#define STM32_USB_USE_OTG1 FALSE
#undef STM32_USB_USE_OTG2
#define STM32_USB_USE_OTG2 TRUE

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE
#undef STM32_ADC_USE_ADC2
#define STM32_ADC_USE_ADC2 TRUE
#undef STM32_ADC_USE_ADC3
#define STM32_ADC_USE_ADC3 TRUE

// adc only running at 21MHz clock (168 / 8)

// Add DMA configuration for ADCs
#undef STM32_ADC_ADC1_DMA_STREAM
#define STM32_ADC_ADC1_DMA_STREAM STM32_DMA_STREAM_ID(2, 4)
#undef STM32_ADC_ADC2_DMA_STREAM
#define STM32_ADC_ADC2_DMA_STREAM STM32_DMA_STREAM_ID(2, 2)
#undef STM32_ADC_ADC3_DMA_STREAM
#define STM32_ADC_ADC3_DMA_STREAM STM32_DMA_STREAM_ID(2, 0)

#undef STM32_ADC_IRQ_PRIORITY
#define STM32_ADC_IRQ_PRIORITY 7
