// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



enum layer_names {
    _QWERTY, _COLEMAK, _NUM, _NAV, _FUN
};

enum custom_keycodes {
    SS_NOT_EQUAL = SAFE_RANGE,
    SS_R_IN
};





// ================================== keymap ======================================= //

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ] │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┘
     * │Sft│ z │ x │ c │ v │ b │ n │ m │ , │ . │┌─────┐
     * ├───┴┬──┴───┴───┴───┴───┴───┴───┴───┴───┘│  /  │
     * │Ctrl│┌───┬───────────────────────────┬──┴┐    │
     * └────┘│Win│           Spc\Alt         │Cnl│    │
     *       └───┴───────────────────────────┴───┴────┘
     */
    [_QWERTY] = LAYOUT_sevenu(
        KC_RBRC,           KC_Q,      KC_W,     KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,
        LT(_NAV,KC_GRV),   KC_A,      KC_S,     KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_LSFT,           KC_Z,      KC_X,     KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL,           KC_LGUI,                            LALT_T(KC_SPC),                      UG_NEXT
    ),
    [_COLEMAK] = LAYOUT_sevenu(
        KC_RBRC,           KC_Q,      KC_W,     KC_F,        KC_P,      KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,      KC_SCLN,    KC_LBRC,
        LT(_NAV,KC_GRV),   KC_A,      KC_R,     KC_S,        KC_T,      KC_G,     KC_M,     KC_N,     KC_E,     KC_I,      KC_O,       KC_QUOT,
        KC_LSFT,           KC_Z,      KC_X,     KC_C,        KC_D,      KC_V,     KC_K,     KC_H,     KC_COMM,  KC_DOT,    KC_SLSH,
        KC_LCTL,        KC_LGUI,                         LALT_T(KC_SPC),                      UG_NEXT
    ),
    [_NUM] = LAYOUT_sevenu(
        KC_TRNS,          KC_TRNS,    KC_7,     KC_8,     KC_9,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
        KC_TRNS,          KC_0,       KC_4,     KC_5,     KC_6,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
        KC_TRNS,          KC_TRNS,    KC_1,     KC_2,     KC_3,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS,          KC_TRNS,                         KC_TRNS,                            TG(_NUM)
    ),
    [_NAV] = LAYOUT_sevenu(
        KC_NO,        KC_NO,      A(KC_F4),    KC_NO,      C(KC_ENT),      KC_NO,     KC_HOME,        C(KC_LEFT),     C(KC_RIGHT),     KC_END,         KC_NO,    KC_NO,
        KC_NO,        KC_NO,      KC_NO,       KC_NO,      KC_NO,          KC_NO,     KC_LEFT,        KC_DOWN,        KC_UP,           KC_RGHT,        KC_NO,    KC_NO,
        KC_TRNS,      KC_NO,      KC_NO,       KC_NO,      KC_NO,          KC_NO,     S(KC_HOME),     RCS(KC_LEFT),  RCS(KC_RGHT),     S(KC_END),      KC_EXLM,
        KC_TRNS,      KC_TRNS,                           KC_TRNS,                      TG(_NAV)
    ),
    [_FUN] = LAYOUT_sevenu(
        KC_TRNS,          KC_F12,    KC_F7,     KC_F8,     KC_F9,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
        KC_TRNS,          KC_F10,    KC_F4,     KC_F5,      KC_F6,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,     KC_TRNS,
        KC_TRNS,          KC_F11,    KC_F1,     KC_F2,     KC_F3,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,
        KC_TRNS,          KC_TRNS,                         KC_TRNS,                            TG(_NUM)
    )
};

// ================================ custom ======================================== //

bool mods_shift_status = false;
bool mods_shift_status_buffer = false;
bool mods_ctrl_status = false;
bool mods_ctrl_status_buffer = false;
bool mods_alt_status = false;
bool mods_alt_status_buffer = false;
bool mods_gui_status = false;
bool mods_gui_status_buffer = false;


void matrix_scan_user(void) {

    // light up MODS status
    mods_shift_status_buffer = get_mods() & MOD_MASK_SHIFT;
    if (mods_shift_status != mods_shift_status_buffer) {
        mods_shift_status = mods_shift_status_buffer;
        rgblight_set_layer_state(0, mods_shift_status);
    }
    mods_ctrl_status_buffer = get_mods() & MOD_MASK_CTRL;
    if (mods_ctrl_status != mods_ctrl_status_buffer) {
        mods_ctrl_status = mods_ctrl_status_buffer;
        rgblight_set_layer_state(1, mods_ctrl_status);
    }
    mods_alt_status_buffer = get_mods() & MOD_MASK_ALT;
    if (mods_alt_status != mods_alt_status_buffer) {
        mods_alt_status = mods_alt_status_buffer;
        rgblight_set_layer_state(2, mods_alt_status);
    }
    mods_gui_status_buffer = get_mods() & MOD_MASK_GUI;
    if (mods_gui_status != mods_gui_status_buffer) {
        mods_gui_status = mods_gui_status_buffer;
        rgblight_set_layer_state(3, mods_gui_status);
    }
}


// lighting layers and status - setup for macOSl
const rgblight_segment_t PROGMEM _NUM_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {28, 15, HSV_CYAN}
);
const rgblight_segment_t PROGMEM _FUN_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {28, 15, HSV_CORAL}
);
const rgblight_segment_t PROGMEM _NAV_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {28, 15, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM _SHIFT_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM _CTRL_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM _ALT_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 2, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM _GUI_LED[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 3, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM _LAYERS_LED[] = RGBLIGHT_LAYERS_LIST(
    _SHIFT_LED,
    _CTRL_LED,
    _ALT_LED,
    _GUI_LED,
    _NUM_LED,
    _FUN_LED,
    _NAV_LED
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = _LAYERS_LED;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(5, layer_state_cmp(state, _FUN));
    rgblight_set_layer_state(6, layer_state_cmp(state, _NAV));
    return state;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [2] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [3] =   { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
    [4] =   { ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
};
#endif
