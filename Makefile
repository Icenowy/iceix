EXTRA_CFLAGS ?= -g
EXTRA_ASFLAGS ?= -g 

CFLAGS = -ffreestanding -Og -Wall -Wextra -I$(PWD)/include $(EXTRA_CFLAGS)

CC = /opt/i686-elf/bin/i686-elf-gcc
AS = /opt/i686-elf/bin/i686-elf-as

all: boot/multiboot/multiboot.elf

include barebone/Makefile
include drivers/Makefile
include kernel/Makefile
include boot/multiboot/Makefile

clean:
	rm -f $(objs) $(target_bin)
.PHONY: clean
