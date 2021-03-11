/* Copyright 2020 Harrison Chan (Xelus)
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

#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0x5845 // XE
#define PRODUCT_ID      0x0060 // Dawn60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Dawn60Rev2

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//underglow
#define MATRIX_ROW_PINS { A9, A10, B13, B14, B15    }
#define MATRIX_COL_PINS { A8, A2, A1, A0, B11, B10, B2, B1, B0, A7, A6, A5, A4, A3 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// I2C Defines
#define I2C1_SCL            8
#define I2C1_SDA            9
#define I2C1_SCL_PAL_MODE   1
#define I2C1_SDA_PAL_MODE   1
#define I2C1_TIMINGR_PRESC  2U
#define I2C1_TIMINGR_SCLDEL 7U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   13U
#define I2C1_TIMINGR_SCLL   42U

// I2C EEPROM Chip
#define EEPROM_I2C_24LC256

// Dynamic Keymap
//#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  65535

// // PWM RGB Underglow Defines
// #define WS2812_PWM_DRIVER PWMD3
// #define WS2812_PWM_CHANNEL 2
// #define WS2812_PWM_PAL_MODE 1
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM3
// #define WS2812_DMA_CHANNEL 3
// #define WS2812_EXTERNAL_PULLUP

// SPI RGB Underglow Defines
#define WS2812_SPI SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5


// This conditionally compiles the backlight code for Dawn60 specifics
#define RGB_BACKLIGHT_ENABLED 1
#define RGB_BACKLIGHT_DAWN60REV2

// IS31FL3731 driver
#define DRIVER_COUNT 2
#define DRIVER_LED_TOTAL 72

//RGB Underglow defines
#define RGB_DI_PIN B5
#define WS2812_LED_TOTAL 20
#define RGBLED_NUM 20

#define RGB_UNDERGLOW_ALPHA_TOP_START 0
#define RGB_UNDERGLOW_ALPHA_TOP_END   6   
#define RGB_UNDERGLOW_ALPHA_BOT_START 12
#define RGB_UNDERGLOW_ALPHA_BOT_END   15

// enable/disable LEDs based on layout
// switch between split backspace (1) or normal backspace(0)
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 1
// switch between Tsangan (1) or Arrows Bottom Row (0)
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
// switch between standard split rshift (0) or arrows r shift (1)
// .------------------.           .-------------------.
// | ? |  Shift  | Fn |    vs     |  Shift  | Up | Fn |
// `------------------'           `-------------------'
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 1

//not used
#define RGB_BACKLIGHT_USE_ISO_ENTER 0
#define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 0

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// the default brightness
#define RGB_BACKLIGHT_BRIGHTNESS 200

// the default effect (RGB test)
#define RGB_BACKLIGHT_EFFECT 255

// the default effect speed (0-3)
#define RGB_BACKLIGHT_EFFECT_SPEED 0

// the default color1 and color2
#define RGB_BACKLIGHT_COLOR_1 { .h = 0, .s = 255 }
#define RGB_BACKLIGHT_COLOR_2 { .h = 127, .s = 255 }

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0000000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0010000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0011000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0011100000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b0011111110011111

#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_1_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_2_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_3_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }

// Backlight config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 31

// VIA lighting is handled by the keyboard-level code
#define VIA_CUSTOM_LIGHTING_ENABLE


#define DEBUG_MATRIX_SCAN_RATE