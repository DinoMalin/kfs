#include "workspace.h"

workspace	ws[NB_WS]   = {0};
unsigned char	active_ws   = 0;

void	copy_workspace() {
    for (int i = 0; i < 4000; i++)
	ws[active_ws].vmem[i] = START_VMEM[i];

    ws[active_ws].cursor = video_memory;
}

void	display_workspace() {
    for (int i = 0; i < 4000; i++)
	START_VMEM[i] = ws[active_ws].vmem[i];

    if (ws[active_ws].cursor)
	video_memory = ws[active_ws].cursor;
    else {
 	video_memory = START_VMEM;
	init_shell();
    }
    move_cursor();
}

void	auto_switch_workspace() {
    copy_workspace(); 

    if (active_ws >= NB_WS - 1)
	active_ws = 0;
    else
	active_ws++;

    display_workspace();
}

void	switch_workspace(int nb) {
    copy_workspace(); 
    
    if (nb < NB_WS && nb >= 0 && nb != active_ws)
	active_ws = nb;

    display_workspace();
}
