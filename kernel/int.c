#include <kernel/int.h>
#include <arch/int.h>
#include <stdint.h>

volatile uint32_t mask_count = 0;

inline void mask_interrupt ()
{
	if (! mask_count) arch_cli ();
	mask_count++;
}

inline void allow_interrupt ()
{
	mask_count--;
	if (! mask_count) arch_sti ();
}
