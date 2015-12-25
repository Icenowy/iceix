#include <arch/pic.h>
#include <kernel/int.h>
#include <kernel/timer.h>

void kmain ();

void arch_kmain ()
{
	pic_init ();
	timer_init ();
	allow_interrupt ();
	kmain ();
}
