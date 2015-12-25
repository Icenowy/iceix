#ifndef _ARCH_INT_H
#define _ARCH_INT_H

#define arch_cli() __asm__ ("cli\n\t")
#define arch_sti() __asm__ ("sti\n\t")

#endif
