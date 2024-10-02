#include "shell.h"

int ps1_len	= 0;
int switching	= 0;

void interpret() {
    char *cmd = get_command(video_memory);

    if (check_arg(cmd, STACK))
	stack(args(STACK));
    else if (check_arg(cmd, ECHO))
	echo(args(ECHO));
    else if (check_arg(cmd, LILALELOLU))
	lilalelolu(args(LILALELOLU));
    else if (check_arg(cmd, SWITCH))
	sh_switch(args(SWITCH));
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
