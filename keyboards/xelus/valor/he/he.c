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
#include "lib/analogkey.h" // custom eeconfig in here
#include "lib/analogConfig.h"
#include "raw_hid.h"

#ifdef BOOTMAGIC_ENABLE
void bootmagic_scan(void) {
    wait_us(200); // wait for the sensors to stabilize
    for (int i = 0; i < 100; i++) {
        // scan the matrix
        matrix_scan();
    }

    uint16_t threshold = 3000; // threshold for bootmagic activation
    uint16_t raw_value = keys[BOOTMAGIC_ROW][BOOTMAGIC_COLUMN].raw;

    if (raw_value > threshold) {
        // reset eeprom
        eeconfig_disable();
        bootloader_jump();
    }
}
#endif

void board_init(void) {
    // Set the USB HS pin to high
    gpio_set_pin_output(A15);
    gpio_write_pin_high(A15);
}

void eeconfig_init_kb(void) {
    // Default values
    reset_analog_config();

    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&analog_config, 0, EECONFIG_KB_DATA_SIZE);

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    debug_enable = true;
    debug_matrix = true;
    
    analog_config_init();
    eeconfig_read_kb_datablock(&analog_config, 0, EECONFIG_KB_DATA_SIZE);

    keyboard_post_init_user();
}

// bool via_command_kb(uint8_t *data, uint8_t length) {
//     // send the matrix key numbers

//     uint8_t row = data[0];
//     // can only fit 32 bytes in a packet
//     // 15 keys per packet
//     uint8_t offset = 1;
//     for (int j = 0; j < MATRIX_COLS; j++) {
//         data[j * 2 + offset]     = (keys[row][j].raw >> 8) & 0xFF; // high byte
//         data[j * 2 + 1 + offset] = keys[row][j].raw & 0xFF;        // low byte
//     }

//     raw_hid_send(data, length);
//     // do not process anything after this
//     return true;
// }