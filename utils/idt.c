#include "dinoint.h"
#include "idt.h"

struct idt_entry idt[NB_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(unsigned long base, unsigned short sel, unsigned char flags) {
    static nb = 0;

    idt[nb].base_lo = base & 0xFFFF;
    idt[nb].base_hi = (base >> 16) & 0xFFFF;

    idt[nb].sel = sel;
    idt[nb].flags = flags;
    idt[nb].always0 = 0;

    nb++;
}

void idt_install() {
    idtp.limit = (sizeof (struct idt_entry) * NB_ENTRIES) - 1;
    idtp.base = &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * NB_ENTRIES);

    idt_load();
}
