#include <vtty/vtty.h>
void kmain()
{
	vtty_initialize ();
	vtty_write ("Hello World\nfrom Iceix", 22);
	for (;;) ;
}
