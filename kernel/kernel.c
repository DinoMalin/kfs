#include "dinio.h"
#include "dinostring.h"

unsigned char *video_memory         = (unsigned char *)0xB8000;
unsigned char *last_written_addr    = (unsigned char *)0xB8000;

void kmain() {
    char s1[] = "42 | DinoMalin was here\nThis is the line 2";
    char s2[] = "\r42 | DinoMalin was here\nThis is the line 3";
    writek(s1, combine(MAIN_COLOR_BG, MAIN_COLOR_FG), strlen(s1));
    writek(s2, combine(MAIN_COLOR_BG, MAIN_COLOR_FG), strlen(s2));
}
