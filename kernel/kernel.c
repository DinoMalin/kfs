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
	init_pages();
}

int kmain() {
	clear_screen();
	default_color = custom_theme(default_theme);

	for (int i = 0; i < 2048; i++) {
		int *j = vmalloc(4);
		int *k = vmalloc(4);
		if (!j)
			printk("Error in memory allocation");
		else {
			*j = 42;
			printk("Allocation succeed ! Value : %d - Address: 0x%x", *j, j);
			vfree(j);
			if (k) {
				printk("SECOND Allocation succeed ! Value : %d - Address: 0x%x", *k, k);
			} else {
				printk("SECOND Allocation FAILED !");
			}
		}
	}

	printk("This 42 is mandatory");
	init_shell();

	while (!exit)
		;

	return exit;
}
