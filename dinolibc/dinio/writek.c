#include "dinio.h"

unsigned char *video_memory = START_VMEM;
int default_color = DEFAULT;

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
	unsigned char *start_line = get_command(video_memory);
	while (*video_memory == 0 && video_memory > start_line) {
		video_memory -= 2;
		putchar_serial('\b');
	}
	putchar_serial(' ');
	putchar_serial('\b');
	clear_cell(video_memory);
}

static int handle_special_char(char c) {
	switch (c) {
	case '\n':
		if (is_last_line(video_memory))
			scroll();
		else
			go_next_line(video_memory);
		putchar_serial('\n');
		return 1;

	case '\r':
		go_start_line(video_memory);
		putchar_serial('\r');
		return 1;

	case '\b':
		backspace();
		return 1;
	}

	return 0;
}

void writek(char *str, unsigned char color, int len) {
	for (int i = 0; i < len; i++) {
		if (handle_special_char(str[i]))
			continue;
		if (video_memory >= END_VMEM)
			scroll();

		video_memory[0] = str[i];
		video_memory[1] = color;
		putchar_serial(str[i]);

		video_memory += 2;
	}
	move_cursor();
}
