#include "dinio.h"

void print_stack(int nb) {
    unsigned int esp;
    asm volatile ("movl %%esp, %0" : "=r"(esp));

    for (int i = 0; i < nb; i++) {
	int delta = i * 16;
	printk("%p  %nonl", (void *)(esp + delta));
	for (int j = 0; j < 16; j++) {
	    printk("%byte%nonl", *((void *)(esp + delta + j)));
	    if (j % 2 == 1 && j != 15)
		printk(" %nonl");
	}
	printk("");
    }
}
