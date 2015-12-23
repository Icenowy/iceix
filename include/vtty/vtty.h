#ifndef _VTTY_VTTY_H
#define _VTTY_VTTY_H

#include <stddef.h>
void vtty_initialize (void);
void vtty_write (const void *buf, size_t nbyte);

#endif
