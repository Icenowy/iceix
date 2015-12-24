.section .data.gdt

.global _gdt
_gdt:
	.quad 0x0000000000000000 # nil
	.quad 0x00cf9a000000ffff # kernel code segment (from 0x0, 4G)
	.quad 0x00cf92000000ffff # kernel data segment (from 0x0, 4G)
	.quad 0x0000000000000000
	.quad 0x0000000000000000
	.quad 0x0000000000000000
	.quad 0x0000000000000000
	.quad 0x0000000000000000 # Reserved

.set GDT_LENGTH, 8

.global _gdt_48
_gdt_48:
	.word 8 * GDT_LENGTH 
	.long _gdt

.section .text
.set CODE_SEL, 0x0008
.set DATA_SEL, 0x0010
.global _set_gdt
_set_gdt:
	lgdt _gdt_48
	ljmp $CODE_SEL, $_set_gdt_after_jmp
_set_gdt_after_jmp: 
	movl $DATA_SEL, %eax
	movw %ax, %ds
	movw %ax, %ss
	movl $0, %eax
	ret
