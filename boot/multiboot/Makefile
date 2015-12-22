ASFLAGS = -ffreestanding -O2 -Wall -Wextra

mbobjs = boot/multiboot/multiboot.o

objs += $(mbobjs)

MBLDFLAGS = -T boot/multiboot/multiboot.lds -ffreestanding -O2 -nostdlib

target_bin += boot/multiboot/multiboot.elf

boot/multiboot/multiboot.elf: $(bbobjs) $(mbobjs)
	$(CC) $(MBLDFLAGS) $(bbobjs) $(mbobjs) -o boot/multiboot/multiboot.elf

