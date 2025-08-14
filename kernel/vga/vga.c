#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../../dataStructures/stack/stack.h"
#include "../../libc/include/string.h"
#include "vga.h"


size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

vStack_t newlineStack;
bool startNewlineStack = false;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	
	newlineStack.size = 0;
	newlineStack.capacity = 25;
	newlineStack.head = 0;
	newlineStack.tail = -1;


}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}




void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}



void terminal_scroll() {

	// transfers text up
	for (size_t y = 1; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index - VGA_WIDTH] = terminal_buffer[index];
		}
	}

	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
	
}


void terminal_putchar(char c) 
{


	if (c == 8) {
		terminal_backspace();
		return;
	}


	if (c == '\n') {
		stackPush(&newlineStack, terminal_column);
		terminal_row++;
		terminal_column = 0;
	}


	if (terminal_column == VGA_WIDTH) {
		stackPush(&newlineStack, terminal_column);
		terminal_column = 0;
		terminal_row++;
	}

	if (terminal_row > VGA_HEIGHT - 1) {
		terminal_scroll();
		terminal_column = 0;
		terminal_row = VGA_HEIGHT - 1;
	}

	if (c == '\n')
		return;

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	terminal_column++;
}

void gotoPrevLine() {

	terminal_column = stackPop(&newlineStack);


	if (terminal_column == STACK_EMPTY) {
		terminal_column = 0;
	} else {
		terminal_row--;
	}

	return;

}

void terminal_backspace() {

	if (!terminal_column) {
		gotoPrevLine();
		return;
	}

	// delete previous character
	size_t idx = terminal_row * VGA_WIDTH + terminal_column - 1;
	terminal_buffer[idx] = vga_entry(' ', terminal_color);	

	terminal_column--;

}



void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

