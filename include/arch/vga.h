#ifndef _ARCH_VGA_H
#define _ARCH_VGA_H

#include <arch/address.h>

#define VGA_CRT_IC 0x3d4
#define VGA_CRT_DC 0x3d5

#define VGA_MEM_TEXT_ADDRESS_VIRT (0xB8000 + KERNEL_MEM_BASE)

#endif
