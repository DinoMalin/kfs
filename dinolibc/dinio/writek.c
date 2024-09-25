#include "dinio.h"

void scroll() {
   for (int i = 0; !islastline(video_memory + i); i += 2) {
       video_memory[i] = video_memory[i + COL * 2];
       video_memory[i + 1] = video_memory[i + 1 + COL * 2];
   }
   for (int i = 3840; i <= 4000; i++)
       video_memory[i] = 0;
   last_written_addr = START_LINE;
}

int handle_special_char(char c) {
    if (c == '\n') {
        if (islastline(last_written_addr))
            scroll();
        else
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
