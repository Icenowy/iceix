#include <arch/timer.h>
#include <arch/idt.h>
#include <arch/pic.h>
#include <arch/trap.h>
#include <arch/portio.h>
#include <kernel/int.h>

#define I8254_TICK 1193180

#define I8254_INT 0x20

static void do_timer ();

void arch_timer_init ()
{
	unsigned int divisor = I8254_TICK/HZ;
	outb (0x36, 0x43);
	outb (divisor & 0xff, 0x40);
	outb (divisor >> 8, 0x40);
	outb (inb (0x21) & 0xfe, 0x21);
	trap_table[I8254_INT] = do_timer;
}

static void do_timer (struct trapframe *tf)
{
	(void) tf;
	mask_interrupt ();
	jiffies++;
	pic1_ready ();
	allow_interrupt ();
}
