#include <stdint.h>
#include <stdbool.h>
#include "compiler_support.h"
#include "util.h"

#pragma once

#ifndef NUM_DKS_CONFS_PER_KEY
#    define NUM_DKS_CONFS_PER_KEY 4 // number of DKS configurations per key
#endif

// this ends up like a reverse state machine
// where we have the before and after states, but we need to
// process HOW we got to the state

typedef enum {
    DKS_HIT_TOP_PRESS = 0, // top press state
    DKS_HIT_BOT_PRESS,     // bottom press state
    DKS_HIT_BOT_RELEASE,   // bottom release state
    DKS_HIT_TOP_RELEASE,   // top release state
} dks_state_t;             // 1 byte
STATIC_ASSERT(sizeof(dks_state_t) == 1, "Size mismatch for dks_state_t");

typedef enum {
    DKS_REGION_BEFORE_TOP = 0, // unpressed region
    DKS_REGION_MID_PRESS,      // top press middle region
    DKS_REGION_AFTER_BOTTOM,   // bottom press region
    DKS_REGION_MID_RELEASE,    // release press middle region
} dks_region_t;                // 1 byte
STATIC_ASSERT(sizeof(dks_region_t) == 1, "Size mismatch for dks_region_t");

// active region mask
#define DKS_REGION_BEFORE_TOP_MASK 0x01 // mask for before top region
#define DKS_REGION_MID_PRESS_MASK  0x02 // mask for mid press region
#define DKS_REGION_AFTER_BOTTOM_MASK 0x04 // mask for after bottom region
#define DKS_REGION_MID_RELEASE_MASK 0x08 // mask for mid release region

typedef struct PACKED {
    bool         top_press : 1;     // true if the top press is active
    bool         top_release : 1;   // true if the top release is active
    bool         bot_press : 1;     // true if the bottom press is active
    bool         bot_release : 1;   // true if the bottom release is active
    dks_region_t active_region : 2; // region where the hold is active
    dks_state_t  reserved : 2;      // reserved for future use
} dks_dist_config_t;
STATIC_ASSERT(sizeof(dks_dist_config_t) == 1, "Size mismatch for dks_key_t");

typedef struct PACKED {
    uint16_t          dks_keycode; // DKS keycode - used for key mapping
    dks_dist_config_t dist_config; // DKS distance configuration
} dks_key_config_t;
STATIC_ASSERT(sizeof(dks_key_config_t) == 3, "Size mismatch for dks_key_t");

typedef struct PACKED {
    dks_state_t      hit;    // current DKS state - internal state machine use
    dks_region_t     region; // DKS region - set by the matrix scan
    dks_key_config_t key_configs[NUM_DKS_CONFS_PER_KEY];
} dks_key_t; // 14 bytes
STATIC_ASSERT(sizeof(dks_key_t) == (1 + 1 + 3 * NUM_DKS_CONFS_PER_KEY), "Size mismatch for dks_key_t");

#ifndef MAX_DKS_KEYS
#    define MAX_DKS_KEYS 10 // maximum number of DKS keys, can be changed if needed
#endif

void dks_init(dks_key_t *dks_keys, uint8_t size);
void dks_set_key_top_press(uint8_t idx, uint8_t config_idx, bool topPress);
void dks_set_key_top_release(uint8_t idx, uint8_t config_idx, bool topRelease);
void dks_set_key_bot_press(uint8_t idx, uint8_t config_idx, bool botPress);
void dks_set_key_bot_release(uint8_t idx, uint8_t config_idx, bool botRelease);

dks_region_t dks_get_key_region(uint8_t idx, uint8_t config_idx);

void dks_set_key_start_region(uint8_t idx, uint8_t config_idx, dks_state_t startState);
void dks_set_key_end_region(uint8_t idx, uint8_t config_idx, dks_state_t endState);

void dks_process_key_hit(dks_key_config_t *config, dks_state_t *state);
bool dks_process_key_state(uint8_t row, uint8_t col, dks_region_t prevRegion, dks_region_t currRegion);
