#include "essentials.h"
#include "shell.h"
#include "string.h"

char *line;
int len = 0;
int size_buff = RL_BUFF_SIZE;

void init_readline() { line = vmalloc(RL_BUFF_SIZE); }

void realloc_line() {
	size_buff += RL_BUFF_SIZE;
	char *new_line = vmalloc(size_buff);

	memcpy(new_line, line, size_buff);

	vfree(line);
	line = new_line;
}

void add_character(char c) {
	if (!line) {
		kernel_panic("allocation error", NO_EXIT);
		submit_line();
	}

	if (c == '\b') {
		line[len] = '\0';
		len--;
	} else {
		if (len >= size_buff - 1)
			realloc_line();
		line[len] = c;
		len++;
	}
}

char *readline() {
	static int index = 0;
	int start_cmd = index;
	int size_cmd = len - start_cmd;

	if (!size_cmd)
		return NULL;

	line[len] = 0;
	index += size_cmd;

	return line + start_cmd;
}
