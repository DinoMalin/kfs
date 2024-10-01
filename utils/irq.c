#include "irq.h"

void *irq_routines[NB_IRQ] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

void irq_install_handler(int index, void (*handler)(struct regs *r)) {
    irq_routines[index] = handler;
}

void irq_uninstall_handler(int index) {
    irq_routines[index] = 0;
}

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
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 32);
    outb(0xA1, 40);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq_install() {
    irq_remap();

    idt_set_gate(IRQ(0));
    idt_set_gate(IRQ(1));
    idt_set_gate(IRQ(2));
    idt_set_gate(IRQ(3));
    idt_set_gate(IRQ(4));
    idt_set_gate(IRQ(5));
    idt_set_gate(IRQ(6));
    idt_set_gate(IRQ(7));
    idt_set_gate(IRQ(8));
    idt_set_gate(IRQ(9));
    idt_set_gate(IRQ(10));
    idt_set_gate(IRQ(11));
    idt_set_gate(IRQ(12));
    idt_set_gate(IRQ(13));
    idt_set_gate(IRQ(14));
    idt_set_gate(IRQ(15));
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
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
