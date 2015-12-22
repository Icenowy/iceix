CFLAGS = -ffreestanding -O2 -Wall -Wextra
ASFLAGS = -ffreestanding -O2 -Wall -Wextra

bbobjs = barebone/kmain.o

mbobjs = boot/multiboot/multiboot.o

elfs = boot/multiboot/multiboot.elf

MBLDFLAGS = -T boot/multiboot/multiboot.lds -ffreestanding -O2 -nostdlib

CC = i686-pc-linux-gnu-gcc
AS = i686-pc-linux-gnu-as

boot/multiboot/multiboot.elf: $(bbobjs) $(mbobjs)
	$(CC) $(MBLDFLAGS) $(bbobjs) $(mbobjs) -o boot/multiboot/multiboot.elf

clean:
	rm -f $(bbobjs) $(mbobjs) $(elfs)
.PHONY: clean
