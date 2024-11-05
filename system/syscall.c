#include "syscall.h"

void syscall_1() { printk("i'm a tyrannosaur"); }
void syscall_2() { printk("i'm a triceratops"); }
void syscall_3() { printk("i'm an ankylosaur"); }

void (*syscall_table[])() = {syscall_1, syscall_2, syscall_3};

void syscall_fault() { printk("There is no such syscall"); }

void syscall_handler(struct regs *r) {
	u32 code = CODE(r);

	if (code < 3) {
		syscall_table[code]();
		return;
	}

	syscall_fault();
}
