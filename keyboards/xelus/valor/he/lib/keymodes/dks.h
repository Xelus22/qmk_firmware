#include <stdint.h>
#include <stdbool.h>

#pragma once

typedef enum {
    DKS_HIT_NONE = 0, // no DKS state
    DKS_HIT_TOP_PRESS, // top press state
    DKS_HIT_TOP_RELEASE, // top release state
    DKS_HIT_BOT_PRESS, // bottom press state
    DKS_HIT_BOT_RELEASE, // bottom release state
} dks_hit_t; // 1 byte
_Static_assert(sizeof(dks_hit_t) == 1, "Size mismatch for dks_key_t");

typedef enum {
    DKS_REGION_BEFORE_TOP = 0, // unpressed region
    DKS_REGION_BETWEEN_TOP_BOTTOM, // top press region
    DKS_REGION_AFTER_BOTTOM, // bottom press region
} dks_region_t; // 1 byte
_Static_assert(sizeof(dks_region_t) == 1, "Size mismatch for dks_key_t");

typedef struct PACKED {
    dks_hit_t hit; // current DKS state - internal state machine use
    dks_region_t region; // DKS region - set by the matrix scan
    uint16_t topPress;
    uint16_t topRelease;
    uint16_t botPress;
    uint16_t botRelease;
} dks_key_t; // 10 bytes
_Static_assert(sizeof(dks_key_t) == 10, "Size mismatch for dks_key_t");

#ifndef MAX_DKS_KEYS
#    define MAX_DKS_KEYS 10 // maximum number of DKS keys, can be changed if needed
#endif

extern dks_key_t dks_keys[MAX_DKS_KEYS];

void dks_init(dks_key_t *dks_keys, uint8_t size);
void dks_set_key_top_press(uint8_t idx, uint16_t topPress);
void dks_set_key_top_release(uint8_t idx, uint16_t topRelease);
void dks_set_key_bot_press(uint8_t idx, uint16_t botPress);
void dks_set_key_bot_release(uint8_t idx, uint16_t botRelease);
bool dks_process_key_hit(uint8_t row, uint8_t col, dks_hit_t hit);
bool dks_process_key_state(uint8_t row, uint8_t col, dks_region_t currRegion);
