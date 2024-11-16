/* Copyright 2017 Jason Williams (Wilba)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dynamic_keymap.h"
#include "keymap_introspection.h"
#include "action.h"
#include "eeprom.h"
#include "progmem.h"
#include "send_string.h"
#include "keycodes.h"

#ifdef VIA_ENABLE
#    include "via.h"
#    define DYNAMIC_KEYMAP_EEPROM_START (VIA_EEPROM_CONFIG_END)
#else
#    include "eeconfig.h"
#    define DYNAMIC_KEYMAP_EEPROM_START (EECONFIG_SIZE)
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#else
#    define NUM_ENCODERS 0
#endif

#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_COUNT
#    define DYNAMIC_KEYMAP_MACRO_COUNT 16
#endif

#if DYNAMIC_KEYMAP_MACRO_COUNT > 256
#    pragma message STR(DYNAMIC_KEYMAP_MACRO_COUNT) " > 256"
#    error DYNAMIC_KEYMAP_MACRO_COUNT must be less than or equal to 256
#endif

#ifdef DYNAMIC_KEYMAP_MACRO_REPEAT_ENABLE
// create an array to hold the macro repeat data
// try to create a bitfield if possible for all macros to enable/disable repeat
// if it is 0, it should repeat indefinitely, until disabled - not for this, for the get repeat count
uint8_t macroRepeatCountdown[DYNAMIC_KEYMAP_MACRO_COUNT] = {0};

// time interval check since last macro sent
uint32_t macroLastSentTime[DYNAMIC_KEYMAP_MACRO_COUNT] = {0};

#    define NUM_MACRO_ENABLED_BITFIELDS (DYNAMIC_KEYMAP_MACRO_COUNT + 31 / 32)
uint32_t macroEnabledBitField[NUM_MACRO_ENABLED_BITFIELDS] = {0};
#endif

#ifndef TOTAL_EEPROM_BYTE_COUNT
#    error Unknown total EEPROM size. Cannot derive maximum for dynamic keymaps.
#endif

#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1)
#endif

#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > (TOTAL_EEPROM_BYTE_COUNT - 1)
#    pragma message STR(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) " > " STR((TOTAL_EEPROM_BYTE_COUNT - 1))
#    error DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is configured to use more space than what is available for the selected EEPROM driver
#endif

// Due to usage of uint16_t check for max 65535
#if DYNAMIC_KEYMAP_EEPROM_MAX_ADDR > 65535
#    pragma message STR(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) " > 65535"
#    error DYNAMIC_KEYMAP_EEPROM_MAX_ADDR must be less than 65536
#endif

// If DYNAMIC_KEYMAP_EEPROM_ADDR not explicitly defined in config.h,
#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_ADDR DYNAMIC_KEYMAP_EEPROM_START
#endif

// Dynamic encoders starts after dynamic keymaps
#ifndef DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#endif

// Dynamic macro header starts after dynamic encoders, but only when using ENCODER_MAP
#ifdef ENCODER_MAP_ENABLE
#    ifndef DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR
#        define DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR (DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * NUM_ENCODERS * 2 * 2))
#    endif // DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR
#else      // ENCODER_MAP_ENABLE
#    ifndef DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR
#        define DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR (DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR)
#    endif // DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR
#endif     // ENCODER_MAP_ENABLE

// Dynamic macros are stored after the keymaps and use what is available
#ifdef DYNAMIC_KEYMAP_MACRO_REPEAT_ENABLE
#    ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#        define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + (DYNAMIC_KEYMAP_MACRO_COUNT * sizeof(dynamic_macro_header_t)))
#    endif
#else
#    ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#        define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR)
#    endif
#endif

// Sanity check that dynamic keymaps fit in available EEPROM
// If there's not 100 bytes available for macros, then something is wrong.
// The keyboard should override DYNAMIC_KEYMAP_LAYER_COUNT to reduce it,
// or DYNAMIC_KEYMAP_EEPROM_MAX_ADDR to increase it, *only if* the microcontroller has
// more than the default.
_Static_assert((DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) - (DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR) >= 100, "Dynamic keymaps are configured to use more EEPROM than is available.");

// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_DELAY
#    define DYNAMIC_KEYMAP_MACRO_DELAY TAP_CODE_DELAY
#endif

uint8_t dynamic_keymap_get_layer_count(void) {
    return DYNAMIC_KEYMAP_LAYER_COUNT;
}

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    // TODO: optimize this with some left shifts
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR) + (layer * MATRIX_ROWS * MATRIX_COLS * 2) + (row * MATRIX_COLS * 2) + (column * 2);
}

uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return KC_NO;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address, (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + 1, (uint8_t)(keycode & 0xFF));
}

#ifdef ENCODER_MAP_ENABLE
void *dynamic_keymap_encoder_to_eeprom_address(uint8_t layer, uint8_t encoder_id) {
    return ((void *)DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR) + (layer * NUM_ENCODERS * 2 * 2) + (encoder_id * 2 * 2);
}

uint16_t dynamic_keymap_get_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return KC_NO;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = ((uint16_t)eeprom_read_byte(address + (clockwise ? 0 : 2))) << 8;
    keycode |= eeprom_read_byte(address + (clockwise ? 0 : 2) + 1);
    return keycode;
}

void dynamic_keymap_set_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address + (clockwise ? 0 : 2), (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + (clockwise ? 0 : 2) + 1, (uint8_t)(keycode & 0xFF));
}
#endif // ENCODER_MAP_ENABLE

void dynamic_keymap_reset(void) {
    // Reset the keymaps in EEPROM to what is in flash.
    for (int layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int column = 0; column < MATRIX_COLS; column++) {
                dynamic_keymap_set_keycode(layer, row, column, keycode_at_keymap_location_raw(layer, row, column));
            }
        }
#ifdef ENCODER_MAP_ENABLE
        for (int encoder = 0; encoder < NUM_ENCODERS; encoder++) {
            dynamic_keymap_set_encoder(layer, encoder, true, keycode_at_encodermap_location_raw(layer, encoder, true));
            dynamic_keymap_set_encoder(layer, encoder, false, keycode_at_encodermap_location_raw(layer, encoder, false));
        }
#endif // ENCODER_MAP_ENABLE
    }
}

void dynamic_keymap_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint16_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void    *source                     = (void *)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset);
    uint8_t *target                     = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void dynamic_keymap_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    uint16_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void    *target                     = (void *)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset);
    uint8_t *source                     = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column) {
    if (layer_num < DYNAMIC_KEYMAP_LAYER_COUNT && row < MATRIX_ROWS && column < MATRIX_COLS) {
        return dynamic_keymap_get_keycode(layer_num, row, column);
    }
    return KC_NO;
}

#ifdef ENCODER_MAP_ENABLE
uint16_t keycode_at_encodermap_location(uint8_t layer_num, uint8_t encoder_idx, bool clockwise) {
    if (layer_num < DYNAMIC_KEYMAP_LAYER_COUNT && encoder_idx < NUM_ENCODERS) {
        return dynamic_keymap_get_encoder(layer_num, encoder_idx, clockwise);
    }
    return KC_NO;
}
#endif // ENCODER_MAP_ENABLE

uint8_t dynamic_keymap_macro_get_count(void) {
    return DYNAMIC_KEYMAP_MACRO_COUNT;
}

uint16_t dynamic_keymap_macro_get_buffer_size(void) {
    return DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE;
}

#ifdef DYNAMIC_KEYMAP_MACRO_REPEAT_ENABLE
// internal helper to set the repeat bit enable/disable
void set_bit(uint32_t *bitfield, uint8_t bit) {
    bitfield[bit / 32] |= (1UL << (bit % 32));
}

void clear_bit(uint32_t *bitfield, uint8_t bit) {
    bitfield[bit / 32] &= ~(1UL << (bit % 32));
}

bool test_bit(uint32_t *bitfield, uint8_t bit) {
    return (bitfield[bit / 32] & (1UL << (bit % 32))) != 0;
}

void process_record_dynamic_keymap_macro_repeat(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    // check if the macro is enabled for repeat
    if (!test_bit(macroEnabledBitField, id)) {
        // enable the macro
        dynamic_keymap_macro_enable_repeat(id);
        // set to X, and then -1 when sent
        macroRepeatCountdown[id] = dynamic_keymap_macro_get_repeat_count(id);
    } else {
        // disable the macro
        dynamic_keymap_macro_disable_repeat(id);
        // reset all values to 0
        macroRepeatCountdown[id] = 0;
        macroLastSentTime[id]    = 0;
    }
}

void dynamic_keymap_macro_repeat_task(void) {
    // faster exit if none enabled
    // for (uint8_t i = 0; i < NUM_MACRO_ENABLED_BITFIELDS; i++) {
    //     if (macroEnabledBitField[i] != 0) {
    //         break;
    //     }
    //     return;
    // }

    // loop through all the bits in the bitfield
    for (uint8_t i = 0; i < DYNAMIC_KEYMAP_MACRO_COUNT; i++) {
        if (test_bit(macroEnabledBitField, i)) {
            // macro is enabled
            // check the timer for the macro
            uint32_t interval = dynamic_keymap_macro_get_repeat_interval(i);

            // check if the timer has elapsed the interval time
            if (macroLastSentTime[i] == 0 || macroLastSentTime[i] + interval <= timer_read32()) {
                // set the last sent time
                macroLastSentTime[i] = timer_read32();
                // send the macro
                dynamic_keymap_macro_send(i);

                // if 0, it should be repeated indefinitely
                // if 1, it should disable the macro after sending
                if (macroRepeatCountdown[i] == 1) {
                    // disable the macro
                    dynamic_keymap_macro_disable_repeat(i);
                    // reset the countdown
                    macroRepeatCountdown[i] = 0;
                    // reset the last sent time
                    macroLastSentTime[i] = 0;
                } else if (macroRepeatCountdown[i] == 0) {
                    // do nothing
                } else {
                    // normal operation
                    // decrement the countdown
                    macroRepeatCountdown[i] -= 1;
                }
            }
        }
    }
}

void dynamic_keymap_macro_enable_repeat(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    set_bit(macroEnabledBitField, id);
}

void dynamic_keymap_macro_disable_repeat(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    clear_bit(macroEnabledBitField, id);
}

uint16_t dynamic_keymap_macro_get_offset(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return UINT16_MAX;
    }

    void *source = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + id * sizeof(dynamic_macro_header_t) + sizeof(dynamic_macro_repeat_t));

    uint16_t offset = eeprom_read_word(source);
    return offset;
}

void dynamic_keymap_macro_get_repeat_data(uint8_t id, uint8_t *data) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    void    *source = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + id * sizeof(dynamic_macro_header_t));
    uint8_t *target = data;
    for (uint16_t i = 0; i < 10; i++) {
        *target = eeprom_read_byte(source);

        source++;
        target++;
    }
}

void dynamic_keymap_macro_set_repeat_data(uint8_t id, uint8_t repeatCount, uint32_t repeatInterval, uint16_t macroOffset) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    void *target = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + id * sizeof(dynamic_macro_header_t));

    dynamic_macro_repeat_t repeat = {
        .repeatCount      = repeatCount,
        .repeatIntervalHI = (repeatInterval >> 16) & 0xFF,
        .repeatIntervalMD = (repeatInterval >> 8) & 0xFF,
        .repeatIntervalLO = repeatInterval & 0xFF,
    };
    eeprom_update_dword(target, repeat.raw);

    target = (void *)(target + sizeof(dynamic_macro_repeat_t));
    eeprom_update_word(target, macroOffset);
}

uint8_t dynamic_keymap_macro_get_repeat_count(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return 0;
    }

    void *source = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + id * sizeof(dynamic_macro_header_t));

    uint8_t count = eeprom_read_byte(source);
    return count;
}

uint32_t dynamic_keymap_macro_get_repeat_interval(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return 0;
    }

    // The interval is stored as 3 bytes, so we can read in all 4 bytes at once
    void *source = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + id * sizeof(dynamic_macro_header_t));

    // stored as the bottom 3 bytes of a 32-bit value
    dynamic_macro_repeat_t repeat;
    repeat.raw = eeprom_read_dword(source);

    return repeat.repeatIntervalHI << 16 | repeat.repeatIntervalMD << 8 | repeat.repeatIntervalLO;
}

void dynamic_keymap_macro_repeat_reset(void) {
    void *p   = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_REPEAT_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_COUNT * sizeof(dynamic_macro_header_t));
    while (p != end) {
        eeprom_update_byte(p, 0);
        ++p;
    }
}
#endif

void dynamic_keymap_macro_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    void    *source = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *target = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void dynamic_keymap_macro_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    void    *target = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *source = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

void dynamic_keymap_macro_reset(void) {
    void *p   = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    while (p != end) {
        eeprom_update_byte(p, 0);
        ++p;
    }
}

void dynamic_keymap_macro_send(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    // Check the last byte of the buffer.
    // If it's not zero, then we are in the middle
    // of buffer writing, possibly an aborted buffer
    // write. So do nothing.
    void *p = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE - 1);
    if (eeprom_read_byte(p) != 0) {
        return;
    }

#ifdef DYNAMIC_KEYMAP_MACRO_REPEAT_ENABLE
    uint16_t offset = dynamic_keymap_macro_get_offset(id);
    if (offset == UINT16_MAX) {
        return;
    }
    p = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
#else
    // Skip N null characters
    // p will then point to the Nth macro
    p         = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    while (id > 0) {
        // If we are past the end of the buffer, then there is
        // no Nth macro in the buffer.
        if (p == end) {
            return;
        }
        if (eeprom_read_byte(p) == 0) {
            --id;
        }
        ++p;
    }
#endif

    // Send the macro string by making a temporary string.
    char data[8] = {0};
    // We already checked there was a null at the end of
    // the buffer, so this cannot go past the end
    while (1) {
        data[0] = eeprom_read_byte(p++);
        data[1] = 0;
        // Stop at the null terminator of this macro string
        if (data[0] == 0) {
            break;
        }
        if (data[0] == SS_QMK_PREFIX) {
            // Get the code
            data[1] = eeprom_read_byte(p++);
            // Unexpected null, abort.
            if (data[1] == 0) {
                return;
            }
            if (data[1] == SS_TAP_CODE || data[1] == SS_DOWN_CODE || data[1] == SS_UP_CODE) {
                // Get the keycode
                data[2] = eeprom_read_byte(p++);
                // Unexpected null, abort.
                if (data[2] == 0) {
                    return;
                }
                // Null terminate
                data[3] = 0;
            } else if (data[1] == SS_DELAY_CODE) {
                // Get the number and '|'
                // At most this is 4 digits plus '|'
                uint8_t i = 2;
                while (1) {
                    data[i] = eeprom_read_byte(p++);
                    // Unexpected null, abort
                    if (data[i] == 0) {
                        return;
                    }
                    // Found '|', send it
                    if (data[i] == '|') {
                        data[i + 1] = 0;
                        break;
                    }
                    // If haven't found '|' by i==6 then
                    // number too big, abort
                    if (i == 6) {
                        return;
                    }
                    ++i;
                }
            }
        }
        send_string_with_delay(data, DYNAMIC_KEYMAP_MACRO_DELAY);
    }
}
