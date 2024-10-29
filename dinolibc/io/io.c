#include "io.h"

inline void outb(u16 port, u8 val) {
	asm volatile("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline u8 inb(u16 port) {
	u8 ret;
	asm volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

void init_serial() { outb(COM1 + 4, 0x0F); }

void putstr_serial(char *str) {
	for (int i = 0; str[i]; i++) {
		outb(COM1, str[i]);
	}
}
