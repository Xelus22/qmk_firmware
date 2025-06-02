
/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#pragma once

// for saving to eeprom
typedef struct PACKED {
    // key number for DKS mapping - max 256 - limited to 10 atm anyway
    uint8_t dks_num;
    uint8_t mode;
    // calibration values
    uint16_t top_out_calibration;
    uint16_t top_out_hysteresis;
    uint16_t bottom_out_calibration;
    uint16_t bottom_out_hysteresis;
    // static actuation values
    uint16_t static_actuation_point;
    uint16_t static_actuation_hysteresis;
    // dynamic actuation values
    uint16_t dynamic_activate_threshold;
    uint16_t dynamic_press_hysteresis;
    uint16_t dynamic_release_hysteresis;
    // dks actuation points
    uint16_t dks_top_actuation_point;
    uint16_t dks_bot_actuation_point;
    // re-use press-hysteresis and release-hysteresis for top/bottom actuation
} per_key_analog_config; /* 24 bytes */
_Static_assert(sizeof(per_key_analog_config) == 24, "Size mismatch");

// for use in RAM
typedef struct PACKED {
    /* For individual analog key data */
    uint16_t raw;
    uint16_t prev;
    uint16_t lastChangeRaw; // for use in dynamic actuation
} analog_key_t;
extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];
