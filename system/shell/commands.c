#include "shell.h"

extern int switching;

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

void sh_switch(char *cmd) {
    int i = 0;
    int wrong = 0;

    if (cmd[i] != ' ') {
		wrong = 1;
		printk(ERSYNT, SWITCH_USAGE);
    }
    i += 2;

    if (!wrong && !isdigit(cmd[i])) {
		wrong = 1;
		printk(ERVALUE);
    }

    int nb = sh_atoi(cmd);
    if (nb > NB_WS) {
		wrong = 1;
		printk(ERTOOBIG, NB_WS);
    }

    if (!wrong) {
		printk(PS1);
		switch_workspace(nb - 1);
		switching = 1;
	}
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
