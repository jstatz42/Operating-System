#include "gdt.h"


void makeSegDescriptor(uint8_t *mem, struct SDVals sd) {

	// puts in limit values
	mem[0] = sd.limit & 0xff;
	mem[1] = (sd.limit >> 8) & 0xff;
	mem[6] = (sd.limit >> 16) & 0xf;


	// puts in base values
	mem[2] = sd.base & 0xff;
	mem[3] = (sd.base >> 8) & 0xff;
	mem[4] = (sd.base >> 16) & 0xff;
	mem[7] = (sd.base >> 24) & 0xff;


	// puts in the access byte
	mem[5] = sd.aByte;

	// puts in flags
	mem[6] |= (sd.flags << 4);
}


void initGDTSegments() {
	
	struct GDTRptr gdtr;
	getgdt(&gdtr);

	uint32_t *memStart = gdtr.base;

	// create null descriptor
	struct SDVals nullDescriptor = {0, 0, 0, 0};
	makeSegDescriptor((uint8_t*) memStart, nullDescriptor);


	// create kernel code segment
	memStart += 2;
	struct SDVals KCSegment = {0, 0xFFFFF, 0x9A, 0xC};
	makeSegDescriptor((uint8_t*) memStart, KCSegment);

	// create kernel data segment
	memStart += 2;
	struct SDVals KDSegment = {0, 0xFFFFF, 0x92, 0xC};
	makeSegDescriptor((uint8_t*) memStart, KDSegment);

	// create user code segment
	memStart += 2;
	struct SDVals UCSegment = {0, 0xFFFFF, 0xFA, 0xC};
	makeSegDescriptor((uint8_t*) memStart, UCSegment);


	// create user data segment
	memStart += 2;
	struct SDVals UDSegment = {0, 0xFFFFF, 0xF2, 0xC};
	makeSegDescriptor((uint8_t*) memStart, UDSegment);

	// create task state segment
	memStart += 2;
	struct SDVals TSSSegment = {TSS_MEM, TSS_BLOCKS * TSS_BLOCK_SIZE, 0x89, 0x0};
	makeSegDescriptor((uint8_t*) memStart, TSSSegment);

	flushGdt();

}



