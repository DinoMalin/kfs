#include "dinio.h"

void putshark(unsigned char c, unsigned char color, int x, int y) {
    if (x > COL)
        x = 0;
    if (y > LIN)
        y = LIN;

    int offset = (y * LIN + x) * 2;
    video_memory[offset] = c;
    video_memory[offset + 1] = color;
}

void putstrk(char *str, unsigned char color, int x, int y) {
    for (int i = 0; str[i]; i++) {
        if (x > COL) {
            x = 0;
            y++;
        }
        if (y > LIN) {
            y = LIN;
            x = 0;
        }
        putshark(str[i], color, x++, y);
    }
}
