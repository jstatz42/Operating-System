#include "../../libc/include/io.h"
#include "pic.h"
#include <stdint.h>



void remapPIC(uint16_t offset1, uint16_t offset2) {
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 1 << CASCADE_IRQ);        // ICW3: tell Master PIC that there is a slave PIC at IRQ2
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	// Unmask both PICs.
	outb(PIC1_DATA, ~2);
	// outb(PIC2_DATA, 0);
}




void sendEOI_PIC(uint8_t irq) {

	if(irq >= 8) {
		outb(PIC2_COMMAND,PIC_EOI);
	}	

	outb(PIC1_COMMAND,PIC_EOI);
}


void initPIC() {
	remapPIC(0x20, 0x28);
}













