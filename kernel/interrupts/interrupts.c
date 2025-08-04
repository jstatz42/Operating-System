#include "interrupts.h"

extern void doubleFault();

struct interruptsGateDescriptor dfGate;
uintptr_t dfAddr = (uintptr_t) doubleFault;

__attribute__((aligned(0x10))) 
static struct interruptsGateDescriptor idt[256]; // Create an array of IDT entries; aligned for performance

void initIDT() {

	setIdt((size_t*) &idt[0], (uint16_t) sizeof(struct interruptsGateDescriptor) * 255);



	dfGate.offset1 = dfAddr & 0xFFFF;
	dfGate.offset2 = dfAddr >> 16;
	dfGate.segSelector = 0x08;
	dfGate.zero = 0;
	dfGate.typeAttributes = 0x8E;

	idt[8] = dfGate;
	struct interruptsGateDescriptor divErrGate;

	uintptr_t divErrorAddr = (uintptr_t) divError;
	size_t offset = (size_t) divErrorAddr;

	// get the first 16 bytes of the interrupt handler
	divErrGate.offset1 = (offset) & 0xFFFF;

	// get the next 16 bits of the interrupts handler
	divErrGate.offset2 = (offset) >> 16;

	// can be any except for the 0th index
	divErrGate.segSelector = 0x08;

	divErrGate.zero = 0;

	divErrGate.typeAttributes = 0x8E;

	// struct interruptsGateDescriptor *idt = (struct interruptsGateDescriptor*) IDT_START;

	// struct idtr IDTRptr;

	// getIDT(&IDTRptr);

	// *idt = divErrGate;
	idt[0] = divErrGate;
	
}
