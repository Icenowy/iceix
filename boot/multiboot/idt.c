#include <arch/idt.h>
#include <arch/address.h>
#include <arch/trap.h>
#include <stdbool.h>

idt_gate_t idt_gates[IDT_LENGTH];

idt_desc_t idt_desc = {IDT_LENGTH * sizeof (idt_gate_t), idt_gates};

void install_idt ();

extern void (*vectors) ();

uint8_t traps[] = {0x80};

void init_idt_item (uint8_t n, void (*function) ())
{
	uint32_t uifp = (uint32_t) function;
	bool is_trap = false;
	idt_gates[n].offset_l = (uint16_t) (uifp & 0xFFFF);
	idt_gates[n].offset_h = (uint16_t) (uifp >> 16);
	idt_gates[n].reserved = 0;
	idt_gates[n].always = 0;
	idt_gates[n].present = 1;
	for (unsigned i = 0; i< (sizeof(traps) / sizeof (uint8_t)); i++) {
		if (traps[i] == n) is_trap = true;
	}
	idt_gates[n].type = is_trap ? 0xF : 0xE;
	idt_gates[n].dpl = 0;
	idt_gates[n].selector = KERNEL_CODE_SEL;
}

void init_idt ()
{
	for (int i = 0; i<IDT_LENGTH; i++) {
		init_idt_item (i, * ( (&vectors) + i));
	}
	install_idt ();
	init_trap ();
}
