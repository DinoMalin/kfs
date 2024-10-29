#pragma once

#include "io.h"
#include "types.h"
#include "string.h"

struct idt_entry {
	unsigned short base_lo packed;
	unsigned short sel packed;
	unsigned char always0 packed;
	unsigned char flags packed;
	unsigned short base_hi packed;
} packed;

struct idt_ptr {
	unsigned short limit packed;
	unsigned int base packed;
} packed;

struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_nb, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void idt_install();
void idt_set_gate(unsigned long base, unsigned short sel, unsigned char flags);

#define NB_ENTRIES 256
#define ISR(num) (unsigned)isr##num, 0x08, 0b10001110

// Load IDT and ISR functions
extern void idt_load();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
