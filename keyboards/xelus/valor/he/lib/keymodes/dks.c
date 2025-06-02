#include "dks.h"
#include "quantum.h"
#include "../analogConfig.h"

dks_key_t dks_keys[MAX_DKS_KEYS] = {0};

// need to hook into process_keycode_xxx()

void dks_init(dks_key_t *eeprom_dks_keys, uint8_t size) {
    // initialize the dks keys
    size = MIN(size, MAX_DKS_KEYS); // ensure we don't exceed the max size
    for (uint8_t i = 0; i < size; i++) {
        dks_keys[i].hit    = DKS_HIT_TOP_PRESS;     // initialize state to none
        dks_keys[i].region = DKS_REGION_BEFORE_TOP; // initialize region to before top
        for (uint8_t j = 0; j < NUM_DKS_CONFS_PER_KEY; j++) {
            dks_keys[i].key_configs[j].dks_keycode             = 0; // initialize keycode to 0
            dks_keys[i].key_configs[j].dist_config.top_press   = false;
            dks_keys[i].key_configs[j].dist_config.top_release = false;
            dks_keys[i].key_configs[j].dist_config.bot_press   = false;
            dks_keys[i].key_configs[j].dist_config.bot_release = false;
            dks_keys[i].key_configs[j].dist_config.start_state = DKS_HIT_TOP_PRESS;
            dks_keys[i].key_configs[j].dist_config.end_state   = DKS_HIT_TOP_PRESS;
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

// set regions
void dks_set_key_start_region(uint8_t idx, uint8_t config_idx, dks_state_t startState) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.start_state = startState;
    }
}
void dks_set_key_end_region(uint8_t idx, uint8_t config_idx, dks_state_t endState) {
    if (idx < MAX_DKS_KEYS && config_idx < NUM_DKS_CONFS_PER_KEY) {
        dks_keys[idx].key_configs[config_idx].dist_config.end_state = endState;
    }
}

// for use in process_keycode_xxx()
void dks_process_key_hit(dks_key_config_t *config, dks_state_t *state) {
    // process the DKS key hit based on the state
    uint16_t keycode = config->dks_keycode; // get the keycode from the config

    dks_state_t startState = config->dist_config.start_state; // get the start region
    dks_state_t endState   = config->dist_config.end_state;   // get the end region

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

    // check the start/end states
    if (*state == startState) {
        register_code16(keycode);
    }

    if (*state == endState) {
        unregister_code16(keycode);
    }
}

bool dks_process_key_state(uint8_t row, uint8_t col, dks_region_t currRegion) {
    // process the DKS key state based on the region
    uint8_t      dks_idx    = analog_config[row][col].dks_num; // get the DKS index for the key
    dks_region_t prevRegion = dks_keys[dks_idx].region;       // get the previous region

    if (dks_idx >= MAX_DKS_KEYS) {
        return false; // invalid DKS index
    }

    dks_key_t *dks_key = &dks_keys[dks_idx];

    // update the region
    dks_key->region = currRegion;

    // check if the region has changed
    if (prevRegion != currRegion) {
        // handle region change logic here
        // e.g. update hit state, etc.
        switch (prevRegion) {
            case DKS_REGION_BEFORE_TOP:
                if (currRegion == DKS_REGION_MID_PRESS) {
                    // entering top press region
                    dks_key->hit = DKS_HIT_TOP_PRESS;
                    return true;
                }
                break;

            case DKS_REGION_MID_PRESS:
                if (currRegion == DKS_REGION_BEFORE_TOP) {
                    // exiting top press region
                    dks_key->hit = DKS_HIT_TOP_RELEASE;
                    return true;
                } else if (currRegion == DKS_REGION_AFTER_BOTTOM) {
                    // entering bottom press region
                    dks_key->hit = DKS_HIT_BOT_PRESS;
                    return true;
                }
                break;

            case DKS_REGION_AFTER_BOTTOM:
                if (currRegion == DKS_REGION_MID_RELEASE) {
                    // entering top press region
                    dks_key->hit = DKS_HIT_BOT_RELEASE;
                    return true;
                }
                break;

            default:
                break; // no change in region
        }
    }

    return false;
}
