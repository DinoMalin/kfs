#include "shell.h"

int ps1_len	= 0;
int switching	= 0;

void fill_buffer(char *buff) {
    unsigned char *start = video_memory;
    go_start_line(start);
    start += ps1_len * 2;

    int i = 0;
    int j = 0;

    while (start + i < END_VMEM) {
	buff[j] = start[i];
	i += 2;
	j++;
    }
}

void interpret() {
    char cmd[BUFF_SIZE];
    fill_buffer(cmd);

    if (check_arg(cmd, STACK))
	stack(args(STACK));
    else if (check_arg(cmd, ECHO))
	echo(args(ECHO));
    else if (check_arg(cmd, LILALELOLU))
	lilalelolu(args(LILALELOLU));
    else if (check_arg(cmd, SWITCH))
	sh_switch(args(SWITCH));
    else if (check_arg(cmd, THEME))
	theme(args(THEME));
    else
	printk(UNKNOWN);
}

void shell() {
    interpret();
    if (!switching)
	printk(PS1);
    switching = 0;
}

void init_shell() {
    ps1_len = strlen(PS1);
    printk(PS1);
}
