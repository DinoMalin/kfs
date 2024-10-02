#include "shell.h"

void stack(char *cmd) {
    int i = 0;
    int wrong = 0;

    if (cmd[i] != ' ') {
	wrong = 1;
	printk(ERSYNT, STACK_USAGE);
    }
    i += 2;

    if (!wrong && !isdigit(cmd[i])) {
	wrong = 1;
	printk(ERVALUE);
    }

    int lines = sh_atoi(cmd);
    if (lines > LIN) {
	wrong = 1;
	printk(ERTOOBIG, LIN);
    }
    if (!wrong)
	print_stack(lines);
}

void echo(char *cmd) {
    int i = 0;
    int wrong = 0;

    if (cmd[i] != ' ') {
		wrong = 1;
		printk(ERSYNT, ECHO_USAGE);
    }
    i += 2;
	printk("");
	sh_putstr(&cmd[i]);
}

void	lilalelolu() {
		printk("lalelilalo");
}
