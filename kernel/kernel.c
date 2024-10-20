#include "dinio.h"
#include "dinostring.h"

#include "gdt.h"
#include "idt.h"
#include "shell.h"

int exit = 0;

void kmain() {
	gdt_install();
	idt_install();
	irq_install();
	asm volatile("sti");
	timer_install();
	keyboard_install();
	clear_screen();

	default_color = custom_theme(default_theme);
	printk("This 42 is mandatory");
	init_shell();

	alloc_basics();

	while (!exit) {
	};

	return exit;
}
