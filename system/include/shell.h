#pragma once
# include "dinio.h"
# include "dinostring.h"
# include "timer.h"
# include "workspace.h"

void	shell();
void	init_shell();
int	check_arg(char *cmd, char *str);
int	sh_atoi(const char *str);
void	sh_putstr(char *str);
void	stack(char *cmd);
void	echo(char *cmd);
void	lilalelolu();
void	sh_switch(char *cmd);
void	theme(char *cmd);
int	get_color(char *str);

# define PS1 "DinOS> "

# define STACK		"stack"
# define STACK_USAGE	"stack <value>"
# define SWITCH		"switch"
# define SWITCH_USAGE	"switch <value>"
# define ECHO		"echo"
# define ECHO_USAGE	"echo <message>"
# define LILALELOLU	"lilalelolu"
# define THEME		"theme\0"
# define THEME_USAGE	"theme <foreground color> <background color>"

# define WRONG_COLOR	16
# define BUFF_SIZE	2000

# define ERSYNT	    "dinosh: Usage: %s"
# define ERVALUE    "dinosh: Unexpected value"
# define UNKNOWN    "dinosh: Command not found"
# define ERTOOBIG   "dinosh: Value too big (max: %d)"
# define ERCOLOR    "dinosh: Color is not valid"

# define args(x) (cmd + strlen(x))
