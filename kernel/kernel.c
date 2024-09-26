#include "dinio.h"
#include "dinostring.h"

void kmain() {
    printk("LINE 1");
    init_serial();
    write_serial("DINOMALINDINOMALINDINOMALIN");
}
