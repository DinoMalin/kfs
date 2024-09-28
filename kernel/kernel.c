#include "dinio.h"
#include "dinostring.h"
#include "gdt.h"

void kmain() {
    gdt_install();
    print_stack(25);
}
