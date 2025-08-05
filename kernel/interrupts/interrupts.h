#ifndef INTERRUPTS_H

#define INTERRUPTS_H

#include <stdint.h>
#include <stddef.h>

typedef struct gdtEntry{
	uint16_t offset1; // first 16 bits of the ofset
	uint16_t segSelector; // code segment selector in GDT
	uint8_t zero; // all 0
	uint8_t typeAttributes;
	uint16_t offset2;
}__attribute__((packed)) gdtEntry_t;


struct idtr {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

extern void divError();
extern struct idtr *getIDT(struct idtr*);
extern void setIdt(size_t*, uint16_t);
extern void doubleFault();
void initIDT();


#endif
