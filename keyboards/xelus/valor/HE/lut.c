#include "lut.h"

pin_t mux_lut(uint8_t mux) {
    switch (iteration) {
        case 0:
            return GPIOB_PIN6;
        case 1:
            return GPIOB_PIN7;
        case 2:
            return GPIOB_PIN8;
        default:
            return GPIOB_PIN6;
    }
}
