#include "stack.h"
#include <stdbool.h>
#include <stdint.h>

extern bool startNewlineStack;

uint8_t stackPop(vStack_t* stack) {


	if (!stack -> size)
		return STACK_EMPTY;

	uint8_t retVal = stack -> vals[stack -> tail--];
	stack -> size--;
	
	if (stack -> tail == -1 && stack -> size) {
		stack -> tail += stack -> capacity;
	}

	return retVal;
}

void stackPush(vStack_t* stack, uint8_t val) {

	if (!startNewlineStack)
		return;

	if (stack -> size == stack -> capacity) {
		stack -> head = (stack -> head + 1) % stack -> capacity;
		stack -> size--; // counters size added to the stack when val is added
	}

	stack -> tail = (stack -> tail + 1) % stack -> capacity;
	stack -> size++;
	stack -> vals[stack -> tail] = val;
}





uint8_t getStackSize(vStack_t* stackPtr) {
	return (*stackPtr).size;
}



uint8_t getStackCapacity(vStack_t* stackPtr) {
	return (*stackPtr).capacity;
}












