#ifndef _ARCH_PIC_H
#define _ARCH_PIC_H

void pic_init ();

#define pic1_ready() outb(0x20, 0x20)

#endif
