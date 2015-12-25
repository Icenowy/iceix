#ifndef _ARCH_TRAP_H
#define _ARCH_TRAP_H

#include <arch/idt.h>

typedef void (*trap_function_t) (struct trapframe *tf);

extern trap_function_t trap_table [IDT_LENGTH];

void init_trap ();

void c_trap (struct trapframe *tf);

#endif
