#include "kernel.h"

int exit = 0;

void ksetup(int magic, struct multiboot_info *multiboot) {
	if (magic != MULTIBOOT_MAGIC)
		kernel_panic("wrong multiboot magic")
	if (!multiboot->flags & MULTIBOOT_INFO_MEM_MAP)
		kernel_panic("mmap not set");
	keep_mmap_info(multiboot);
	init_pmem();
	pmem_alloc_zone(multiboot->mmap_addr, multiboot->mmap_length);

	printk("length = %u", multiboot->mmap_length);
	printk("addr = %x", multiboot->mmap_addr);

	gdt_install();
	idt_install();
	irq_install();
	asm volatile("sti");

	timer_install();
	keyboard_install();
	init_paging();
}

int kmain() {
	clear_screen();
	default_color = custom_theme(default_theme);
	printk("This 42 is mandatory");
	init_shell();

	while (!exit) {
	}

	return exit;
}
