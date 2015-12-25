#include <vtty/vtty.h>
#include <arch/pic.h>
#include <arch/int.h>
#include <kernel/timer.h>
#include <kernel/int.h>

void kmain()
{
	uint64_t current_jiffies;
	pic_init ();
	timer_init ();
	allow_interrupt ();
	vtty_initialize ();
	vtty_write ("Merry Christmas!\n", 17);
	current_jiffies = 0;
	for (;;) {
		if ((! (jiffies % HZ)) && jiffies > current_jiffies) {
			vtty_write (".", 1);
			current_jiffies = jiffies;
		}
	}
}
