#ifndef INTERRUPTS_H

#define INTERRUPTS_H

#include <stdint.h>
#include <stddef.h>

#define TRAP_GATE 0x8E
#define INTERRUPT_GATE 0x8F
#define KERNEL_CODE_SELECTOR 0x08
#define NUM_IDT_DESCRIPTORS 256

typedef struct gdtEntry{
	uint16_t offset1; // lower 16 bits of the ofset
	uint16_t segSelector; // code segment selector in GDT
	uint8_t zero; // all 0
	uint8_t typeAttributes; // defines privillege level and gate type
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
extern void generalException();
extern void keyInterrupt();
void initIDT();
void assignUnhandledExceptions();

#endif
