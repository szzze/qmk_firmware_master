/* Copyright (C) 2023 sze - Monsgeek M1 Iso
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

#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

// DEFINE MACROS
#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])

enum __layers {
    WIN_B,
    WIN_FN
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

#define CAPS_LAYER MT(KC_CAPS, KC_NO)



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_all( /* Base */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS,          KC_PGUP,
        CAPS_LAYER, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_NUHS,  KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(WIN_FN),KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
        ),

    [WIN_FN] = LAYOUT_all( /* Stuff */
        _______, KC_NUM_LOCK, KC_PSLS, KC_PAST, KC_PMNS, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______,           RESET,
        _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,           KC_MPLY,
        _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______, _______, KC_INS,  _______, KC_PSCR,_______, _______, _______,           KC_MNXT,
        _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______, _______, _______, RGB_HUD, RGB_HUI, _______, _______, _______, _______,           KC_MPRV,
        _______, KC_KP_0, KC_KP_DOT, _______, KC_CALC, _______, _______, _______, KC_MUTE, RGB_VAD, RGB_VAI, RGB_TOG,          _______,  RGB_MOD, KC_MSTP,
        _______, _______, _______,                   _______,                            KC_APP, _______, KC_INS,          RGB_SPD,  RGB_RMOD, RGB_SPI
        ),
};


// clang-format on

// change layers on tap capslock key
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CAPS_LAYER:
            if (record->tap.count && record->event.pressed) {
                layer_invert(WIN_FN); // intercept tap function to change layer
            } else if (record->event.pressed) {
                tap_code16(KC_CAPS); // Intercept hold function to send Caps
            }
            return false;
    }
    return true;
}



// RGB change on layer
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state)) {
        case 1:
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_YELLOW);
            }
            break;
        default:
            break;
    }

    if(IS_LED_ON(host_keyboard_leds(), USB_LED_CAPS_LOCK))
    {
        for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_CAPS); i++) {
            rgb_matrix_set_color(LED_LIST_CAPS[i], RGB_RED);
        }
    }
    return false;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_B] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_FN] = { ENCODER_CCW_CW(RGB_VAI, RGB_VAD) }
};
#endif

