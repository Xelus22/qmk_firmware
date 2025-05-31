#include <stdint.h>

typedef struct PACKED {
    uint16_t press_keycode;
    uint16_t release_keycode;
    uint8_t behaviour;
} dynamic_keystroke_t;

typedef enum {
    DKS_BEHAVIOUR_TAP = 0,     // Default behaviour: tap the press keycode on press, release keycode on release
    DKS_BEHAVIOUR_PRESS_HOLD,  // Hold the press keycode on press, release keycode on release AND tap the release keycode on release
} dynamic_keystroke_behaviour_t;

#define MAX_DYNAMIC_KEYSTROKE_PAIRS 10

uint16_t                   dynamic_keystroke_count_raw(void);
uint16_t                   dynamic_keystroke_count(void);
const dynamic_keystroke_t* dynamic_keystroke_get_raw(uint16_t index);
const dynamic_keystroke_t* dynamic_keystroke_get(uint16_t index);