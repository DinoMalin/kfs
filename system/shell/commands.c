#include "shell.h"

extern int switching;

void echo(char *cmd) {
    int i = 0;

    if (cmd[i] != ' ') {
		printk(ERSYNT, ECHO_USAGE);
		return ;
    }
    i += 2;
	printk("");
	sh_putstr(&cmd[i]);
}

void stack(char *cmd) {
    int i = 0;

    if (cmd[i] != ' ') {
		printk(ERSYNT, STACK_USAGE);
		return ;
    }
    i += 2;

    if (!isdigit(cmd[i])) {
		printk(ERVALUE);
		return ;
    }

    int lines = sh_atoi(cmd);
    if (lines > LIN) {
		printk(ERTOOBIG, LIN);
		return ;
    }
	print_stack(lines);
}

void sh_switch(char *cmd) {
    int i = 0;

    if (cmd[i] != ' ') {
		printk(ERSYNT, SWITCH_USAGE);
		return ;
    }
    i += 2;

    if (!isdigit(cmd[i])) {
		printk(ERVALUE);
		return ;
    }

    int nb = sh_atoi(cmd);
    if (nb > NB_WS) {
		printk(ERTOOBIG, NB_WS);
		return ;
    }

	printk(PS1);
	switch_workspace(nb - 1);
	switching = 1;
}

void theme(char *cmd) {
	int i = 0;

    if (cmd[i] != ' ') {
		printk(ERSYNT, THEME_USAGE);
		return ;
    }
    i += 2;
    if (!isalpha(cmd[i])) {
		printk(ERSYNT, THEME_USAGE);
		return ;
    }

	int fg = get_color(&cmd[i]);

	while (isalpha(cmd[i]))
		i += 2;
    if (cmd[i] != ' ') {
		printk(ERSYNT, THEME_USAGE);
		return ;
    }
	i += 2;
    if (!isalpha(cmd[i])) {
		printk(ERSYNT, THEME_USAGE);
		return ;
    }

	int bg = get_color(&cmd[i]);
	if (fg == WRONG_COLOR || bg == WRONG_COLOR) {
			printk(ERCOLOR);
			return ;
	}

	default_color = combine(bg, fg);
    color_screen();
}

void	lilalelolu() {
		printk("lalelilalo");
}
