#include "dinio.h"

int handle_special_char(char c) {
    if (c == '\n') {
        last_written_addr = NEXT_LINE;
        return 1;
    } else if (c == '\r') {
        last_written_addr = START_LINE;
        return 1;
    }
    return 0;
}

void writek(char *str, unsigned char color, int len) {
    for (int i = 0; i < len; i++) {
        if (handle_special_char(str[i]))
            continue;
        *last_written_addr = str[i];
        *(last_written_addr + 1) = color;
        last_written_addr += 2;
    }
}
