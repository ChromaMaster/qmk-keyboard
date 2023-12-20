//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE
#ifndef OLED_C
#define OLED_C

#include "layers.h"
#include "keylogger/keylogger.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return OLED_ROTATION_270; // Vertical screen
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

void render_empty_line(void);
void render_caps_look(void);
void render_layer_state(void);
void render_last_key_pressed(void);
void render_last_keys_pressed(void);

// If you want to change the display of OLED, you need to change here
bool oled_task_user(void) {
    if (is_keyboard_master()) {

        render_caps_look();
        render_layer_state();
        
        render_empty_line();
        
        render_last_key_pressed();
        render_last_keys_pressed();

        return false;
    }

    oled_write(read_logo(), false);

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed){
        keylogger_record_key_pressed(keycode);
    }

    return true;
}

void render_empty_line(void) {
    oled_write_ln(PSTR(""), false);
}

void render_caps_look(void) {
    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR("-CAP-"), false);
        return;
    }

    oled_write_ln(PSTR(""), false);
}

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _ADJUST:
            oled_write_ln(PSTR(" ADJ "), false);
            break;
        case _LOWER:
            oled_write_P(PSTR(" LOW "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR(" RAI "), false);
            break;
        default:
            oled_write_P(PSTR(" BAS "), false);
            break;
    }
}

void render_last_key_pressed(void) {
    char str[6] = "";
    snprintf(str, sizeof(str), "  %c  ", keylogger_last_key_pressed());
    oled_write(str, false);
}

void render_last_keys_pressed(void) {
    oled_write(keylogger_last_keys_pressed(), false);
}

#endif // OLED_C
#endif // OLED_ENABLE