#include <stdint.h>
#include "paging.h"


void kernelPageInit() {
	size_t cur = (size_t) & _k_text_start;
	while (cur <= (size_t) & _k_rodata_end) {
		markRO(cur);
		cur += 4096;
	}
}


size_t *findPTEAddr(size_t vMem) {
	uint16_t dirIdx = getDirectoryIndex(vMem);
	uint16_t ptIdx = getPageTableIndex(vMem);

	// gets address of the page table
	size_t *pte = (size_t*) ((size_t) DIR_ADDR_START + dirIdx * 0x1000);

	// gets address of the page table entry
	pte += ptIdx;

	return pte;

}


size_t *findPDEAddr(size_t vMem) {
	uint16_t dirIdx = getDirectoryIndex(vMem);
	size_t *pde = (size_t*) LAST_PAGE_ADDR + dirIdx;
	return pde;
}




void markRO(size_t vMem) {
	size_t *pt = findPTEAddr(vMem);
	(*pt) &= ~0x2;
}


size_t *getPDEAddr(uint16_t idx) {
	return (size_t*) LAST_PAGE_ADDR + idx;
}

size_t *getPTEAddr(uint16_t dIdx, uint16_t pIdx) {
	return (size_t*) ((size_t) DIR_ADDR_START + 0x1000 * dIdx + 4 * pIdx);
}


void setPDE(uint16_t idx, size_t val) {
	size_t *pdeAddr = getPDEAddr(idx);
	*pdeAddr = val;
}

void setPTE(uint16_t dIdx, uint16_t pIdx, size_t val) {
	size_t *pteAddr = getPTEAddr(dIdx, pIdx);
	*pteAddr = val;
}



// idx represents the page index of the new page table
// physAddr represents the physical address of the new page table
void pageTableAlloc(uint16_t idx, size_t physAddr, uint16_t dFlags, uint16_t pFlags) {
	
	size_t *pdeAddr = getPDEAddr(idx);

	// makes sure that only the first 12 bits
	// of the flags are used
	dFlags &= 0x0FFF;
	pFlags &= 0x0FFF;

	// puts the values into the page directory
	*pdeAddr = physAddr | dFlags;

	// marks all the page table entries as readable and writable
	// continuously from the memory start
	size_t *pteAddr = getPTEAddr(idx, 0);
	size_t end = *pteAddr + 0x1000;

	// the addresses that the page table points to will be immediately
	// after the page table
	physAddr += 0x1000;
	for (;*pteAddr < end; pteAddr += 1, physAddr += 0x1000) {
		*pteAddr = physAddr | pFlags;
	}
}

void initSecondPageTable() {
	pageTableAlloc(769, 0x00411000, 0x0003, 0x0003);
}

