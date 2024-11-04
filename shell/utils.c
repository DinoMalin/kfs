#include "shell.h"

int check_arg(char *cmd, char *str) {
	int i;

	i = 0;
	while (cmd[i] == str[i] && cmd[i] != ' ' && cmd[i] && str[i]) {
		i++;
	}
	if (cmd[i] == ' ' && !str[i])
		return 1;
	return !((u8)cmd[i] - (u8)str[i]);
}

int get_color(char *str) {
	add_color("black", BLACK);
	add_color("blue", GREEN);
	add_color("cyan", CYAN);
	add_color("red", RED);
	add_color("magenta", MAGENTA);
	add_color("brown", BROWN);
	add_color("light_gray", LGRAY);
	add_color("dark_gray", DGRAY);
	add_color("light_blue", LBLUE);
	add_color("light_green", LGREEN);
	add_color("light_cyan", LCYAN);
	add_color("light_red", LRED);
	add_color("light_magenta", LMAGENTA);
	add_color("yellow", YELLOW);
	add_color("white", WHITE);
	return WRONG_COLOR;
}

int custom_theme(char *str) {
	add_theme("dinosaur", LGREEN, BLACK);
	add_theme("papyrus", YELLOW, BLACK);
	add_theme("demolinux", MAGENTA, WHITE);
	add_theme("powershell", BLUE, WHITE);
	add_theme("casamit", BLACK, MAGENTA);
	add_theme("rosa", MAGENTA, LGREEN);
	add_theme("louis", BLUE, CYAN);
	add_theme("default", BLACK, WHITE);
	return 0;
}

int count_args(char *str) {
	int is_arg = 0;
	int result = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == ' ' && is_arg)
			is_arg = 0;
		else if (str[i] != ' ') {
			if (!is_arg)
				result++;
			is_arg = 1;
		}
	}

	return result;
}

int good_syntax(char *str) {
	for (int i = 0; str[i]; i++) {
		if (!authorized_character(str[i]))
			return 0;
	}
	return 1;
}
