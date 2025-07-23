#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>

#define DIR_ADDR_START 0xFFC00000
#define LAST_PAGE_ADDR 0xFFFFF000

extern char _k_text_start;
extern char _k_text_end;
extern char _k_rodata_start;
extern char _k_rodata_end;
extern char _k_data_start;
extern char _k_data_end;
extern char _k_bss_start;
extern char _k_bss_end;
extern char _kernel_start;
extern char _kernel_end;


static inline uint16_t getDirectoryIndex(size_t vMem) {
	return vMem >> 22;
}

static inline uint16_t getPageTableIndex(size_t vMem) {
	return (vMem >> 12) & 0x3FF;
}


void markRO(size_t);
void kernelPageInit();
size_t *findPTEAddr(size_t);
size_t *findPDEAddr(size_t);
void setPDE(uint16_t, size_t);
void setPTE(uint16_t, uint16_t, size_t);
void assignMem(size_t);
void pageTableAlloc(uint16_t, size_t, uint16_t, uint16_t);
size_t *getPDEAddr(uint16_t);
size_t *getPTEAddr(uint16_t, uint16_t);
void initSecondPageTable();
#endif
