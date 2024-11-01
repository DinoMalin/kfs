ENTRY(_start)

SECTIONS
{

	. = 1M;
	.multiboot.data ALIGN(4K):
	{
		*(.multiboot.data)
	}
	.multiboot.bss ALIGN(4K) :
	{
		page_directory = .;
		. += 0x1000;
		first_table = .;
		. += 0x1000;
	}
	.multiboot.text ALIGN(4K):
	{
		*(.multiboot.text)
	}

	. += 0xC0000000;
	kernel_start = .;
	.text ALIGN(4K) : AT(ADDR (.text) - 0xC0000000)
	{
		*(.text)
	}

	.rodata ALIGN(4K) : AT(ADDR (.rodata) - 0xC0000000)
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR (.data) - 0xC0000000)
	{
		*(.data)
	}


	.bss ALIGN(4K) : AT(ADDR (.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
	}

	kernel_end = .;
}
