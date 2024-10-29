#pragma once

#include "idt.h"

struct idt_entry idt[NB_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(unsigned long base, unsigned short sel, u8 flags) {
	static nb = 0;

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

	idt_set_gate(ISR(0));
	idt_set_gate(ISR(1));
	idt_set_gate(ISR(2));
	idt_set_gate(ISR(3));
	idt_set_gate(ISR(4));
	idt_set_gate(ISR(5));
	idt_set_gate(ISR(6));
	idt_set_gate(ISR(7));
	idt_set_gate(ISR(8));
	idt_set_gate(ISR(9));
	idt_set_gate(ISR(10));
	idt_set_gate(ISR(11));
	idt_set_gate(ISR(12));
	idt_set_gate(ISR(13));
	idt_set_gate(ISR(14));
	idt_set_gate(ISR(15));
	idt_set_gate(ISR(16));
	idt_set_gate(ISR(17));
	idt_set_gate(ISR(18));
	idt_set_gate(ISR(19));
	idt_set_gate(ISR(20));
	idt_set_gate(ISR(21));
	idt_set_gate(ISR(22));
	idt_set_gate(ISR(23));
	idt_set_gate(ISR(24));
	idt_set_gate(ISR(25));
	idt_set_gate(ISR(26));
	idt_set_gate(ISR(27));
	idt_set_gate(ISR(28));
	idt_set_gate(ISR(29));
	idt_set_gate(ISR(30));
	idt_set_gate(ISR(31));

	idt_load();
}

u8 *exceptions[] = {"Division By Zero",
					"Debug",
					"Non Maskable Interrupt",
					"Breakpoint",
					"Into Detected Overflow",
					"Out of Bounds",
					"Invalid Opcode",
					"No Coprocessor",
					"Double Fault",
					"Coprocessor Segment Overrun",
					"Bad TSS",
					"Segment Not Present",
					"Stack Fault",
					"General Protection Fault",
					"Page Fault",
					"Unknown Interrupt",
					"Coprocessor Fault",
					"Alignment Check",
					"Machine Check",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved",
					"Reserved"};

void fault_handler(struct regs *r) {
	if (r->int_nb < 32) {
		putstr_serial(exceptions[r->int_nb]);
		putstr_serial(" Exception. System halted.\n");
		printk("%s Exception. System halted.", exceptions[r->int_nb]);
		while (1) {
		}
	}
}
