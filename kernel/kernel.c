#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga/vga.h"





void kernel_main(void) {
	terminal_initialize();
	terminal_writestring("Hello, kernel World1!\n");


	// drawing a triangle
	
	for (uint8_t i = 0; i < 3; i++) {

		// prints beginning spaces
		for (uint8_t j = 0; j < 3 - i; j++) {
			terminal_putchar(' ');
		}

		terminal_setcolor(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));

		terminal_putchar('/');

		// prints middle spaces
		for (uint8_t j = 0; j < 2 * i; j++) {
			terminal_putchar(' ');
		}

		terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));

		terminal_writestring("\\\n");
	}


	terminal_setcolor(vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK));
	for (uint8_t i = 0; i < 8; i++) {
		terminal_putchar('_');
	}
}
