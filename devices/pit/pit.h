#ifndef PIT_H

#define PIT_H

#include <stdint.h>

#define CHANNEL_0_DATA_PORT 0x40
#define COMMAND_REG 0x43
#define LOW_HIGH_BYTE 0x30
#define SQUARE_WAVE 0x06
#define PIT_FREQUENCY 56569

void setPITCount(uint16_t);
void initPIT();

#endif
