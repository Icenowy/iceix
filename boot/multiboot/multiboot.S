.set MULTIBOOT_FLAG_ALIGN, 1<<0
.set MULTIBOOT_FLAG_MEMINFO, 1<<1
.set MULTIBOOT_FLAGS, MULTIBOOT_FLAG_ALIGN | MULTIBOOT_FLAG_MEMINFO
.set MULTIBOOT_MAGIC, 0x1BADB002
.set MULTIBOOT_CHECKSUM, -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

.section .multiboot_header # The header of multiboot specification
.align 4
_multiboot_header:
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long MULTIBOOT_CHECKSUM

.set KERNEL_MEM_BASE, 0xC0000000
.set KERNEL_REAL_BASE, 0x00100000

.set KERNEL_PAGE_NUMBER, (KERNEL_MEM_BASE >> 22)

.section .data.initial_pgd
.align 4096
initial_pgd_top:
# The first page of kernel is a 4MB-sized page
# Repeat it at here, in order to access the memory when the CPU didn't jump to higher half
.long 0x00000083
.space (KERNEL_PAGE_NUMBER - 1) * 4, 0
.long 0x00000083
.space (1024 - KERNEL_PAGE_NUMBER - 1) * 4, 0

.section .initial_stack, "aw", @nobits # The initial kernel stack
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function

.equ _start, (real_start - KERNEL_MEM_BASE)

real_start:
	movl $(initial_pgd_top - KERNEL_MEM_BASE), %ecx
	mov %ecx, %cr3 # PGD Address

	movl %cr4, %ecx
	orl $0x00000010, %ecx
	movl %ecx, %cr4 # Enable 4M Page

	movl %cr0, %ecx
	orl $0x80000000, %ecx
	movl %ecx, %cr0 # Enable Paging

	movl $_higher_mem, %ecx
	jmpl *%ecx

_higher_mem:

	movl $0x0, initial_pgd_top
	invlpg 0x0

	movl $stack_top, %esp

	movl $1, mask_count

	call _set_gdt

	call init_idt

	call kmain
	
	# This shouldn't occur, unless on a bare bone
	cli
_init_inf_loop:
	hlt
	jmp _init_inf_loop

.size _start, . - _start
