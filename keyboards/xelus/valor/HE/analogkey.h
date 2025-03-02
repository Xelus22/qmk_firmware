
/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t analog_key_modes;
enum { dynamic_actuation = 0, continuous_dynamic_actuation, static_actuation, flashing };

/* global struct to save keypress logic params */
typedef struct {
    uint16_t actuation_point;
    uint16_t press_sensitivity;
    uint16_t release_sensitivity;
    uint16_t press_hysteresis;
    uint16_t release_hysteresis;
    uint8_t  mode;
} analog_config; /* 11 bytes */
_Static_assert(sizeof(analog_config) == 11, "Size mismatch");

typedef struct {
    /* For individual analog key data */
    uint16_t raw;
    uint16_t value;
    uint16_t topOut;
    uint16_t bottomOut;
    uint16_t offset;
    bool     continuous_dynamic_actuation;
} analog_key_t;
extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];
