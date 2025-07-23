#ifndef GDT_H
#define GDT_H

#include <stdint.h>

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

};


struct GDTRptr {
	uint16_t limit;
	uint32_t* base;
}__attribute__((packed));



void makeSegDescriptor(uint8_t*, struct SDVals);
void getgdt(struct GDTRptr*);
void setgdt(uint32_t, uint16_t);
void initGDTSegments();
void flushGdt();
void completeFlush();




#endif
