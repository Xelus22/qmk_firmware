/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef MCUCONF_H
#define MCUCONF_H

#define AT32F403A_MCUCONF
#define AT32F403xC

/*
 * AT32F103 drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

/*
 * HAL driver system settings.
 */
#define AT32_NO_INIT                       FALSE
#define AT32_HSI_ENABLED                   TRUE
#define AT32_LSI_ENABLED                   FALSE
#define AT32_HSE_ENABLED                   FALSE
#define AT32_LSE_ENABLED                   FALSE
#define AT32_SW                            AT32_SW_PLL
#define AT32_PLLSRC                        AT32_PLLSRC_HSI
#define AT32_PLLXTPRE                      AT32_PLLXTPRE_DIV1
#define AT32_PLLMUL_VALUE                  48
#define AT32_HPRE                          AT32_HPRE_DIV1
#define AT32_PPRE1                         AT32_PPRE1_DIV2
#define AT32_PPRE2                         AT32_PPRE2_DIV2
#define AT32_ADCPRE                        AT32_ADCPRE_DIV8
#define AT32_USB_CLOCK_REQUIRED            TRUE
#define AT32_USBSRC                        AT32_USBSRC_HSI
#define AT32_USBPRE                        AT32_USBPRE_DIV1
#define AT32_MCOSEL                        AT32_MCOSEL_NOCLOCK
#define AT32_RTCSEL                        AT32_RTCSEL_NOCLOCK
#define AT32_PVD_ENABLE                    FALSE
#define AT32_PLS                           AT32_PLS_LEV0

/*
 * IRQ system settings.
 */
#define AT32_IRQ_EXTI0_PRIORITY            6
#define AT32_IRQ_EXTI1_PRIORITY            6
#define AT32_IRQ_EXTI2_PRIORITY            6
#define AT32_IRQ_EXTI3_PRIORITY            6
#define AT32_IRQ_EXTI4_PRIORITY            6
#define AT32_IRQ_EXTI5_9_PRIORITY          6
#define AT32_IRQ_EXTI10_15_PRIORITY        6
#define AT32_IRQ_EXTI16_PRIORITY           6
#define AT32_IRQ_EXTI17_PRIORITY           6
#define AT32_IRQ_EXTI18_PRIORITY           6
#define AT32_IRQ_EXTI19_PRIORITY           6

/*
 * ADC driver system settings.
 */
#define AT32_ADC_USE_ADC1                  FALSE
#define AT32_ADC_ADC1_DMA_PRIORITY         2
#define AT32_ADC_ADC1_IRQ_PRIORITY         6

/*
 * CAN driver system settings.
 */
#define AT32_CAN_USE_CAN1                  FALSE
#define AT32_CAN_CAN1_IRQ_PRIORITY         11

/*
 * GPT driver system settings.
 */
#define AT32_GPT_USE_TIM1                  FALSE
#define AT32_GPT_USE_TIM2                  FALSE
#define AT32_GPT_USE_TIM3                  FALSE
#define AT32_GPT_USE_TIM4                  FALSE
#define AT32_GPT_USE_TIM5                  FALSE
#define AT32_GPT_USE_TIM8                  FALSE
#define AT32_GPT_TIM1_IRQ_PRIORITY         7
#define AT32_GPT_TIM2_IRQ_PRIORITY         7
#define AT32_GPT_TIM3_IRQ_PRIORITY         7
#define AT32_GPT_TIM4_IRQ_PRIORITY         7
#define AT32_GPT_TIM5_IRQ_PRIORITY         7
#define AT32_GPT_TIM8_IRQ_PRIORITY         7

/*
 * I2C driver system settings.
 */
