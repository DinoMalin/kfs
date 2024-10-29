#pragma once
#include "io.h"

#define is_last_line(vmem) (vmem >= LAST_LINE ? 1 : 0)
#define reach_command(vmem)                                                    \
	(vmem - (vmem - START_VMEM) % (COL * 2) + ps1_len * 2)

#define copy_next_line(vmem) (vmem)[0] = (vmem)[COL * 2];
#define go_next_line(vmem)                                                     \
	((unsigned char *)vmem += (COL - (((vmem - START_VMEM) / 2) % COL)) * 2)

void scroll();
void backspace();
