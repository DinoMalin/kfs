#include "dinio.h"
#include "dinostring.h"

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "shell.h"

#include "virtual_mem.h"

int exit = 0;

int kmain() {
	gdt_install();
	idt_install();
	irq_install();
	asm volatile("sti");
	timer_install();
	keyboard_install();

	init_paging();

	clear_screen();
	default_color = custom_theme(default_theme);
	printk("This 42 is mandatory");
	init_shell();

	while (!exit) {
	}

	return exit;
}
