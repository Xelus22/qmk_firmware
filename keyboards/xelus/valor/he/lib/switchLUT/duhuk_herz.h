// LUT for duhuk herz switch

#pragma once

#include <stdint.h>
#include <math.h>
#include "switchLUT.h"
#include "progmem.h"

#define FUNC(x) (117.39 * log(0.0001215 * x) - 110.43)

// 1 distance unit = 0.0001mm
// 1000 distance units = 0.1mm
// 10000 distance units = 1mm
// 35000 distance units = 3.5mm

// basically non-linear mapping 0 - 1024 -> 0mm - 3.3mm

const uint16_t calculate_duhuk_herz(uint16_t raw_value) {
    // 0 raw value = 0 distance
    // 10000 raw value = 1mm distance
    // Calculate the value based on the raw value using the function
    // The function is derived from the characteristics of the duhuk herz switch
    return (uint16_t)(FUNC(raw_value));
}
