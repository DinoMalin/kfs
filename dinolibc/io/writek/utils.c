#include "writek.h"

void scroll() {
	for (int i = 0; !is_last_line(START_VMEM + i); i += 2) {
		copy_next_line(START_VMEM + i);
		copy_next_line(START_VMEM + i + 1);
	}
	for (int i = 3840; i <= 4000; i += 2) {
		START_VMEM[i] = 0;
	}
	video_memory = LAST_LINE;
}

void backspace() {
	unsigned char *start_line = reach_command(video_memory);
	while (*video_memory == 0 && video_memory > start_line) {
		video_memory -= 2;
		putchar_serial('\b');
	}
	putchar_serial(' ');
	putchar_serial('\b');
	clear_cell(video_memory);
}
