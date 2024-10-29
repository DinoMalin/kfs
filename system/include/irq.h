#pragma once

#include "idt.h"
#include "io.h"

#define NB_IRQ 16

// Load IRQs
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_install();
void irq_install_handler(int index, void (*handler)(struct regs *r));
void irq_uninstall_handler(int index);
void irq_handler(struct regs *r);

#define IRQ(num) (unsigned)irq##num, 0x08, 0b10001110
#define EOI 0x20

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_CMD PIC1
#define PIC2_CMD PIC2
#define PIC1_DATA (PIC1 + 1)
#define PIC2_DATA (PIC2 + 1)
