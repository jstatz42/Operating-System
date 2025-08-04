#include "gdt.h"
#include <stdint.h>


__attribute__((aligned(0x10)))
static struct gdt_entry gdt[6];



void makeSegDescriptor(uint8_t *mem, struct SDVals sd) {

	// puts in limit values
	mem[1] = sd.limit & 0xff;
	mem[0] = (sd.limit >> 8) & 0xff;
	mem[6] = (sd.limit >> 16) & 0xf;


	// puts in base values
	mem[3] = sd.base & 0xff;
	mem[2] = (sd.base >> 8) & 0xff;
	mem[4] = (sd.base >> 16) & 0xff;
	mem[7] = (sd.base >> 24) & 0xff;


	// puts in the access byte
	mem[5] = sd.aByte;

	// puts in flags
	mem[6] |= (sd.flags << 4);
}


void initGDTSegments() {
	
	setgdt((size_t*) &gdt[0], 47);

	// create null descriptor
	struct SDVals nullDescriptor = {0, 0, 0, 0};
	makeSegDescriptor((uint8_t*) &gdt[0], nullDescriptor);


	// create kernel code segment
	struct SDVals KCSegment = {0, 0xFFFFF, 0x9B, 0xC};
	makeSegDescriptor((uint8_t*) &gdt[1], KCSegment);

	// create kernel data segment
	struct SDVals KDSegment = {0, 0xFFFFF, 0x93, 0xC};
	makeSegDescriptor((uint8_t*) &gdt[2], KDSegment);

	// create user code segment
	struct SDVals UCSegment = {0, 0xFFFFF, 0xFB, 0xC};
	makeSegDescriptor((uint8_t*) &gdt[3], UCSegment);


	// create user data segment
	struct SDVals UDSegment = {0, 0xFFFFF, 0xF3, 0xC};
	makeSegDescriptor((uint8_t*) &gdt[4], UDSegment);

	// create task state segment
	struct SDVals TSSSegment = {TSS_MEM, TSS_BLOCKS * TSS_BLOCK_SIZE, 0x89, 0x0};
	makeSegDescriptor((uint8_t*) &gdt[5], TSSSegment);

	flushGdt();

}



