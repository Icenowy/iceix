ENTRY(_start)

SECTIONS
{

	KERNEL_MEM_BASE = 0xC0000000;
	KERNEL_REAL_BASE = 0x00100000;

	. = (KERNEL_MEM_BASE + KERNEL_REAL_BASE);

	.text BLOCK(4K) : AT(ADDR(.text) - KERNEL_MEM_BASE)
	{
		*(.multiboot_header)
		*(.text)
	}

	.rodata BLOCK(4K) : AT(ADDR(.rodata) - KERNEL_MEM_BASE)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : AT(ADDR(.data) - KERNEL_MEM_BASE)
	{
		*(.data)
	}

	.bss BLOCK(4K) : AT(ADDR(.bss) - KERNEL_MEM_BASE)
	{
		*(COMMON)
		*(.bss)
		*(.initial_stack)
	}
}
