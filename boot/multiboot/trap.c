#include <arch/idt.h>
#include <arch/trap.h>
#include <stddef.h>

trap_function_t trap_table [IDT_LENGTH];

void init_trap ()
{
	for (unsigned i = 0; i < IDT_LENGTH; i++) {
		trap_table[i] = NULL;
	}
}

void c_trap(struct trapframe *tf)
{
	if (trap_table[tf->trapno]) trap_table[tf->trapno] (tf);
}
