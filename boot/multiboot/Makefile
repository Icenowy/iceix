ASFLAGS = -ffreestanding -Og -Wall -Wextra $(EXTRA_ASFLAGS) -I$(PWD)/include

mbobjs = boot/multiboot/multiboot.o boot/multiboot/kgdt.o boot/multiboot/idt_asm.o boot/multiboot/idt.o boot/multiboot/vectors.o boot/multiboot/trap.o

objs += $(mbobjs)

MBLDFLAGS = -T boot/multiboot/multiboot.lds -ffreestanding -Og -nostdlib

target_bin += boot/multiboot/multiboot.elf

GCCLIB = -lgcc

boot/multiboot/multiboot.elf: $(objs) boot/multiboot/multiboot.lds
	$(CC) $(MBLDFLAGS) $(objs) -o boot/multiboot/multiboot.elf $(GCCLIB)
	@echo boot/multiboot/multiboot.elf is ready

boot/multiboot/vectors.S: boot/multiboot/vectors.pl
	perl boot/multiboot/vectors.pl > boot/multiboot/vectors.S

qemu-mb-gdb: boot/multiboot/multiboot.elf
	qemu-system-i386 -kernel boot/multiboot/multiboot.elf -s -S

gdb-mb: boot/multiboot/multiboot.elf
	gdb boot/multiboot/multiboot.elf -iex "target remote :1234"

qemu-mb: boot/multiboot/multiboot.elf
	qemu-system-i386 -kernel boot/multiboot/multiboot.elf
