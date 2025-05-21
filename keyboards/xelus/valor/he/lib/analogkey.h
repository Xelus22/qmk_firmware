
/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#pragma once

// for saving to eeprom
typedef struct PACKED {
    uint8_t  unused;
    uint8_t  mode;
    uint16_t actuation_point;
    uint16_t press_sensitivity;
    uint16_t release_sensitivity;
    uint16_t actuation_hysteresis;
    uint16_t press_hysteresis;
    uint16_t release_hysteresis;
} per_key_analog_config; /* 14 bytes */
_Static_assert(sizeof(per_key_analog_config) == 14, "Size mismatch");
extern per_key_analog_config analog_config[MATRIX_ROWS][MATRIX_COLS];

// for use in RAM
typedef struct PACKED {
    /* For individual analog key data */
    uint16_t raw;
    uint16_t value;
    uint16_t topOut;
    uint16_t bottomOut;
    uint16_t offset;
    uint16_t extremum; // for use in dynamic actuation
} analog_key_t;
extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];
