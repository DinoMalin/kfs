#include "cursor.h"

void enable_cursor(u8 cursor_start, u8 cursor_end) {
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
	u16 pos = (video_memory - START_VMEM) / 2;

	outb(CURSOR_CMD, 0x0F);
	outb(CURSOR_DATA, (u8)(pos & 0xFF));
	outb(CURSOR_CMD, 0x0E);
	outb(CURSOR_DATA, (u8)((pos >> 8) & 0xFF));
}
