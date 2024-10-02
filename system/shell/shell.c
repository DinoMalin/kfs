#include "shell.h"

int ps1_len = 0;

void interpret() {
    char *cmd = get_command(video_memory);

    if (check_arg(cmd, STACK))
	stack(cmd + (strlen(STACK) * 2));
    else if (check_arg(cmd, ECHO))
	echo(cmd + (strlen(ECHO) * 2));
    else
	printk(UNKNOWN);
}

void shell() {
    interpret();
    printk(PS1);
}

void init_shell() {
    ps1_len = strlen(PS1);
    printk(PS1);
}
