#include "shell.h"

int ps1_len = 0;
int switching = 0;
int executed = 0;

void command(char *cmd, char *line, void (*handler)(char *)) {
	if (executed || !check_arg(cmd, line))
		return;
	handler(args(line));
	executed = 1;
}

void interpret() {
	char cmd[BUFF_SIZE];
	fill_buffer(cmd);

	command(cmd, MEMORY, memory);
	command(cmd, ECHO, echo);
	command(cmd, LILALELOLU, lilalelolu);
	command(cmd, SWITCH, sh_switch);
	command(cmd, THEME, theme);
	command(cmd, HELP, help);
	command(cmd, MAN, help);
	command(cmd, REBOOT, reboot);
	command(cmd, HALT, halt);

	if (!executed)
		printk(UNKNOWN);
	executed = 0;
}

void shell() {
	interpret();
	if (!switching)
		printk(PS1);
	switching = 0;
}

void init_shell() {
	apply_color(default_color);
	ps1_len = strlen(PS1);
	printk(PS1);
}
