#include "dinoint.h"
#include "gdt.h"

struct gdt_entry gdt[NB_SEGMENTS];
struct gdt_ptr gp;

extern void gdt_flush();

void gdt_set_gate(unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    static int nb = 0;

    gdt[nb].base_low = (base & 0xFFFF);
    gdt[nb].base_middle = (base >> 16) & 0xFF;
    gdt[nb].base_high = (base >> 24) & 0xFF;

    gdt[nb].limit_low = (limit & 0xFFFF);

    gdt[nb].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[nb].access = access;

    nb++;
}

void gdt_install() {
    gp.limit = (sizeof(struct gdt_entry) * NB_SEGMENTS) - 1;
    gp.base = &gdt;

    gdt_set_gate(null_descriptor);
    gdt_set_gate(kernel_code);
    gdt_set_gate(kernel_data);
    gdt_set_gate(kernel_stack);
    gdt_set_gate(user_code);
    gdt_set_gate(user_data);
    gdt_set_gate(user_stack);

    gdt_flush();
}

