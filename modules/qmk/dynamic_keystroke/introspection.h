#include <stdint.h>

typedef struct dynamic_keystroke_t {
    uint16_t pressKeycode;
    uint16_t releaseKeycode;
} dynamic_keystroke_t;

#define MAX_DYNAMIC_KEYSTROKE_PAIRS 10

uint16_t                                   dynamic_keystroke_count_raw(void);
__attribute__((weak)) uint16_t             dynamic_keystroke_count(void);
dynamic_keystroke_t*                       dynamic_keystroke_get_raw(uint16_t index);
__attribute__((weak)) dynamic_keystroke_t* dynamic_keystroke_get(uint16_t index);