#include "shell.h"

extern int switching;

void echo(char *cmd) {
	next_arg(cmd);
	printk("%s", cmd);
}

void help(char *cmd) {
	printk(HELP_MSG);
}

void stack(char *cmd) {
    int nb_args = count_args(cmd);
    if (!good_syntax(cmd) || (nb_args != STACK_ARGS)) {
		printk(ERSYNT, STACK_USAGE);
		return ;
    }

    next_arg(cmd);
    int lines = atoi(cmd);

    if (!isdigit(*cmd)) {
		printk(ERVALUE);
		return ;
    }
    if (lines > LIN) {
		printk(ERTOOBIG, LIN);
		return ;
    }

	print_stack(lines);
}

void sh_switch(char *cmd) {
    int nb_args = count_args(cmd);
    if (!good_syntax(cmd) || (nb_args != SWITCH_ARGS)) {
		printk(ERSYNT, STACK_USAGE);
		return ;
    }

    next_arg(cmd);
    int workspace = atoi(cmd);

    if (!isdigit(*cmd)) {
		printk(ERVALUE);
		return ;
    }
    if (workspace > NB_WS) {
		printk(ERTOOBIG, NB_WS);
		return ;
    }

	printk(PS1);
	switch_workspace(workspace - 1);
	switching = 1;
}

void theme(char *cmd) {
    int nb_args = count_args(cmd);
    if (!good_syntax(cmd) || (nb_args != THEME_ARGS && nb_args != THEME_ARGS_OPT)) {
		printk(ERSYNT, THEME_USAGE);
		return ;
    }

    next_arg(cmd);
    if (nb_args == 1) {
        int custom = custom_theme(cmd);
        if (!custom)
            printk(ERSYNT, THEME_USAGE);
        else
            apply_color(custom);
        return ;
    }

    int fg = get_color(cmd);
    next_arg(cmd);
    int bg = get_color(cmd);

    if (fg == WRONG_COLOR || bg == WRONG_COLOR) {
		printk(ERCOLOR, THEME_USAGE);
		return ;
    }
    apply_color(combine(bg, fg));
}

void	lilalelolu() {
		printk("lalelilalo");
}

