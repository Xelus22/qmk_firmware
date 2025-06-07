/* Copyright 2021 Harrison Chan (Xelus)
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

// USB
#define USB_DRIVER USBD2

// SPI
#define SPI_SCK_PIN C10
#define SPI_SCK_PAL_MODE 6
#define SPI_MOSI_PIN C12
#define SPI_MOSI_PAL_MODE 6
#define SPI_MISO_PIN C11
#define SPI_MISO_PAL_MODE 6
#define SPI_DRIVER SPID3

// SPI FLASH
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN D2
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 1  // 48MHz; max supported by W25Q128JV is 133MHz
#define EXTERNAL_FLASH_SIZE (64 * 1024)  //128Mbit or 16MByte // actually 16MByte but using as 64kB for now
#define EXTERNAL_FLASH_SPI_TIMEOUT 200000 //datasheet max is 200seconds for flash chip erase

// WEAR LEVELLING
// #define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT 8
// #define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET 0

// RGB PWM
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM6
#define WS2812_PWM_DMA_CHANNEL 2
#define WS2812_PWM_DMAMUX_ID STM32_DMAMUX1_TIM4_UP

// WS2812
#define WS2812_TIMING 900
#define WS2812_T1H 650
#define WS2812_T0H 320

#define DEBUG_MATRIX_SCAN_RATE

#define EECONFIG_KB_DATA_SIZE ((24 * 8 * 9) + 14 * 10) // 24 bytes per key, 8 rows, 9 cols + 10 dks keys