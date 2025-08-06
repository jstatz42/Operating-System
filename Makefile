CC=~/opt/cross/bin/i686-elf-gcc
CCA=~/opt/cross/bin/i686-elf-as
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -g
VGA=kernel/vga/vga.c kernel/vga/vga.h
OBJS=objects/boot.o objects/kernel.o objects/vga.o objects/string.o objects/gdt.o objects/asmgdt.o objects/paging.o objects/interrupts.o objects/interC.o objects/pic.o objects/io.o
CRTBEGIN=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI=kernel/cri/crti.s
CRTN=kernel/cri/crtn.s
GDT=kernel/GDT/gdt.c
AGDT=kernel/GDT/asmgdt.s
OBJ_LINK_ORDER=objects/crti.o $(CRTBEGIN) $(OBJS) $(CRTEND) objects/crtn.o
STRINGS=libc/include/string.c libc/include/string.h
PAGING=kernel/paging/paging.c
INTERRUPTS=kernel/interrupts/interrupts.s
INTERC=kernel/interrupts/interrupts.c
PIC=devices/pic/pic.c
IO=libc/include/io.c

.PHONY: all clean qemu debug

all: pic.o io.o interC.o interrupts.o paging.o asmgdt.o gdt.o string.o crti.o crtn.o vga.o kernel.o boot.o myos.iso

pic.o: $(PIC)
	$(CC) -c $(PIC) -o objects/pic.o $(CFLAGS)

io.o: $(IO)
	$(CC) -c $(IO) -o objects/io.o $(CFLAGS)

interC.o: $(INTERC)
	$(CC) -c $(INTERC) -o objects/interC.o $(CFLAGS)

interrupts.o: $(INTERRUPTS)
	$(CCA) -o objects/interrupts.o $(INTERRUPTS) -g

paging.o: $(PAGING)
	$(CC) -c $(PAGING) -o objects/paging.o $(CFLAGS)

asmgdt.o: $(AGDT)
	$(CCA) -o objects/asmgdt.o $(AGDT) -g

gdt.o: $(GDT)
	$(CC) -c $(GDT) -o objects/gdt.o $(CFLAGS)

string.o: $(STRINGS)
	$(CC) -c libc/include/string.c -o objects/string.o $(CFLAGS)

crti.o: $(CRTI)
	$(CCA) $(CRTI) -o objects/crti.o -g

crtn.o: $(CRTN)
	$(CCA) $(CRTN) -o objects/crtn.o -g

vga.o: $(VGA)
	$(CC) -c kernel/vga/vga.c -o objects/vga.o $(CFLAGS)

kernel.o: kernel/kernel.c
	$(CC) -c kernel/kernel.c -o objects/kernel.o $(CFLAGS)

boot.o: boot.s
	$(CCA) boot.s -o objects/boot.o -g


myos.iso: $(OBJ_LINK_ORDER)
	$(CC) -T linker.ld -o myos.bin  $(OBJ_LINK_ORDER) -ffreestanding -O2 -nostdlib -lgcc -g
	@if ./multiboot.sh; then \
		cp myos.bin isodir/boot/myos.bin; \
		cp grub.cfg isodir/boot/grub/grub.cfg; \
		grub-mkrescue -o myos.iso isodir; \
	else \
		echo "Could not build OS"; \
		exit 1; \
	fi


qemu:
	qemu-system-i386 -kernel myos.bin

clean:
	rm -f objects/*.o

debug:
	qemu-system-i386 -cdrom myos.iso -s -S
