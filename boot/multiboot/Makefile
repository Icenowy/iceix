ASFLAGS = -ffreestanding -Og -Wall -Wextra $(EXTRA_ASFLAGS)

mbobjs = boot/multiboot/multiboot.o

objs += $(mbobjs)

MBLDFLAGS = -T boot/multiboot/multiboot.lds -ffreestanding -Og -nostdlib

target_bin += boot/multiboot/multiboot.elf

boot/multiboot/multiboot.elf: $(objs)
	$(CC) $(MBLDFLAGS) $(objs) -o boot/multiboot/multiboot.elf
	@echo boot/multiboot/multiboot.elf is ready

qemu-mb-gdb: boot/multiboot/multiboot.elf
	qemu-system-i386 -kernel boot/multiboot/multiboot.elf -s -S

gdb-mb: boot/multiboot/multiboot.elf
	gdb boot/multiboot/multiboot.elf -iex "target remote :1234"

qemu-mb: boot/multiboot/multiboot.elf
	qemu-system-i386 -kernel boot/multiboot/multiboot.elf
