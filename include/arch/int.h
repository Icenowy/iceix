#ifndef _ARCH_INT_H
#define _ARCH_INT_H

#define mask_interrupt() __asm__ ("cli\n\t")
#define allow_interrupt() __asm__ ("sti\n\t")

#endif
