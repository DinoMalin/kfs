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

unsigned char *video_memory = (unsigned char *)0xB8000;

void putshark(unsigned char c, unsigned char color, int x, int y)
{
    if (x > COL)
        x = 0;
    if (y > LIN)
        y = LIN;

    int offset = (y * LIN + x) * 2;
    video_memory[offset] = c;
    video_memory[offset + 1] = color;
}

void putstrk(char *str, unsigned char color, int x, int y)
{
    for (int i = 0; str[i]; i++)
    {
        if (x > COL)
        {
            x = 0;
            y++;
        }
        if (y > LIN)
        {
            y = LIN;
            x = 0;
        }
        putshark(str[i], color, x++, y);
    }
}

void kmain()
{
    putstrk("42 | DinoMalin was here", combine(WHITE, BLUE), 0, 0);
}
