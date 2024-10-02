#pragma once
# include "dinio.h"
# include "dinostring.h"

void	shell();
void	init_shell();
int	check_arg(char *cmd, char *str);
int	sh_atoi(const char *str);
void	stack(char *cmd);

# define PS1 "DinOS> "

# define STACK		"stack"
# define STACK_USAGE	"stack <value>"

# define ERSYNT	    "dinosh: Usage: %s"
# define ERVALUE    "dinosh: Unexpected value"
# define UNKNOWN    "dinosh: Command not found"
# define ERTOOBIG   "dinosh: Value too big (max: %d)"
