#include "dks.h"
#include "../analogConfig.h"

dks_key_t dks_keys[MAX_DKS_KEYS] = {0};

// need to hook into process_keycode_xxx()

void dks_init(dks_key_t *eeprom_dks_keys, uint8_t size) {
    // initialize the dks keys
    size = MIN(size, MAX_DKS_KEYS); // ensure we don't exceed the max size
    for (uint8_t i = 0; i < size; i++) {
        dks_keys[i].hit = DKS_HIT_NONE; // initialize state to none
        dks_keys[i].region = DKS_REGION_BEFORE_TOP; // initialize region to before top
        dks_keys[i].topPress = eeprom_dks_keys[i].topPress;
        dks_keys[i].topRelease = eeprom_dks_keys[i].topRelease;
        dks_keys[i].botPress = eeprom_dks_keys[i].botPress;
        dks_keys[i].botRelease = eeprom_dks_keys[i].botRelease;
    }
}

void dks_set_key_top_press(uint8_t idx, uint16_t topPress){
    if (idx < MAX_DKS_KEYS) {
        dks_keys[idx].topPress = topPress;
    }
}
void dks_set_key_top_release(uint8_t idx, uint16_t topRelease)
{
    if (idx < MAX_DKS_KEYS) {
        dks_keys[idx].topRelease = topRelease;
    }
}
void dks_set_key_bot_press(uint8_t idx, uint16_t botPress)
{
    if (idx < MAX_DKS_KEYS) {
        dks_keys[idx].botPress = botPress;
    }
}
void dks_set_key_bot_release(uint8_t idx, uint16_t botRelease)
{
    if (idx < MAX_DKS_KEYS) {
        dks_keys[idx].botRelease = botRelease;
    }
}

bool dks_process_key_hit(uint8_t row, uint8_t col, dks_hit_t hit)
{
    // get the raw value of the key and compare to the DKS keys
    uint8_t dks_idx = analog_config[row][col].dksNum; // get the DKS index for the key

    if (dks_idx >= MAX_DKS_KEYS) {
        return false; // invalid DKS index
    }

    // dks_state_t current_state = dks_keys[dks_idx].state;

    // uint16_t topPointRaw = get_dks_top_actuation_point(row, col);
    // uint16_t botPointRaw = get_dks_bot_actuation_point(row, col);
    return false;
}

bool dks_process_key_state(uint8_t row, uint8_t col, dks_region_t currRegion) 
{
    // process the DKS key state based on the region
    uint8_t dks_idx = analog_config[row][col].dksNum; // get the DKS index for the key
    dks_region_t prevRegion = dks_keys[dks_idx].region; // get the previous region

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
                if (currRegion == DKS_REGION_BETWEEN_TOP_BOTTOM) {
                    // entering top press region
                    dks_key->hit = DKS_HIT_TOP_PRESS;
                    return true;
                }
                break;

            case DKS_REGION_BETWEEN_TOP_BOTTOM:
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
                if (currRegion == DKS_REGION_BETWEEN_TOP_BOTTOM) {
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
