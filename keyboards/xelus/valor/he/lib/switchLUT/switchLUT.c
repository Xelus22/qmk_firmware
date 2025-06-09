#include "switchLUT.h"

#include "duhuk_herz.h" // Include the specific switch LUT header

uint8_t switch_lut_picker = SWITCH_LUT_DUHUK_HERZ;


void set_switch_lut(switch_lut_picker_t lut) {
    switch (lut) {
        case SWITCH_LUT_DUHUK_HERZ:
            switch_lut_picker = SWITCH_LUT_DUHUK_HERZ;
            break;
        // Add cases for other switch LUTs here
        default:
            switch_lut_picker = SWITCH_LUT_END; // Default to end if no match
            break;
    }
}

uint16_t *get_switch_lut(switch_lut_picker_t lut) {
    switch (lut) {
        case SWITCH_LUT_DUHUK_HERZ:
            return (uint16_t *)switchLUT_duhuk_herz; // Cast to uint16_t pointer
        // Add cases for other switch LUTs here
        default:
            return NULL; // Return NULL if no match
    }
}


