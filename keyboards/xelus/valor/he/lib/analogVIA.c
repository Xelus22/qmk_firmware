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

#include <stdint.h>
#include <string.h>
#include "via.h"
#include "analogVIA.h"
#include "switchLUT.h"
#include "calibration.h"
#include "analogConfig.h"
#include "distance.h"

#define MAX_VIA_DATA_SIZE (32 - 4) // max amount of data that can be sent in a VIA packet

// remove this later, just for linting
#ifndef MATRIX_COLS
#    define MATRIX_COLS 9
#endif

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]); // byte 2
    uint8_t *value_data = &(data[1]); // byte 3

    switch (*value_id) {
        case id_switch_lut: {
            // Handle setting switch LUT
            switch_lut_picker_t lut = (switch_lut_picker_t)value_data[0];
            set_switch_lut(lut);
            break;
        }
        case id_top_out_calibration: {
            // Handle setting top out calibration
            calibration_sequence_top_out();
            break;
        }
        case id_bottom_out_calibration: {
            bool bCalibrate = value_data[0]; // byte 3
            // Handle setting bottom out calibration
            calibration_sequence_bottom_out(bCalibrate);
            break;
        }
        case id_reset_calibration: {
            // Handle resetting calibration
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    set_top_out_calibration(row, col, DEFAULT_TOP_OUT_CALIBRATION);
                    set_bottom_out_calibration(row, col, DEFAULT_BOTTOM_OUT_CALIBRATION);
                }
            }
            break;
        }
        default: {
            // Unhandled message.
            *value_id = id_unhandled;
            break;
        }
    }
}

void via_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_get_raw_value: {
            // Handle getting raw value
            uint8_t  row       = value_data[0];
            uint8_t  col       = value_data[1];
            uint16_t raw_value = keys[row][col].raw;
            value_data[2]      = (raw_value >> 8) & 0xFF; // High byte
            value_data[3]      = raw_value & 0xFF;        // Low byte
            break;
        }
#if (MATRIX_COLS <= 14)
        case id_get_raw_value_multi: {
            // Handle getting multiple raw values
            // can only fit 28 bytes in a packet after all the request bytes
            // 14 keys per packet
            uint8_t row    = value_data[0]; // byte 3
            uint8_t offset = 4;             // Start from byte 4 for row
            for (int j = 0; j < MATRIX_COLS; j++) {
                uint8_t raw                    = keys[row][j].raw;
                value_data[offset + j * 2]     = (raw >> 8) & 0xFF; // high byte
                value_data[offset + j * 2 + 1] = raw & 0xFF;        // low byte
            }
            break;
        }
#endif
        case id_switch_lut: {
            // Handle getting switch LUT
            switch_lut_picker_t lut = get_switch_lut();
            value_data[0]           = lut; // Store the LUT index in the first byte
            break;
        }
        case id_get_switch_lut_options: {
            // Handle getting switch options
            // This could be a list of available switch LUTs or other options
            // For now, we will just return the current LUT index
            value_data[0] = SWITCH_LUT_END; // num options
            break;
        }
        case id_get_switch_lut_name: {
            // Handle getting switch LUT name
            switch_lut_picker_t lut      = value_data[0]; // Get the LUT index from value_data
            const char         *lut_name = get_switch_lut_name(lut);
            // Copy the name into value_data, ensuring it fits
            size_t name_length = strlen(lut_name);
            // - 1 for the value_data[0] byte
            if (name_length < (MAX_VIA_DATA_SIZE - 1)) {
                memcpy(value_data, lut_name, name_length);
            } else {
                // If the name is too long, truncate it
                memcpy(value_data, lut_name, (MAX_VIA_DATA_SIZE - 1));
            }
            break;
        }
        case id_get_switch_max_distance: {
            // Handle getting switch max distance
            switch_distance_t max_distance = get_switch_max_distance();
            value_data[0]                  = (max_distance >> 8) & 0xFF; // High byte
            value_data[1]                  = max_distance & 0xFF;        // Low byte
            break;
        }
        case id_top_out_calibration: {
            // Handle getting top out calibration
            uint8_t  row                 = value_data[0];
            uint8_t  col                 = value_data[1];
            uint16_t top_out_calibration = get_top_out_calibration(row, col);
            value_data[2]                = (top_out_calibration >> 8) & 0xFF; // High byte
            value_data[3]                = top_out_calibration & 0xFF;        // Low byte
            break;
        }
        case id_bottom_out_calibration: {
            // Handle getting bottom out calibration
            uint8_t  row                    = value_data[0];
            uint8_t  col                    = value_data[1];
            uint16_t bottom_out_calibration = get_bottom_out_calibration(row, col);
            value_data[2]                   = (bottom_out_calibration >> 8) & 0xFF; // High byte
            value_data[3]                   = bottom_out_calibration & 0xFF;        // Low byte
            break;
        }
        case id_get_calibration_data: {
            // Handle getting calibration data
            // This could be a more complex structure, but for now, we will just return the top and bottom out calibrations
            uint8_t  row                    = value_data[0];
            uint8_t  col                    = value_data[1];
            uint16_t top_out_calibration    = get_top_out_calibration(row, col);
            uint16_t bottom_out_calibration = get_bottom_out_calibration(row, col);
            uint16_t top_out_hysteresis     = get_top_out_calibration_hysteresis(row, col);
            uint16_t bottom_out_hysteresis  = get_bottom_out_calibration_hysteresis(row, col);
            value_data[2]                   = (top_out_calibration >> 8) & 0xFF;    // High byte
            value_data[3]                   = top_out_calibration & 0xFF;           // Low byte
            value_data[4]                   = (bottom_out_calibration >> 8) & 0xFF; // High byte
            value_data[5]                   = bottom_out_calibration & 0xFF;        // Low byte
            value_data[6]                   = (top_out_hysteresis >> 8) & 0xFF;     // High byte
            value_data[7]                   = top_out_hysteresis & 0xFF;            // Low byte
            value_data[8]                   = (bottom_out_hysteresis >> 8) & 0xFF;  // High byte
            value_data[9]                   = bottom_out_hysteresis & 0xFF;         // Low byte
            break;
        }
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]); // byte 0
    uint8_t *channel_id        = &(data[1]); // byte 1
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                save_config_to_eeprom();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}