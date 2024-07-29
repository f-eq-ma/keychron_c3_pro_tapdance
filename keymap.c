/* Adjusted by Robert Hayden with custom tap dance 
 * Removed Mac layers, made Windows default
 * Replaced keymap with one from my Frog setup
*/

/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum {
  TD_F12,
  TD_F11,
  TD_F10,
  TD_F9,
  TD_F8,
  TD_F7
};

void td_f12_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F12);
		unregister_code16(KC_F12);
	} else {
		SEND_STRING("string_here");
		reset_tap_dance(state);
	}
}

void td_f11_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F11);
		unregister_code16(KC_F11);
	} else {
		SEND_STRING("string_here");
		reset_tap_dance(state);
	}
}

void td_f10_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F10);
		unregister_code16(KC_F10);
	} else if (state->count ==2) {
		SEND_STRING("string1_here");
		reset_tap_dance(state);
	} else {
		SEND_STRING("string2_here");
		reset_tap_dance(state);
	}
}

void td_f9_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F9);
		unregister_code16(KC_F9);
	} else {
		SEND_STRING("string_here");

		reset_tap_dance(state);
	}
}

void td_f8_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F8);
		unregister_code16(KC_F8);
	} else {
		SEND_STRING("string_here");
		reset_tap_dance(state);
	}
}

void td_f7_func(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_F7);
		unregister_code16(KC_F7);
	} else {
		SEND_STRING("string_here");
		reset_tap_dance(state);
	}
}

//Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
	[TD_F7]  = ACTION_TAP_DANCE_FN(td_f7_func),
	[TD_F8]  = ACTION_TAP_DANCE_FN(td_f8_func),
	[TD_F9]  = ACTION_TAP_DANCE_FN(td_f9_func),
	[TD_F10] = ACTION_TAP_DANCE_FN(td_f10_func),
	[TD_F11] = ACTION_TAP_DANCE_FN(td_f11_func),
	[TD_F12] = ACTION_TAP_DANCE_FN(td_f12_func)
}; 


enum layers{
  WIN_BASE,
  WIN_FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, TD(TD_F7), TD(TD_F8), TD(TD_F9), TD(TD_F10), TD(TD_F11), TD(TD_F12), KC_F16, KC_F17,  KC_F19,
        KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,      KC_9,      KC_0,      KC_MINS,    KC_EQL,     KC_BSPC,    KC_INS, KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,      KC_O,      KC_P,      KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DEL, KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,      KC_L,      KC_SCLN,   KC_QUOT,    KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,    KC_RSFT,                         KC_UP,
        KC_LCTL, KC_LWIN, KC_LALT,                       KC_SPC,                            KC_RALT,   MO(WIN_FN), KC_APP,     KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_FN] = LAYOUT_tkl_ansi(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  KC_VOLD, KC_VOLU, KC_F14,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  BL_DOWN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______)
};

// clang-format on
void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }
    return true;
}