#define AT32_I2C_USE_I2C1                  FALSE
#define AT32_I2C_USE_I2C2                  FALSE
#define AT32_I2C_BUSY_TIMEOUT              50
#define AT32_I2C_I2C1_IRQ_PRIORITY         5
#define AT32_I2C_I2C2_IRQ_PRIORITY         5
#define AT32_I2C_I2C1_DMA_PRIORITY         3
#define AT32_I2C_I2C2_DMA_PRIORITY         3
#define AT32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define AT32_ICU_USE_TIM1                  FALSE
#define AT32_ICU_USE_TIM2                  FALSE
#define AT32_ICU_USE_TIM3                  FALSE
#define AT32_ICU_USE_TIM4                  FALSE
#define AT32_ICU_USE_TIM5                  FALSE
#define AT32_ICU_USE_TIM8                  FALSE
#define AT32_ICU_TIM1_IRQ_PRIORITY         7
#define AT32_ICU_TIM2_IRQ_PRIORITY         7
#define AT32_ICU_TIM3_IRQ_PRIORITY         7
#define AT32_ICU_TIM4_IRQ_PRIORITY         7
#define AT32_ICU_TIM5_IRQ_PRIORITY         7
#define AT32_ICU_TIM8_IRQ_PRIORITY         7

/*
 * PWM driver system settings.
 */
#define AT32_PWM_USE_ADVANCED              FALSE
#define AT32_PWM_USE_TIM1                  FALSE
#define AT32_PWM_USE_TIM2                  FALSE
#define AT32_PWM_USE_TIM3                  FALSE
#define AT32_PWM_USE_TIM4                  FALSE
#define AT32_PWM_USE_TIM5                  FALSE
#define AT32_PWM_USE_TIM8                  FALSE
#define AT32_PWM_TIM1_IRQ_PRIORITY         7
#define AT32_PWM_TIM2_IRQ_PRIORITY         7
#define AT32_PWM_TIM3_IRQ_PRIORITY         7
#define AT32_PWM_TIM4_IRQ_PRIORITY         7
#define AT32_PWM_TIM5_IRQ_PRIORITY         7
#define AT32_PWM_TIM8_IRQ_PRIORITY         7

/*
 * RTC driver system settings.
 */
#define AT32_RTC_IRQ_PRIORITY              15

/*
 * SERIAL driver system settings.
 */
#define AT32_SERIAL_USE_USART1             FALSE
#define AT32_SERIAL_USE_USART2             FALSE
#define AT32_SERIAL_USE_USART3             FALSE
#define AT32_SERIAL_USE_UART4              FALSE
#define AT32_SERIAL_USE_UART5              FALSE
#define AT32_SERIAL_USART1_PRIORITY        12
#define AT32_SERIAL_USART2_PRIORITY        12
#define AT32_SERIAL_USART3_PRIORITY        12
#define AT32_SERIAL_UART4_PRIORITY         12
#define AT32_SERIAL_UART5_PRIORITY         12

/*
 * SPI driver system settings.
 */
#define AT32_SPI_USE_SPI1                  FALSE
#define AT32_SPI_USE_SPI2                  FALSE
#define AT32_SPI_USE_SPI3                  FALSE
#define AT32_SPI_SPI1_DMA_PRIORITY         1
#define AT32_SPI_SPI2_DMA_PRIORITY         1
#define AT32_SPI_SPI3_DMA_PRIORITY         1
#define AT32_SPI_SPI1_IRQ_PRIORITY         10
#define AT32_SPI_SPI2_IRQ_PRIORITY         10
#define AT32_SPI_SPI3_IRQ_PRIORITY         10
#define AT32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define AT32_ST_IRQ_PRIORITY               8
#define AT32_ST_USE_TIMER                  2

/*
 * UART driver system settings.
 */
#define AT32_UART_USE_USART1               FALSE
#define AT32_UART_USE_USART2               FALSE
#define AT32_UART_USE_USART3               FALSE
#define AT32_UART_USART1_IRQ_PRIORITY      12
#define AT32_UART_USART2_IRQ_PRIORITY      12
#define AT32_UART_USART3_IRQ_PRIORITY      12
#define AT32_UART_USART1_DMA_PRIORITY      0
#define AT32_UART_USART2_DMA_PRIORITY      0
#define AT32_UART_USART3_DMA_PRIORITY      0
#define AT32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define AT32_USB_USE_USB1                  TRUE
#define AT32_USB_LOW_POWER_ON_SUSPEND      FALSE
#define AT32_USB_USB1_HP_IRQ_PRIORITY      13
#define AT32_USB_USB1_LP_IRQ_PRIORITY      14

/*
 * WDG driver system settings.
 */
#define AT32_WDG_USE_IWDG                  FALSE

#endif /* MCUCONF_H */
