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
#include "quantum.h"

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
        case id_actuation_mode: {
            // Handle setting actuation mode
            uint8_t row  = value_data[0]; // byte 3
            uint8_t col  = value_data[1]; // byte 4
            uint8_t mode = value_data[2]; // byte 5
            set_analog_key_mode(row, col, mode);
            break;
        }
        case id_reset_mode: {
            // Handle resetting actuation mode
            reset_analog_key_mode();
            break;
        }
        case id_static_actuation_press_point: {
            // Handle setting static actuation press point
            uint8_t  row             = value_data[0];                        // byte 3
            uint8_t  col             = value_data[1];                        // byte 4
            uint16_t actuation_point = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_static_actuation_press_point(row, col, actuation_point);
            break;
        }
        case id_static_actuation_release_point: {
            // Handle setting static actuation release point
            uint8_t  row             = value_data[0];                        // byte 3
            uint8_t  col             = value_data[1];                        // byte 4
            uint16_t actuation_point = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_static_actuation_release_point(row, col, actuation_point);
            break;
        }
        case id_reset_static_actuation: {
            // Handle resetting static actuation
            reset_static_actuation();
            break;
        }
        case id_dynamic_activate_threshold: {
            // Handle setting dynamic activate threshold
            uint8_t  row           = value_data[0];                        // byte 3
            uint8_t  col           = value_data[1];                        // byte 4
            uint16_t act_threshold = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_dynamic_activate_threshold(row, col, act_threshold);
            break;
        }
        case id_dynamic_press_hysteresis: {
            // Handle setting dynamic press hysteresis
            uint8_t  row              = value_data[0];                        // byte 3
            uint8_t  col              = value_data[1];                        // byte 4
            uint16_t press_hysteresis = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_dynamic_press_hysteresis(row, col, press_hysteresis);
            break;
        }
        case id_dynamic_release_hysteresis: {
            // Handle setting dynamic release hysteresis
            uint8_t  row                = value_data[0];                        // byte 3
            uint8_t  col                = value_data[1];                        // byte 4
            uint16_t release_hysteresis = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_dynamic_release_hysteresis(row, col, release_hysteresis);
            break;
        }
        case id_reset_dynamic_actuation: {
            // Handle resetting dynamic actuation
            reset_dynamic_actuation();
            break;
        }
        case id_reset_dks_actuation: {
            // Handle resetting DKS actuation
            reset_dks_actuation();
            break;
        }
        case id_dks_num: {
            // Handle setting DKS number
            uint8_t row     = value_data[0]; // byte 3
            uint8_t col     = value_data[1]; // byte 4
            uint8_t dks_num = value_data[2]; // byte 5
            set_dks_num(row, col, dks_num);
            break;
        }
        case id_dks_top_actuation_point: {
            // Handle setting DKS top actuation point
            uint8_t  row             = value_data[0];                        // byte 3
            uint8_t  col             = value_data[1];                        // byte 4
            uint16_t actuation_point = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_dks_top_actuation_point(row, col, actuation_point);
            break;
        }
        case id_dks_bottom_actuation_point: {
            // Handle setting DKS bottom actuation point
            uint8_t  row             = value_data[0];                        // byte 3
            uint8_t  col             = value_data[1];                        // byte 4
            uint16_t actuation_point = (value_data[2] << 8) | value_data[3]; // bytes 5 and 6
            set_dks_bot_actuation_point(row, col, actuation_point);
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
#ifdef DEBUG_MATRIX_SCAN_RATE
        case id_get_matrix_scan_rate: {
            // Handle getting matrix scan rate
            uint32_t scan_rate = get_matrix_scan_rate();
            value_data[0]      = (scan_rate >> 24) & 0xFF; // High byte
            value_data[1]      = (scan_rate >> 16) & 0xFF; // Second byte
            value_data[2]      = (scan_rate >> 8) & 0xFF;  // Third byte
            value_data[3]      = scan_rate & 0xFF;         // Low byte
            break;
        }
#endif
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
            uint8_t offset = 1;             // Start from byte 4 for row
            for (int j = 0; j < MATRIX_COLS; j++) {
                uint16_t raw                   = keys[row][j].raw;
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
        case id_switch_lut_table: {
            // Handle getting switch LUT
            uint16_t          idx_high     = value_data[0];                  // High byte of LUT index
            uint16_t          idx_low      = value_data[1];                  // Low byte of LUT index
            uint16_t          idx          = (idx_high << 8) | idx_low;      // Combine high and low bytes
            switch_distance_t lut_value    = get_switch_distance_value(idx); // Get the distance value and store it in value_data starting from byte 3
            uint8_t           lut_val_high = (lut_value >> 8) & 0xFF;        // High byte of LUT value
            uint8_t           lut_val_low  = lut_value & 0xFF;               // Low byte of LUT value
            value_data[2]                  = lut_val_high;                   // Store high byte in byte 3
            value_data[3]                  = lut_val_low;                    // Store low byte in byte 4
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
        case id_actuation_mode: {
            // Handle getting actuation mode
            uint8_t row   = value_data[0];                 // byte 3
            uint8_t col   = value_data[1];                 // byte 4
            value_data[2] = get_analog_key_mode(row, col); // Store the mode in byte 5
            break;
        }
        case id_static_actuation_press_point: {
            // Handle getting static actuation press point
            uint8_t  row             = value_data[0]; // byte 3
            uint8_t  col             = value_data[1]; // byte 4
            uint16_t actuation_point = get_static_actuation_press_point(row, col);
            value_data[2]            = (actuation_point >> 8) & 0xFF; // High byte
            value_data[3]            = actuation_point & 0xFF;        // Low byte
            break;
        }
        case id_static_actuation_release_point: {
            // Handle getting static actuation release point
            uint8_t  row             = value_data[0]; // byte 3
            uint8_t  col             = value_data[1]; // byte 4
            uint16_t actuation_point = get_static_actuation_release_point(row, col);
            value_data[2]            = (actuation_point >> 8) & 0xFF; // High byte
            value_data[3]            = actuation_point & 0xFF;        // Low byte
            break;
        }
        case id_dynamic_activate_threshold: {
            // Handle getting dynamic activate threshold
            uint8_t  row           = value_data[0]; // byte 3
            uint8_t  col           = value_data[1]; // byte 4
            uint16_t act_threshold = get_dynamic_activate_threshold(row, col);
            value_data[2]          = (act_threshold >> 8) & 0xFF; // High byte
            value_data[3]          = act_threshold & 0xFF;        // Low byte
            break;
        }
        case id_dynamic_press_hysteresis: {
            // Handle getting dynamic press hysteresis
            uint8_t  row              = value_data[0]; // byte 3
            uint8_t  col              = value_data[1]; // byte 4
            uint16_t press_hysteresis = get_dynamic_press_hysteresis(row, col);
            value_data[2]             = (press_hysteresis >> 8) & 0xFF; // High byte
            value_data[3]             = press_hysteresis & 0xFF;        // Low byte
            break;
        }
        case id_dynamic_release_hysteresis: {
            // Handle getting dynamic release hysteresis
            uint8_t  row                = value_data[0]; // byte 3
            uint8_t  col                = value_data[1]; // byte 4
            uint16_t release_hysteresis = get_dynamic_release_hysteresis(row, col);
            value_data[2]               = (release_hysteresis >> 8) & 0xFF; // High byte
            value_data[3]               = release_hysteresis & 0xFF;        // Low byte
            break;
        }
        case id_dks_num: {
            // Handle getting DKS number
            uint8_t row   = value_data[0];         // byte 3
            uint8_t col   = value_data[1];         // byte 4
            value_data[2] = get_dks_num(row, col); // Store the DKS number in byte 5
            break;
        }
        case id_dks_top_actuation_point: {
            // Handle getting DKS top actuation point
            uint8_t  row             = value_data[0]; // byte 3
            uint8_t  col             = value_data[1]; // byte 4
            uint16_t actuation_point = get_dks_top_actuation_point(row, col);
            value_data[2]            = (actuation_point >> 8) & 0xFF; // High byte
            value_data[3]            = actuation_point & 0xFF;        // Low byte
            break;
        }
        case id_dks_bottom_actuation_point: {
            // Handle getting DKS bottom actuation point
            uint8_t  row             = value_data[0]; // byte 3
            uint8_t  col             = value_data[1]; // byte 4
            uint16_t actuation_point = get_dks_bot_actuation_point(row, col);
            value_data[2]            = (actuation_point >> 8) & 0xFF; // High byte
            value_data[3]            = actuation_point & 0xFF;        // Low byte
            break;
        }
            // case id_dks_config: {
            //     // Handle getting DKS configuration
            //     uint8_t   row        = value_data[0]; // byte 3
            //     uint8_t   col        = value_data[1]; // byte 4
            //     uint8_t   nDksKey    = value_data[2]; // byte 5
            //     uint8_t   nKeyConfig = value_data[3]; // byte 6
            //     dks_key_t dks_key    = get_dks_key(row, col);
            //     break;
            // }
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