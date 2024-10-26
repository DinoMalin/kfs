ENTRY(_start)

SECTIONS
{

	.multiboot :
	{
		*(.multiboot)
	}

	. = 1M;
	kernel_start = .;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}


	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	.gdt 0x800 : { *(.gdt) }

	kernel_end = .;
}
