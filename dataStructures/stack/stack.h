#ifndef STACK_H

#define STACK_H

#define STACK_EMPTY 100

#include <stdint.h>

typedef struct vgaStack {
	uint8_t vals[25];
	uint8_t head;
	signed char tail;
	uint8_t capacity;
	uint8_t size;
} vStack_t;



uint8_t stackPop(vStack_t*);
void stackPush(vStack_t*, uint8_t);
uint8_t getStackSize(vStack_t*);
uint8_t getStackCapacity(vStack_t*);


#endif
