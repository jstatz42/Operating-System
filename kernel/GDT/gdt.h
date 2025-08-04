#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>

#define GDT_START 0xC03FFFAC
#define GDT_LIMIT 0xFFFF
#define TSS_MEM 0xC040FFAC
#define TSS_BLOCKS 4
#define TSS_BLOCK_SIZE 104


struct SDVals {

	uint32_t base;
	unsigned int limit: 20;
	uint8_t aByte;
	unsigned int flags: 4;

}__attribute__((packed));

struct gdt_entry {
	uint16_t limit1;
	uint16_t base1;
	uint8_t base2;
	uint8_t access_byte;
	unsigned int limit2: 4;
	unsigned int flags: 4;
	uint8_t base3;
}__attribute__((packed));

struct GDTRptr {
	uint16_t limit;
	uint32_t* base;
}__attribute__((packed));



void makeSegDescriptor(uint8_t*, struct SDVals);
void getgdt(struct GDTRptr*);
void initGDTSegments();
void completeFlush();
extern void setgdt(size_t*, uint16_t);
extern void flushGdt();



#endif
