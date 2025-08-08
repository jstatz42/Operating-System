#ifndef KEYBOARD_H

#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define L_SHIFT_PRESSED 0x2A
#define L_SHIFT_RELEASED 0xAA
#define R_SHIFT_PRESSED 0x36
#define R_SHIFT_RELEASED 0xB6
#define CAPS_LOCK_PRESSED 0x3A
#define CAPS_LOCK_RELEASED 0xBA
#define ENABLED 1
#define DISABLED 0
#define CONTINUE 0
#define STOP 1

void executeKey();
void enableLShift();
void disableLShift();
void enableRShift();
void disbaleRShift();
void enableCapsLock();
void disableCapsLock();
uint8_t capitalEnabled();
void switchCapsLock();
uint8_t checkForSpecialKeys(uint8_t);
bool isLowerLetter(char);
#endif
