# Operating-System
This is a 32-bit operating system that utilizes the GRUB bootloader and qemu to emulate a computer environment. This operating system also uses a cross-compiler to compile the files.

## Features
- keyboard: Users are able to type, which utilizes the VGA buffer and the keyboard interrupt
- GDT: the global descriptor table has been set up
- IDT: the interrupt descriptor table has been set up with a few of the interrupts having designated interrupt handlers
- Paging: paging and some page tables have been setup
- PIT: programmable interval timer has been configured 
- PIC: programmable interrupt contorller has been configured with the keyboard and timer
- able to use constructor attributes for functions
- Interrupt handlers: The keyboard interrupt handler, the timer interrupt handler, and the division error handler have been implemented
