#include "keylogger.h"

#include <stdbool.h>
#include <stdio.h>

static char last_key_pressed = ' ';
static char last_keys_pressed[6] = {' ', ' ', ' ', ' ', ' ', '\0'};
static int keys_pressed_index = 0;
static bool priv_mode = true;

// clang-format off
static const char keycode_to_key[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};
// clang-format on

void keylogger_record_key_pressed(uint16_t keycode) {
    if (keycode >= 60) {
        return;
    }

    // Record the last key pressed or '*' if in priv mode
    if (priv_mode) {
        last_key_pressed = '*';
    } else {
        last_key_pressed = keycode_to_key[keycode];
    }

    // Clear the buffer
    if (keys_pressed_index == sizeof(last_keys_pressed) - 1) {
        keys_pressed_index = 0;
        // Do not remove the `\0` at the end of the string
        for (int i = 0; i < sizeof(last_keys_pressed) - 2; i++) {
            last_keys_pressed[i] = ' ';
        }
    }

    last_keys_pressed[keys_pressed_index] = last_key_pressed;
    keys_pressed_index++;
}

char keylogger_last_key_pressed() {
    return last_key_pressed;
}

const char *keylogger_last_keys_pressed() {
    return last_keys_pressed;
}

void keylogger_toggle_priv_mode(void) {
    priv_mode = !priv_mode;
}