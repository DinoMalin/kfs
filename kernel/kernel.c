# define LIN 24
# define COL 80

# define BLACK      0
# define BLUE       1
# define GREEN      2
# define CYAN       3
# define RED        4
# define MAGENTA    5
# define BROWN      6
# define LGRAY      7

# define DGRAY      8
# define LBLUE      9
# define LGREEN     10
# define LCYAN      11
# define LRED       12
# define LMAGENTA   13
# define YELLOW     14
# define WHITE      15

# define combine(bg, fg) (bg * 16 + fg)
# define NEXT_LINE      last_written_addr + (COL - (((last_written_addr - video_memory) / 2) % COL)) * 2
# define START_LINE   last_written_addr - (((last_written_addr - video_memory) / 2) % COL) * 2

unsigned char *video_memory         = (unsigned char *)0xB8000;
unsigned char *last_written_addr    = (unsigned char *)0xB8000;

int strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

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

void kmain() {
    char s1[] = "42 | DinoMalin was here\nThis is the line 2";
    char s2[] = "\r42 | DinoMalin was here\nThis is the line 3";
    writek(s1, combine(WHITE, BLUE), strlen(s1));
    writek(s2, combine(WHITE, BLUE), strlen(s2));

}
