#include "workspace.h"

workspace	ws[NB_WS]   = {0};
unsigned char	active_ws   = 0;

void	copy_workspace() {
    for (int i = 0; i < 4000; i += 2)
	ws[active_ws].vmem[i] = START_VMEM[i];

    ws[active_ws].cursor = video_memory;
}

void	display_workspace() {
    for (int i = 0; i < 4000; i += 2)
	START_VMEM[i] = ws[active_ws].vmem[i];

    if (ws[active_ws].cursor)
	video_memory = ws[active_ws].cursor;
    else
	video_memory = START_VMEM;

    move_cursor();
}

void	switch_workspace() {
    copy_workspace(); 

    if (active_ws >= NB_WS - 1)
	active_ws = 0;
    else
	active_ws++;

    display_workspace();
}
