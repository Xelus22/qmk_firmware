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

#pragma once

// uses the VIA custom channel
// if you need to move the custom options further,
// you can change the VIA_CUSTOM_OPTION_START here
#ifndef VIA_CUSTOM_OPTION_START
#    define VIA_CUSTOM_OPTION_START (1)
#endif

enum via_enums {
// clang-format off
    // diagnostic
    id_get_matrix_scan_rate = VIA_CUSTOM_OPTION_START,
    id_get_raw_value,
    id_get_raw_value_multi,
    // switch LUT
    id_switch_lut,
    id_switch_lut_table,
    id_get_switch_lut_options,
    id_get_switch_lut_name,
    id_get_switch_max_distance,
    // calibration
    id_top_out_calibration,
    id_bottom_out_calibration,
    id_reset_calibration,
    id_get_calibration_data,
    // modes
    id_actuation_mode,
    id_reset_mode,
    id_static_actuation_press_point,
    id_static_actuation_release_point,
    id_reset_static_actuation,
    id_dynamic_activate_threshold,
    id_dynamic_press_hysteresis,
    id_dynamic_release_hysteresis,
    id_reset_dynamic_actuation,
    id_reset_dks_actuation,
    // dks
    id_dks_num,
    id_dks_top_actuation_point,
    id_dks_bottom_actuation_point,
    id_dks_config,
    id_reset_dks_config,

    id_end_via_enums,

    // clang-format on
};