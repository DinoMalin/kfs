# pragma once
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

# ifndef MAIN_COLOR_BG
# 	define MAIN_COLOR_BG BLUE
# endif

# ifndef MAIN_COLOR_FG
# 	define MAIN_COLOR_FG BLUE
# endif

void    writek(char *str, unsigned char color, int len);
