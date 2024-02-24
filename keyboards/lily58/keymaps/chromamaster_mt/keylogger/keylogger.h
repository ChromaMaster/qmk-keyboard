#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#include <stdint.h>

void keylogger_record_key_pressed(uint16_t keycode);
char keylogger_last_key_pressed(void);
const char* keylogger_last_keys_pressed(void);

#endif  // KEYLOGGER_H