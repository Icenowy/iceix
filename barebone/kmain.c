#include <vtty/vtty.h>
void kmain()
{
	vtty_initialize ();
	vtty_write ("Merry Christmas!\n", 18);
	for (;;) ;
}
