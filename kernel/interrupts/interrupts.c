#include "interrupts.h"
#include <stdbool.h>
#include <stdint.h>

__attribute__((aligned(0x10))) 
static gdtEntry_t idt[256]; // Create an array of IDT entries; aligned for performance


void fillGate(gdtEntry_t *gate, size_t addr, uint8_t seg, uint8_t type) {
	(*gate).offset1 = addr & 0xFFFF;
	(*gate).offset2 = addr >> 16;
	(*gate).segSelector = seg;
	(*gate).zero = 0;
	(*gate).typeAttributes = type;
}


void assignUnhandledExceptions() {

	gdtEntry_t genGate;
	
	uintptr_t geAddr = (uintptr_t) generalException;

	// creates general exception gate
	fillGate(&genGate, geAddr, KERNEL_CODE_SELECTOR, TRAP_GATE);

	for (int i = 0; i < 32; i++) {
		idt[i] = genGate;
	}
}

void initIDT() {

	setIdt((size_t*) &idt[0], (uint16_t) (sizeof(gdtEntry_t) * NUM_IDT_DESCRIPTORS - 1));

	// makes double fault gate
	gdtEntry_t dfGate;

	uintptr_t dfAddr = (uintptr_t) doubleFault;
fillGate(&dfGate, dfAddr, KERNEL_CODE_SELECTOR, TRAP_GATE);
	idt[8] = dfGate;


	// makes division error gate
	gdtEntry_t divErrGate;
	size_t offset = (size_t) divError;
	fillGate(&divErrGate, offset, KERNEL_CODE_SELECTOR, TRAP_GATE);
	idt[0] = divErrGate;


	// makes keyboard interrupt gate
	gdtEntry_t keyGate;	
	uintptr_t kiAddr = (uintptr_t) keyInterrupt;
	fillGate(&keyGate, kiAddr, KERNEL_CODE_SELECTOR, INTERRUPT_GATE);
	idt[33] = keyGate;
}





