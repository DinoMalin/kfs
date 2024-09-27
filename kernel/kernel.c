#include "dinio.h"
#include "dinostring.h"
#include "gdt.h"

void kmain() {
    gdt_install();
    printk("LINE 1");
}
