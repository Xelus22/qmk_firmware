#include "switchLUT.h"

#include "duhuk_herz.h" // Include the specific switch LUT header

uint8_t selectedSwitchLUT = DEFAULT_SWITCH_LUT;

// copy of the current switch LUT in RAM
uint16_t switch_lut[LUT_SIZE] = {0};

void set_switch_lut(switch_lut_picker_t lut) {
    uint16_t *pSwitchLUT = NULL;

    switch (lut) {
        case SWITCH_LUT_DUHUK_HERZ:
            selectedSwitchLUT = SWITCH_LUT_DUHUK_HERZ;
            pSwitchLUT = switchLUT_duhuk_herz; // Assign the pointer to the specific LUT
            break;
        // Add cases for other switch LUTs here
        default:
            selectedSwitchLUT = SWITCH_LUT_END; // Default to end if no match
            break;
    }

    for (uint16_t i = 0; i < LUT_SIZE; i++) {
        switch_lut[i] = pgm_read_word(&pSwitchLUT[i]); // Read from PROGMEM into the switch_lut array
    }
}

uint16_t get_switch_lut_value(uint16_t raw_value) {
    if (raw_value >= LUT_SIZE) {
        return 0; // Return 0 or handle out-of-bounds access
    }
    return switch_lut[raw_value]; // Return the value from the LUT based on the raw value
}


