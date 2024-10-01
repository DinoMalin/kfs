#include "dinio.h"

#define COM1 0x3f8

inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

void init_serial() {
    outb(COM1 + 4, 0x0F);
}

void write_serial(char *str) {
    for (int i = 0; str[i]; i++)
	outb(COM1, str[i]);
}
