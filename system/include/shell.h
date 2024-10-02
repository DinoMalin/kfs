#pragma once
# include "dinio.h"
# include "dinostring.h"
# include "timer.h"

void	shell();
void	init_shell();
int	check_arg(char *cmd, char *str);
int	sh_atoi(const char *str);
void	sh_putstr(char *str);
void	stack(char *cmd);
void	echo(char *cmd);
void	lilalelolu();

# define PS1 "DinOS> "

# define STACK		"stack"
# define STACK_USAGE	"stack <value>"
# define ECHO		"echo"
# define ECHO_USAGE	"echo <message>"
# define LILALELOLU	"lilalelolu"

# define ERSYNT	    "dinosh: Usage: %s"
# define ERVALUE    "dinosh: Unexpected value"
# define UNKNOWN    "dinosh: Command not found"
# define ERTOOBIG   "dinosh: Value too big (max: %d)"

# define args(x) (cmd + (strlen(x) * 2))
