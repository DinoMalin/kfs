#include "kernel.h"

int exit = 0;
multiboot_info *multiboot;

void ksetup(int magic, multiboot_info *_multiboot) {
	if (magic != MULTIBOOT_MAGIC)
		kernel_panic("wrong multiboot magic");
	if (!_multiboot->flags & MULTIBOOT_INFO_MEM_MAP)
		kernel_panic("mmap not set");

	multiboot = _multiboot;
	keep_mmap_info(multiboot);
	init_pmem();

	gdt_install();
	idt_install();
	irq_install();
	asm volatile("sti");

	timer_install();
	keyboard_install();
}

int kmain() {
	clear_screen();
	default_color = custom_theme(default_theme);
	printk("This 42 is mandatory");
	init_shell();

	while (!exit)
		;

	return exit;
}
