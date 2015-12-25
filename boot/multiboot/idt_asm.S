#include <arch/address.h>

.section .text
.globl install_idt
install_idt:
	lidt idt_desc
	ret

.globl general_trap
general_trap:
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushal

	movw $KERNEL_DATA_SEL, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

	pushl %esp
	call c_trap
	addl $4, %esp

.globl general_trap_ret
general_trap_ret:
	popal
	popl %gs
	popl %fs
	popl %es
	popl %ds
	addl $0x8, %esp # remove things poped by vector
	iret
