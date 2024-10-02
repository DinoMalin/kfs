#include "shell.h"

int ps1_len = 0;

void interpret() {
    char *cmd = get_command(video_memory);

    if (check_arg(cmd, STACK))
	stack(args(STACK));
    else if (check_arg(cmd, ECHO))
	echo(args(ECHO));
    else if (check_arg(cmd, LILALELOLU))
	lilalelolu(args(LILALELOLU));
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
