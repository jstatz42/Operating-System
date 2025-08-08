
#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include "../../libc/include/io.h"
#include "../../kernel/vga/vga.h"


static char scanCodes[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u' ,'i', 'o', 'p', '[', ']',
	'\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' '};



static uint8_t lShift = DISABLED;
static uint8_t rShift = DISABLED;
static uint8_t capsLock = DISABLED;


uint8_t checkForSpecialKeys(uint8_t code) {
	
	switch (code) {
		case L_SHIFT_PRESSED:
			enableLShift();
			return STOP;
		case L_SHIFT_RELEASED:
			disableLShift();
			return STOP;
		case R_SHIFT_PRESSED:
			enableRShift();
			return STOP;
		case R_SHIFT_RELEASED:
			disbaleRShift();
			return STOP;
		case CAPS_LOCK_PRESSED:
			switchCapsLock();
			return STOP;

	}

	return CONTINUE;
}


void executeKey() {

	uint8_t keyCode = inb(0x60);

	if (checkForSpecialKeys(keyCode)) {
		return;
	}

	// do not print if code does not have a char
	if (keyCode > 0x39 || !keyCode) {
		return;
	}

	char character = scanCodes[keyCode];

	if (capitalEnabled() && isLowerLetter(character))
		character -= 32; // makes capital

	terminal_putchar(character);
}


void enableLShift() {
	lShift = ENABLED;
}

void disableLShift() {
	lShift = DISABLED;
}

void enableRShift() {
	rShift = ENABLED;
}

void disbaleRShift() {
	rShift = DISABLED;
}

void enableCapsLock() {
	capsLock = ENABLED;
}

void disableCapsLock() {
	capsLock = DISABLED;
}

uint8_t capitalEnabled() {
	if (lShift || rShift || capsLock)
		return ENABLED;
	return DISABLED;
}

bool isLowerLetter(char c) {
	if (c >= 97 && c <= 122)
		return true;
	return false;
}

void switchCapsLock() {
	capsLock ^= 1;
}





