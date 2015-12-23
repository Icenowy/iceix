.set MULTIBOOT_FLAG_ALIGN, 1<<0
.set MULTIBOOT_FLAG_MEMINFO, 1<<1
.set MULTIBOOT_FLAGS, MULTIBOOT_FLAG_ALIGN | MULTIBOOT_FLAG_MEMINFO
.set MULTIBOOT_MAGIC, 0x1BADB002
.set MULTIBOOT_CHECKSUM, -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

.section multiboot_header # The header of multiboot specification
.align 4
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long MULTIBOOT_CHECKSUM


.section initial_stack, "aw", @nobits # The initial kernel stack
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	call _set_gdt

	call kmain
	
	# This shouldn't occur, unless on a bare bone
	cli
_init_inf_loop:
	hlt
	jmp _init_inf_loop

.size _start, . - _start
