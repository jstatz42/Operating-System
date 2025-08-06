#include "gdt.h"
#include <stdint.h>


__attribute__((aligned(0x10)))
static struct gdt_entry gdt[6];


static struct gdt_entry gdt[6];
void encodeGdtEntry(uint8_t *target, struct GDTData source) {
 
	// Encode the limit
	target[0] = source.limit & 0xFF;
	target[1] = (source.limit >> 8) & 0xFF;
	target[6] = (source.limit >> 16) & 0x0F;

	// Encode the base
	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	// Encode the access byte
	target[5] = source.access_byte;

	// Encode the flags
	target[6] |= (source.flags << 4);
}

void initGDT(void) {
	setgdt((size_t*) &gdt[0], GDT_LIMIT);
	

	// creates null descriptor
	struct GDTData nd = {0,0,0,0};
	encodeGdtEntry((uint8_t*) &gdt[0], nd);

	// creates kernel code segment
	struct GDTData kcd = {0, 0x000FFFFF, 0x9A, 0xC};
	encodeGdtEntry((uint8_t*) &gdt[1], kcd);

	// creates kernel data segment
	struct GDTData kdd = {0, 0x000FFFFF, 0x92, 0xC};
	encodeGdtEntry((uint8_t*) &gdt[2], kdd);

	// creates user code segment
	struct GDTData ucd = {0, 0x000FFFFF, 0xFA, 0xC};
	encodeGdtEntry((uint8_t*) &gdt[3], ucd);

	// creates user data segment
	struct GDTData udd = {0, 0x000FFFFF, 0xF2, 0xC};
	encodeGdtEntry((uint8_t*) &gdt[4], udd);

	// creates task state segment
	struct GDTData tss = {0xC0400000, 0x1000, 0x89, 0xC};
	encodeGdtEntry((uint8_t*) &gdt[5], tss);

	flushGdt();
}

