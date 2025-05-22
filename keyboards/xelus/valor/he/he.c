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

#include "quantum.h"
#include "lib/analogkey.h"

// custom EECONFIG
typedef struct custom_config_t {
    per_key_analog_config config[MATRIX_ROWS][MATRIX_COLS];
} custom_config_t;

custom_config_t custom_config;

// #ifdef BOOTMAGIC_ENABLE
// void bootmagic_scan(void) {
//     matrix_scan();

//     uint16_t threshold = distance_to_adc(CALIBRATION_RANGE * 3 / 4);
//     uint16_t raw_value = keys[BOOTMAGIC_ROW][BOOTMAGIC_COLUMN].raw;

//     if (((lut_b > 0) & (raw_value > threshold)) | ((lut_b < 0) & (raw_value < threshold))) {
//         bootloader_jump();
//     }
// }
// #endif

void board_init(void) {
    // Set the USB HS pin to high
    gpio_set_pin_output(A15);
    gpio_write_pin_high(A15);
}

void keyboard_post_init_kb(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

  keyboard_post_init_user();
}
