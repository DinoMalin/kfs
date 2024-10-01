#include "cursor.h"

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
	outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xC0) | cursor_start);

	outb(CURSOR_CMD, 0x0B);
	outb(CURSOR_DATA, (inb(CURSOR_DATA) & 0xE0) | cursor_end);
}

void disable_cursor() {
    outb(CURSOR_CMD, 0x0A);
	outb(CURSOR_CMD, 0x20);
}

void move_cursor() {
    uint16_t pos = (video_memory - START_VMEM) / 2;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (uint8_t) (pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
    outb(CURSOR_DATA, (uint8_t) ((pos >> 8) & 0xFF));
}

