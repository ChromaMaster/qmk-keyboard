#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <stdint.h>
#include <stdbool.h>

void keylogger_record_key_pressed(uint16_t keycode);
char keylogger_last_key_pressed(void);
const char* keylogger_last_keys_pressed(void);
void keylogger_toggle_priv_mode(void);

#endif  // KEYLOGGER_H