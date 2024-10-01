#include "dinio.h"

unsigned char *video_memory         = START_VMEM;

void scroll() {
   for (int i = 0; START_VMEM + i < LAST_LINE; i += 2) {
       START_VMEM[i] = START_VMEM[i + COL * 2];
       START_VMEM[i + 1] = START_VMEM[i + 1 + COL * 2];
   }
   for (int i = 3840; i <= 4000; i++)
       START_VMEM[i] = 0;
   video_memory = START_LINE;
}

int handle_special_char(char c) {
    if (c == '\n') {
        if (video_memory >= LAST_LINE)
            scroll();
        else
            video_memory = NEXT_LINE;
        return 1;
    } else if (c == '\r') {
        video_memory = START_LINE;
        return 1;
    } else if (c == '\b') {
        video_memory -= 2;
        *video_memory = 0;
        *(video_memory + 1) = 0;
        return 1;
    }
    return 0;
}

void writek(char *str, unsigned char color, int len) {
    for (int i = 0; i < len; i++) {
        if (handle_special_char(str[i]))
            continue;
        *video_memory = str[i];
        *(video_memory + 1) = color;
        video_memory += 2;
    }
}
