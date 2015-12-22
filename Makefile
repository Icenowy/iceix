CFLAGS = -ffreestanding -O2 -Wall -Wextra

CC = i686-pc-linux-gnu-gcc

all: boot/multiboot/multiboot.elf

include barebone/Makefile
include boot/multiboot/Makefile
include drivers/Makefile

clean:
	rm -f $(objs) $(target_bin)
.PHONY: clean
