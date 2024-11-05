#pragma once

#include "irq.h"

void *irq_routines[NB_IRQ] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int index, void (*handler)(struct regs *r)) {
	irq_routines[index] = handler;
}

void irq_uninstall_handler(int index) { irq_routines[index] = 0; }

/* IRQs from the master PIC are mapped
 * on entries 8-15, which are exceptions
 * interrupt, so we need to remap the IRQs
 * so that IRQ0 doesn't cause a double
 * fault exception when triggered.
 * We use commands directly to the port
 * in order to make IRQ0-15 to be
 * remapped to IDT entries 32 to 47.
 * */
void irq_remap(void) {
	outb(PIC1_CMD, 0x11);
	outb(PIC2_CMD, 0x11);

	outb(PIC1_DATA, 32);
	outb(PIC2_DATA, 40);

	outb(PIC1_DATA, 0x04);
	outb(PIC2_DATA, 0x02);
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);

	outb(PIC1_DATA, 0x0);
	outb(PIC2_DATA, 0x0);
}

void irq_install() {
	irq_remap();

	idt_set_gate(IRQ(0));
	idt_set_gate(IRQ(1));
}

void irq_handler(struct regs *r) {
	void (*handler)(struct regs *r);
	handler = irq_routines[r->int_nb - 32];
	if (handler)
		handler(r);

	/* If the IRQ is on the second PIC (Slave PIC),
	 * we need to send an "End of Interrupt" (0x20)
	 * to the slave PIC AND the master PIC.
	 * */
	if (r->int_nb >= 40)
		outb(PIC2_CMD, EOI);
	outb(PIC1_CMD, EOI);
}
