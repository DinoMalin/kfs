#include "shell.h"

extern int switching;

void lilalelolu() { printk("lalelilalo"); }
void help(char *cmd) { printk(HELP_MSG); }
void reboot(char *cmd) { end = EXIT_REBOOT; }
void halt(char *cmd) { end = EXIT_HALT; }
void _valgrind(char *cmd) { valgrind(); }

void echo(char *cmd) {
	next_arg(cmd);
	printk("%s", cmd);
}

void _layout(char *cmd) {
	int nb_args = count_args(cmd);
	if (!good_syntax(cmd) || (nb_args != LAYOUT_ARGS)) {
		printk(ERSYNT, LAYOUT_USAGE);
		return;
	}

	next_arg(cmd);
	if (!strcmp(cmd, "azerty"))
		switch_layout(FR);
	else if (!strcmp(cmd, "qwerty"))
		switch_layout(US);
	else
		printk(ERNOLAYOUT);
}

void memory(char *cmd) {
	int nb_args = count_args(cmd);
	if (!good_syntax(cmd) ||
		(nb_args != MEMORY_ARGS && nb_args != MEMORY_ARGS_OPT)) {
		printk(ERSYNT, MEMORY_USAGE);
		return;
	}

	next_arg(cmd);
	int lines = atoi(cmd);
	if (!isdigit(*cmd)) {
		printk(ERVALUE);
		return;
	}
	if (lines > LIN) {
		printk(ERTOOBIG, LIN);
		return;
	}

	if (nb_args == MEMORY_ARGS) {
		print_stack(lines);
		return;
	}

	next_arg(cmd);
	if (strncmp(cmd, "0x", 2) || skip_prefix(cmd) || !valid_address(cmd)) {
		printk(ERADDR);
		return;
	}
	u32 addr = address(cmd);
	print_memory(lines, addr);
}

void _switch(char *cmd) {
	int nb_args = count_args(cmd);
	if (!good_syntax(cmd) || (nb_args != SWITCH_ARGS)) {
		printk(ERSYNT, SWITCH_USAGE);
		return;
	}

	next_arg(cmd);
	int workspace = atoi(cmd);

	if (!isdigit(*cmd)) {
		printk(ERVALUE);
		return;
	}
	if (workspace > NB_WS) {
		printk(ERTOOBIG, NB_WS);
		return;
	}

	printk(PS1);
	switch_workspace(workspace - 1);
	switching = 1;
}

void theme(char *cmd) {
	int nb_args = count_args(cmd);
	if (!good_syntax(cmd) ||
		(nb_args != THEME_ARGS && nb_args != THEME_ARGS_OPT)) {
		printk(ERSYNT, THEME_USAGE);
		return;
	}

	next_arg(cmd);
	if (nb_args == 1) {
		int custom = custom_theme(cmd);
		if (!custom)
			printk(ERSYNT, THEME_USAGE);
		else
			apply_color(custom);
		return;
	}

	int fg = get_color(cmd);
	next_arg(cmd);
	int bg = get_color(cmd);

	if (fg == WRONG_COLOR || bg == WRONG_COLOR) {
		printk(ERCOLOR, THEME_USAGE);
		return;
	}
	apply_color(combine(bg, fg));
}

void _syscall(char *cmd) {
	int nb_args = count_args(cmd);
	if (!good_syntax(cmd) || (nb_args != SYSCALL_ARGS)) {
		printk(ERSYNT, SYSCALL_USAGE);
		return;
	}

	next_arg(cmd);
	int call = atoi(cmd);

	if (!isdigit(*cmd)) {
		printk(ERVALUE);
		return;
	}

	syscall(call);
}
