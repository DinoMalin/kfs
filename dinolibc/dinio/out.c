#include "dinio.h"
#include "dinoint.h"

#define COM1 0x3f8

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

void init_serial() {
    outb(COM1 + 4, 0x0F);
}

void write_serial(char *str) {
    for (int i = 0; str[i]; i++)
	outb(COM1, str[i]);
}
