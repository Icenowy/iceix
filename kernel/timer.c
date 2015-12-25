#include <kernel/timer.h>

#include <arch/timer.h>

volatile uint64_t jiffies;

void timer_init ()
{
	jiffies = 0;
	arch_timer_init ();
}
