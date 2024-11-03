#include "kernel.h"

int end = 0;
multiboot_info *multiboot;

int ksetup(int magic, multiboot_info *_multiboot) {
	if (magic != MULTIBOOT_MAGIC)
		kernel_panic("wrong multiboot magic", EXIT);
	if (!_multiboot->flags & MULTIBOOT_INFO_MEM_MAP)
		kernel_panic("mmap not set", EXIT);

	multiboot = _multiboot;
	keep_mmap_info(multiboot);
	init_pmem();

	gdt_install();
	idt_install();
	irq_install();
	asm volatile("sti");

	timer_install();
	keyboard_install();
	if (!init_pages())
		kernel_panic("failed to init basic pages", EXIT);
	return end;
}

int kmain() {
	clear_screen();
	default_color = custom_theme(default_theme);

	printk("This 42 is mandatory");
	init_shell();

	while (!end)
		;

	return end;
}
