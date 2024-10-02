#include "shell.h"

int check_arg(char *cmd, char *str) {
    int	i;

    i = 0;
    while (cmd[i] == str[i] && cmd[i] != ' ' && cmd[i] && str[i]) {
		i++;
    }
	if (cmd[i] == ' ' && !str[i])
		return 1;
    return !((unsigned char)cmd[i] - (unsigned char)str[i]); 
}

int get_color(char *str) {
	if (check_arg(str, "black"))
		return BLACK;
	else if (check_arg(str, "blue"))
		return BLUE;
	else if (check_arg(str, "green"))
		return GREEN;
	else if (check_arg(str, "cyan"))
		return CYAN;
	else if (check_arg(str, "red"))
		return RED;
	else if (check_arg(str, "magenta"))
		return MAGENTA;
	else if (check_arg(str, "brown"))
		return BROWN;
	else if (check_arg(str, "light_gray"))
		return LGRAY;
	else if (check_arg(str, "dark_gray"))
		return DGRAY;
	else if (check_arg(str, "light_blue"))
		return LBLUE;
	else if (check_arg(str, "light_green"))
		return LGREEN;
	else if (check_arg(str, "light_cyan"))
		return LCYAN;
	else if (check_arg(str, "light_red"))
		return LRED;
	else if (check_arg(str, "light_magenta"))
		return LMAGENTA;
	else if (check_arg(str, "yellow"))
		return YELLOW;
	else if (check_arg(str, "white"))
		return WHITE;
	return WRONG_COLOR;
}
