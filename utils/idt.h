#pragma once

# define packed __attribute__((packed))

struct idt_entry
{
    unsigned short base_lo packed;
    unsigned short sel packed;
    unsigned char always0 packed;
    unsigned char flags packed;
    unsigned short base_hi packed;
} packed;

struct idt_ptr
{
    unsigned short limit packed;
    unsigned int base packed;
} packed;

extern void idt_load();

void idt_install();

# define NB_ENTRIES 256
