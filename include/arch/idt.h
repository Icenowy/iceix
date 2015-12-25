#ifndef _ARCH_IDT_H
#define _ARCH_IDT_H

#include <stdint.h>

struct idt_gate {
	uint16_t offset_l;
	uint16_t selector;
	uint8_t reserved;
	uint8_t type:4;
	uint8_t always:1;
	uint8_t dpl:2;
	uint8_t present:1;
	uint16_t offset_h;
} __attribute__((__packed__));
typedef struct idt_gate idt_gate_t;

struct idt_desc {
	uint16_t length;
	idt_gate_t *pointer;
} __attribute__((__packed__));
typedef struct idt_desc idt_desc_t;

// Layout of the trap frame built on the stack by the
// hardware and by trapasm.S, and passed to trap().
struct trapframe {
  // registers as pushed by pusha
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t oesp;      // useless & ignored
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;

  // rest of trap frame
  uint16_t gs;
  uint16_t padding1;
  uint16_t fs;
  uint16_t padding2;
  uint16_t es;
  uint16_t padding3;
  uint16_t ds;
  uint16_t padding4;
  uint32_t trapno;

  // below here defined by x86 hardware
  uint32_t err;
  uint32_t eip;
  uint16_t cs;
  uint16_t padding5;
  uint32_t eflags;

  // below here only when crossing rings, such as from user to kernel
  uint32_t esp;
  uint16_t ss;
  uint16_t padding6;
} __attribute__((__packed__));

typedef struct trapframe trapframe_t;

extern idt_desc_t idt_desc;

#define IDT_LENGTH 256

#endif
