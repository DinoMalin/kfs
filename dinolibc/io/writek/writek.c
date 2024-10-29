#include "writek.h"

unsigned char *video_memory = START_VMEM;
int default_color = DEFAULT;

static int handle_special_char(char c) {
	switch (c) {
	case '\n':
		is_last_line(video_memory) ? scroll() : go_next_line(video_memory);
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
