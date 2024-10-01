#include "dinio.h"
#include "dinostring.h"

#include "gdt.h"
#include "idt.h"

void kmain() {
    gdt_install();
    idt_install();
    irq_install();
    asm volatile ("sti");
    print_stack(25);
    int a = 9 / 0;
}
