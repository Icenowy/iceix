EXTRA_CFLAGS ?= -g
EXTRA_ASFLAGS ?= -g 

CFLAGS = -ffreestanding -Og -Wall -Wextra -I$(PWD)/include -std=gnu99 $(EXTRA_CFLAGS)

CC = /opt/i686-elf/bin/i686-elf-gcc
AS = /opt/i686-elf/bin/i686-elf-as

all: boot/multiboot/multiboot.elf

include stdc/Makefile

include barebone/Makefile
include drivers/Makefile
include kernel/Makefile
include arch/Makefile

include boot/multiboot/Makefile

clean:
	rm -f $(objs) $(target_bin)
.PHONY: clean
