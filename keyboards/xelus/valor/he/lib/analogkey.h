
/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#pragma once

// for saving to eeprom
typedef struct PACKED {
    uint8_t  dksNum; // key number for DKS mapping - max 256
    uint8_t  mode;
    // calibration values
    uint16_t topOutCalibration;
    uint16_t topOutHysteresis; // auto calculated
    uint16_t bottomOutCalibration;
    uint16_t bottomOutHysteresis;  // auto calculated
    // static actuation values
    uint16_t staticActuationPoint;
    uint16_t staticActuationHysteresis; // auto calc???
    // dynamic actuation values
    uint16_t dynamicActivateThreshold;
    uint16_t dynamicPressHysteresis;
    uint16_t dynamicReleaseHysteresis;
    // dks actuation points
    uint16_t dksTopActuationPoint;
    uint16_t dksBotActuationPoint;
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
