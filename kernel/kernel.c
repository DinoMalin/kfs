#include "dinio.h"
#include "dinostring.h"

#include "gdt.h"
#include "idt.h"

void kmain() {
    gdt_install();
    idt_install();
    irq_install();
    asm volatile ("sti");
    timer_install();
    printk("one");
    wait(200);
    printk("two");
}
