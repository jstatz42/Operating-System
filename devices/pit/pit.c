#include "pit.h"
#include <stdint.h>
#include "../../libc/include/io.h"



void setPITCount(uint16_t count) {

	asm volatile("cli");

	// sets low byte to count
	outb(CHANNEL_0_DATA_PORT, count & 0xFF);

	// sets high byte
	outb(CHANNEL_0_DATA_PORT, (count & 0xFF00) >> 8);


	asm volatile("sti");
}


void initPIT() {

	outb(COMMAND_REG, LOW_HIGH_BYTE | SQUARE_WAVE);

	setPITCount(PIT_FREQUENCY);
}
