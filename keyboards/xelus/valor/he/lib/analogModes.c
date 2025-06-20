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

#include "analogModes.h"
#include "analogConfig.h"
#include "analogkey.h"
#include "calibration.h"
#include "keymodes/dks.h"
#include "print.h"

// get mode for a key
uint8_t get_mode(uint8_t row, uint8_t col) {
    return get_analog_key_mode(row, col);
}

// set mode for a key
void set_mode(uint8_t row, uint8_t col, uint8_t mode) {
    set_analog_key_mode(row, col, mode);
}

bool process_static_actuation(bool bPrevState, uint8_t row, uint8_t col) {
    // static actuation logic
    uint16_t raw_value = keysRaw[row][col];
    if (raw_value < get_static_actuation_release_point(row, col)) {
        return false; // not pressed
    }
    if (raw_value > get_static_actuation_press_point(row, col)) {
        return true; // now pressed
    }

    return bPrevState; // no mans land keep prev state
}

bool process_dynamic_actuation(bool bPrevState, uint8_t row, uint8_t col) {
    // dynamic actuation logic
    uint16_t raw_value = keysRaw[row][col];

    // get the thresholds
    uint16_t activate_threshold = get_dynamic_activate_threshold(row, col);

    // make sure that we are below the activate threshold
    if (raw_value < activate_threshold) {
        return false;
    }

    uint16_t press_hysteresis   = get_dynamic_press_hysteresis(row, col);
    uint16_t release_hysteresis = get_dynamic_release_hysteresis(row, col);
    uint16_t top_out_hysteresis = get_top_out_calibration_hysteresis(row, col);

    if (bPrevState) {
        // pressed state

        // check lastChangeRaw currently is the lowest press point
        if (raw_value < lastChangeRaw[row][col] - release_hysteresis) {
            if (row == 5 && col == 3) {
                // uprintf("release\n");
            }
            // key release
            lastChangeRaw[row][col] = raw_value; // update last change raw
            return false;                        // not pressed
        }

        // update the last change raw if the current raw value is higher
        if (raw_value > lastChangeRaw[row][col] + top_out_hysteresis) {
            lastChangeRaw[row][col] = raw_value; // update last change raw
        }
    } else {
        // released state
        if (raw_value > lastChangeRaw[row][col] + press_hysteresis) {
            // key press
            if (row == 5 && col == 3) {
                // uprintf("press\n");
            }
            lastChangeRaw[row][col] = raw_value; // update last change raw
            return true;                         // now pressed
        }

        // update the last change raw if the current raw value is lower
        if (raw_value < lastChangeRaw[row][col] - top_out_hysteresis) {
            lastChangeRaw[row][col] = raw_value; // update last change raw
        }
    }

    return bPrevState; // no mans land keep prev state
}

bool process_continuous_dynamic_actuation(bool bPrevState, uint8_t row, uint8_t col) {
    // dynamic actuation logic
    uint16_t raw_value = keysRaw[row][col];
    // resuse the lastChangeRaw for dynamic actuation
    // use to check if it is in the top-out region

    // top bit is used to check the state
    bool     bState      = lastChangeRaw[row][col] & 0x8000; // get the state from the lastChangeRaw
    uint16_t extremumRaw = lastChangeRaw[row][col] & 0x7FFF;

    // get the thresholds
    uint16_t activate_threshold = get_dynamic_activate_threshold(row, col);

    bool bBelowActivateThreshold = (raw_value < activate_threshold);

    if (!bState && bBelowActivateThreshold) {
        // automatically resets the bState to 0 here
        // because we are stealing the top bit of the lastChangeRaw
        lastChangeRaw[row][col] = raw_value;
        return false;
    }
    
    uint16_t press_hysteresis   = get_dynamic_press_hysteresis(row, col);
    uint16_t release_hysteresis = get_dynamic_release_hysteresis(row, col);
    uint16_t top_out_hysteresis = get_top_out_calibration_hysteresis(row, col);


    if (bPrevState) {
        // pressed state

        // check lastChangeRaw currently is the lowest press point
        if (raw_value < extremumRaw - release_hysteresis) {
            if (row == 5 && col == 3) {
                // uprintf("release\n");
            }
            // key release
            if (bState) {
                raw_value |= 0x8000;
            }
            lastChangeRaw[row][col] = raw_value; // update last change raw
            return false;                        // not pressed
        }

        // update the last change raw if the current raw value is higher
        if (raw_value > extremumRaw + top_out_hysteresis) {
            if (bState) {
                raw_value |= 0x8000;
            }
            lastChangeRaw[row][col] = raw_value; // update last change raw
        }
    } else {
        // released state
        if (raw_value > extremumRaw + press_hysteresis) {
            // key press
            if (row == 5 && col == 3) {
                // uprintf("press\n");
            }

            if (!bState) {
                bState = true;
            }

            if (bState) {
                raw_value |= 0x8000;
            }
            lastChangeRaw[row][col] = raw_value; // update last change raw

            return true; // now pressed
        }

        // update the last change raw if the current raw value is lower
        if (raw_value < extremumRaw - top_out_hysteresis) {
            if (bState) {
                raw_value |= 0x8000;
            }
            lastChangeRaw[row][col] = raw_value; // update last change raw
        }
    }

    return bPrevState; // no mans land keep prev state
}

bool process_dks(uint8_t row, uint8_t col) {
    // process DKS logic
    uint16_t raw_value = keysRaw[row][col];

    // check which region the key is in
    uint16_t topPress      = get_dks_top_actuation_point(row, col);
    uint16_t botPress      = get_dks_bot_actuation_point(row, col);
    uint16_t topHysteresis = get_top_out_calibration_hysteresis(row, col);
    uint16_t botHysteresis = get_bottom_out_calibration_hysteresis(row, col);

    dks_region_t currentRegion;
    dks_region_t prevRegion = dks_get_key_region(row, col);

    if (raw_value < topPress - topHysteresis) {
        // in the unpressed region
        currentRegion = DKS_REGION_BEFORE_TOP;
    } else if (raw_value > botPress + botHysteresis) {
        // in the bottom pressed region
        currentRegion = DKS_REGION_AFTER_BOTTOM;
    } else if (topPress + topHysteresis <= raw_value && raw_value <= botPress - botHysteresis) {
        // in the middle pressed region
        currentRegion = DKS_REGION_MID_PRESS;
    } else {
        currentRegion = prevRegion;
    }

    return dks_process_key_state(row, col, prevRegion, currentRegion);
}

bool process_mode_key(analog_key_mode_t mode, bool bPrevState, uint8_t row, uint8_t col) {
    switch (mode) {
        case MODE_STATIC_ACTUATION:
            // process static actuation
            return process_static_actuation(bPrevState, row, col);
        case MODE_DYNAMIC_ACTUATION:
            // process dynamic actuation
            return process_dynamic_actuation(bPrevState, row, col);
        case MODE_CONTINUOUS_DYNAMIC_ACTUATION:
            // process continuous dynamic actuation
            return process_continuous_dynamic_actuation(bPrevState, row, col);
        case MODE_DYNAMIC_KEY_STROKE:
            return process_dks(row, col);
            break;
        // case MODE_ANALOG_HID_OUTPUT:
        //     // process analog HID output
        //     // do not ever output a key press
        //     return false;
        case MODE_CALIBRATION:
            // process calibration
            calibrate_bottom_out(row, col);
            break;
        default:
            break;
    }

    return false; // key has not changed state
}
