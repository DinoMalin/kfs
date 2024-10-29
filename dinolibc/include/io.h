#pragma once

#include "cursor.h"
#include "types.h"

#define LIN 24
#define COL 80

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LGRAY 7

#define DGRAY 8
#define LBLUE 9
#define LGREEN 10
#define LCYAN 11
#define LRED 12
#define LMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define START_VMEM ((unsigned char *)0xB8000)
#define LAST_LINE ((unsigned char *)0xB8F00)
#define END_VMEM ((unsigned char *)0xB8FA0)

#define combine(bg, fg) (bg * 16 + fg)
#define color_cell(vmem)                                                       \
	{ vmem[1] = default_color; }
#define clear_cell(vmem)                                                       \
	{                                                                          \
		vmem[0] = 0;                                                           \
		vmem[1] = default_color;                                               \
	}
#define go_start_line(vmem)                                                    \
	((unsigned char *)vmem -= (((vmem - START_VMEM) / 2) % COL) * 2)

#define COM1 0x3f8
#define putchar_serial(c) outb(COM1, c)

#define DEFAULT combine(WHITE, BLACK)

extern unsigned char *video_memory;
extern int default_color;
extern int ps1_len;

void writek(char *str, unsigned char color, int len);
int printk(char *str, ...);
void print_stack(int nb);
void print_memory(int nb, unsigned int addr);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void init_serial();
void putstr_serial(char *str);

void color_screen();
void clear_screen();
