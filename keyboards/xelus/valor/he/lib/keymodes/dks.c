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

#include "dks.h"
#include "quantum.h"
#include "../analogConfig.h"

dks_key_t *dks_keys = analog_config.dks_keys; // Pointer to the DKS keys array

// need to hook into process_keycode_xxx()

void dks_init(dks_key_t *eeprom_dks_keys, uint8_t size) {
    // initialize the dks keys
    size = MIN(size, MAX_DKS_KEYS); // ensure we don't exceed the max size
    for (uint8_t i = 0; i < size; i++) {
        dks_keys[i].hit    = DKS_HIT_TOP_PRESS;     // initialize state to none
        dks_keys[i].region = DKS_REGION_BEFORE_TOP; // initialize region to before top
        for (uint8_t j = 0; j < NUM_DKS_CONFS_PER_KEY; j++) {
            dks_keys[i].key_configs[j].dks_keycode               = 0; // initialize keycode to 0
            dks_keys[i].key_configs[j].dist_config.top_press     = false;
            dks_keys[i].key_configs[j].dist_config.top_release   = false;
            dks_keys[i].key_configs[j].dist_config.bot_press     = false;
            dks_keys[i].key_configs[j].dist_config.bot_release   = false;
            dks_keys[i].key_configs[j].dist_config.active_region = 0;
        }
    }
}

// enable the key presses for the DKS key at index idx and config_idx
void dks_set_key_top_press(uint8_t idx, uint8_t config_idx, bool topPress) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.top_press = topPress;
    }
}
void dks_set_key_top_release(uint8_t idx, uint8_t config_idx, bool topRelease) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.top_release = topRelease;
    }
}
void dks_set_key_bot_press(uint8_t idx, uint8_t config_idx, bool botPress) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.bot_press = botPress;
    }
}
void dks_set_key_bot_release(uint8_t idx, uint8_t config_idx, bool botRelease) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.bot_release = botRelease;
    }
}

// get the region for the DKS key at index idx and config_idx
dks_region_t dks_get_key_region(uint8_t idx, uint8_t config_idx) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        return dks_keys[idx].region;
    }
    return 0; // return default region if out of bounds
}

// set regions
void dks_set_key_active_region(uint8_t idx, uint8_t config_idx, dks_region_t region) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.active_region |= (1 << region);
    }
}
bool dks_activate_hold_key(dks_region_t regionBitField, dks_activate_t state) {
    // check if the region is valid
    if (regionBitField == 0) {
        return false; // no region is active
    }

    switch (state) {
        case DKS_HIT_TOP_PRESS:
            if (regionBitField & DKS_REGION_MID_PRESS_MASK) {
                return true;
            };
            break;
        case DKS_HIT_BOT_PRESS:
            if (regionBitField & DKS_REGION_AFTER_BOTTOM_MASK) {
                return true;
            };
            break;
        case DKS_HIT_BOT_RELEASE:
            if (regionBitField & DKS_REGION_MID_RELEASE_MASK) {
                return true;
            };
            break;
        case DKS_HIT_TOP_RELEASE:
            // release will never activate a hold
            return false;
    }
    return false; // no valid state
}

bool dks_deactivate_hold_key(dks_region_t regionBitField, dks_activate_t state) {
    // check if the region is valid
    if (regionBitField == 0) {
        return false; // no region is active
    }

    switch (state) {
        case DKS_HIT_TOP_PRESS:
            // press will never deactivate a hold
            break;
        case DKS_HIT_BOT_PRESS:
            // deactive is the next region does not have the bottom mask
            if ((regionBitField & DKS_REGION_AFTER_BOTTOM_MASK) != DKS_REGION_AFTER_BOTTOM_MASK) {
                return true;
            };
            break;
        case DKS_HIT_BOT_RELEASE:
            if ((regionBitField & DKS_REGION_MID_RELEASE_MASK) != DKS_REGION_MID_RELEASE_MASK) {
                return true;
            };
            break;
        case DKS_HIT_TOP_RELEASE:
            if ((regionBitField & DKS_REGION_MID_RELEASE)) {
                return true;
            };
            break;
    }

    return false; // no valid state
}

// for use in process_keycode_xxx()
void dks_process_key_hit(dks_key_config_t *config, dks_activate_t *state) {
    // process the DKS key hit based on the state
    uint16_t keycode = config->dks_keycode; // get the keycode from the config

    switch (*state) {
        case DKS_HIT_TOP_PRESS:
            if (config->dist_config.top_press) {
                tap_code16(keycode); // send the keycode for top press
            }
            break;
        case DKS_HIT_BOT_PRESS:
            if (config->dist_config.bot_press) {
                tap_code16(keycode); // send the keycode for bottom press
            }

            break;
        case DKS_HIT_TOP_RELEASE:
            if (config->dist_config.top_release) {
                tap_code16(keycode); // send the keycode for top release
            }
            break;
        case DKS_HIT_BOT_RELEASE:
            if (config->dist_config.bot_release) {
                tap_code16(keycode); // send the keycode for bottom release
            }
            break;
        default:
            break; // no action for none state
    }

    dks_region_t region = config->dist_config.active_region; // get the active region

    if (dks_activate_hold_key(region, *state)) {
        // if the hold key is activated, register the keycode
        register_code16(keycode);
    }

    if (dks_deactivate_hold_key(region, *state)) {
        // if the hold key is deactivated, unregister the keycode
        unregister_code16(keycode);
    }
}

bool dks_process_key_state(uint8_t row, uint8_t col, dks_region_t prevRegion, dks_region_t currRegion) {
    // process the DKS key state based on the region
    if (prevRegion == currRegion) {
        return false; // no change in region, do nothing
    }

    uint8_t dks_idx = get_dks_num(row, col); // get the DKS index from the analog config

    if (dks_idx >= MAX_DKS_KEYS) {
        return false; // invalid DKS index
    }

    dks_key_t *dks_key = &dks_keys[dks_idx];

    // update the region
    dks_key->region = currRegion;

    // check if the region has changed
    // handle region change logic here
    // e.g. update hit state, etc.
    switch (prevRegion) {
        case DKS_REGION_BEFORE_TOP:
            if (currRegion == DKS_REGION_MID_PRESS) {
                // entering top press region
                dks_key->hit = DKS_HIT_TOP_PRESS;
            }
            break;
        case DKS_REGION_MID_PRESS:
            if (currRegion == DKS_REGION_BEFORE_TOP) {
                // exiting top press region
                dks_key->hit = DKS_HIT_TOP_RELEASE;
            } else if (currRegion == DKS_REGION_AFTER_BOTTOM) {
                // entering bottom press region
                dks_key->hit = DKS_HIT_BOT_PRESS;
            }
            break;
        case DKS_REGION_AFTER_BOTTOM:
            if (currRegion == DKS_REGION_MID_RELEASE) {
                // entering top press region
                dks_key->hit = DKS_HIT_BOT_RELEASE;
            }
            break;
        case DKS_REGION_MID_RELEASE:
            if (currRegion == DKS_REGION_AFTER_BOTTOM) {
                // exiting bottom press region
                dks_key->hit = DKS_HIT_BOT_PRESS;
            } else if (currRegion == DKS_REGION_BEFORE_TOP) {
                // entering top press region
                dks_key->hit = DKS_HIT_TOP_RELEASE;
            }
            break;
    }

    return true;
}
