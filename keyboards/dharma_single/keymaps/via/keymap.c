/* Copyright 2018 Jason Williams (Wilba)
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

// VIA layout for Dharma
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Default layer
[0] = LAYOUT_all(
	KC_LGUI, KC_A,
	KC_B, KC_C      
),

// Fn1 Layer
[1] = LAYOUT_all(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS		 
),

// Fn2 Layer
[2] = LAYOUT_all(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS	 
),

// Fn3 Layer
[3] = LAYOUT_all(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS		 
)
};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(B7);
  setPinOutput(F0);
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(F0);
    } else {
        writePinLow(F0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(B7);
    } else {
        writePinLow(B7);
    }
}

// uint32_t layer_state_set_user(uint32_t state) {
//     switch (biton32(state)) {
//       case 1:
//         writePinHigh(D1);
//         break;
//       default: //  for any other layers, or the default layer
//         writePinLow(D1);
//         break;
//       }
//     return state;
// }