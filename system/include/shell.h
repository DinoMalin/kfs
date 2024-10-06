#pragma once
# include "dinio.h"
# include "dinostring.h"
# include "timer.h"
# include "workspace.h"

void	shell();
void	init_shell();

void	stack(char *cmd);
void	echo(char *cmd);
void	lilalelolu();
void	sh_switch(char *cmd);
void	theme(char *cmd);
void	help(char *cmd);
void	reboot(char *cmd);
void	halt(char *cmd);

int		check_arg(char *cmd, char *str);
int		get_color(char *str);
int		count_args(char *str);
int		good_syntax(char *str);
void	fill_buffer(char *buff);

extern int ps1_len;
extern int exit;

# define STACK			"stack"
# define STACK_USAGE	"stack <value>"
# define STACK_ARGS		1

# define SWITCH			"switch"
# define SWITCH_USAGE	"switch <value>"
# define SWITCH_ARGS	1

# define ECHO			"echo"
# define ECHO_USAGE		"echo <message>"
# define ECHO_ARGS		1

# define THEME			"theme"
# define THEME_USAGE	"theme <foreground color> <background color>"
# define THEME_ARGS		1
# define THEME_ARGS_OPT	2

# define LILALELOLU		"lilalelolu"
# define HELP			"help"
# define MAN			"man"
# define REBOOT			"reboot"
# define HALT			"halt"

# define WRONG_COLOR	16
# define BUFF_SIZE		2000

# define ERSYNT	    "dinosh: Usage: %s"
# define ERVALUE    "dinosh: Unexpected value"
# define UNKNOWN    "dinosh: Command not found"
# define ERTOOBIG   "dinosh: Value too big (max: %d)"
# define ERCOLOR    "dinosh: Color is not valid"

# define EXIT_REBOOT	1;
# define EXIT_HALT		2;

# define args(x)					(cmd + strlen(x))
# define isword(c)					(isalpha(c) || isdigit(c) || c == '_' || c == '-')
# define authorized_character(c)	(isword(c) || c == ' ')

# define next_arg(str)				{while (isword(*str)) {str++;} while (*str == ' ') {str++;}}
# define apply_color(color)			{default_color = color; color_screen();}
# define add_theme(name, bg, fg)	if (check_arg(str, name)) return combine(bg, fg)

# define HELP_MSG	"DINOS - HELP\n" \
					"echo <value>                           display <value> on the output.\n" \
					"\n" \
					"halt                                   halt the computer.\n" \
					"\n" \
					"lilalelolu                             lalelilalo\n" \
					"\n" \
					"reboot                                 restart the computer.\n" \
					"\n" \
					"stack <number>                         display <number> lines from the stack,\n" \
					"                                       with 16 bytes per line.\n" \
					"\n" \
					"switch <number>                        switch to the <number> workspace.\n" \
					"\n" \
					"theme <foreground> <background>        modify the colors of the output.\n" \
					"      <theme>                          use a custom theme.\n" \
