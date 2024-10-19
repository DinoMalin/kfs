#include "dinio.h"

void print_stack(int nb) {
	unsigned int esp;
	asm volatile("movl %%esp, %0" : "=r"(esp));
	print_memory(nb, esp);
}

void print_memory(int nb, unsigned int addr) {
	for (int i = 0; i < nb; i++) {
		int delta = i * 16;
		printk("%p  %nonl", (void *)(addr + delta));

		for (int j = 0; j < 16; j++) {
			printk("%byte%nonl", *((void *)(addr + delta + j)));
			if (j % 2 == 1 && j != 15)
				printk(" %nonl");
		}

		printk("");
	}
}
