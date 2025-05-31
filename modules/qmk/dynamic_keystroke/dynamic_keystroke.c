// Copyright 2025 Harrison Chan (@xelus22)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "introspection.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

bool process_record_dynamic_keystroke(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_keystroke_kb(keycode, record)) {
        return false;
    }

    switch (keycode) { // This will do most of the grunt work with the keycodes.
        case COMMUNITY_MODULE_DYNAMIC_KEYSTROKE_0 ... COMMUNITY_MODULE_DYNAMIC_KEYSTROKE_9:
            uint16_t             index             = keycode - COMMUNITY_MODULE_DYNAMIC_KEYSTROKE_0;
            const dynamic_keystroke_t *dynamic_keystroke = dynamic_keystroke_get(index);

            if (record->event.pressed) {
                tap_code16(dynamic_keystroke->pressKeycode);
            } else {
                tap_code16(dynamic_keystroke->releaseKeycode);
            }
            return false;
    }
    return true;
}
