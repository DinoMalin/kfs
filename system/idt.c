#pragma once

#include "idt.h"

struct idt_entry idt[NB_ENTRIES];
struct idt_ptr idtp;
void (*isr_table[])() = {ISR_FUNCS};

void idt_set_gate(int nb, unsigned long base, unsigned short sel, u8 flags) {
	idt[nb].base_lo = base & 0xFFFF;
	idt[nb].base_hi = (base >> 16) & 0xFFFF;

	idt[nb].sel = sel;
	idt[nb].flags = flags;
	idt[nb].always0 = 0;

	nb++;
}

void idt_install() {
	idtp.limit = (sizeof(struct idt_entry) * NB_ENTRIES) - 1;
	idtp.base = (u32)&idt;

	memset(&idt, 0, sizeof(struct idt_entry) * NB_ENTRIES);

	for (int i = 0; i < 31; i++) {
		idt_set_gate(ISR(i));
	}
	idt_set_gate(SOFT_INT);

	idt_load();
}

u8 *exceptions[] = {EXCEPTIONS_MSG};

u32 get_cr() {
	unsigned int cr;
	asm volatile("movl %%cr2, %0" : "=r"(cr));
	return cr;
}

void fault_handler(struct regs *r) {
	if (r->int_nb == 0) {
		fkernel_panic(NO_EXIT, "%s exception\n", exceptions[r->int_nb]);
	} else if (r->int_nb == 14) {
		fkernel_panic(EXIT, "%s exception\nInvalid access to 0x%x",
					  exceptions[r->int_nb], get_cr());
	} else if (r->int_nb < 32)
		fkernel_panic(EXIT, "%s exception", exceptions[r->int_nb]);
	if (r->int_nb < 32) {
		GO_HALT();
	}
}
