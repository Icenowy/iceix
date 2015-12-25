#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <stdint.h>

#define HZ 100

extern volatile uint64_t jiffies;

void timer_init ();

#endif
