#pragma once

#include "essentials.h"
#include "io.h"
#include "string.h"
#include "timer.h"
#include "workspace.h"

void shell();
void init_shell();

void memory(char *cmd);
void echo(char *cmd);
void lilalelolu();
void sh_switch(char *cmd);
void theme(char *cmd);
void help(char *cmd);
void reboot(char *cmd);
void halt(char *cmd);
void _valgrind(char *cmd);

char *readline();
int check_arg(char *cmd, char *str);
int get_color(char *str);
int count_args(char *str);
int good_syntax(char *str);
int custom_theme(char *str);

extern int ps1_len;
extern int end;

#define MEMORY "memory"
#define MEMORY_USAGE "memory <number> [address]"
#define MEMORY_ARGS 1
#define MEMORY_ARGS_OPT 2

#define SWITCH "switch"
#define SWITCH_USAGE "switch <value>"
#define SWITCH_ARGS 1

#define ECHO "echo"
#define ECHO_USAGE "echo <message>"
#define ECHO_ARGS 1

#define THEME "theme"
#define THEME_USAGE "theme <foreground color> <background color>"
#define THEME_ARGS 1
#define THEME_ARGS_OPT 2

#define LILALELOLU "lilalelolu"
#define HELP "help"
#define MAN "man"
#define REBOOT "reboot"
#define HALT "halt"
#define VALGRIND "valgrind"

#define WRONG_COLOR 16
#define BUFF_SIZE 2000

#define ERSYNT "dinosh: Usage: %s"
#define ERVALUE "dinosh: Unexpected value"
#define UNKNOWN "dinosh: Command not found"
#define ERTOOBIG "dinosh: Value too big (max: %d)"
#define ERCOLOR "dinosh: Color is not valid"
#define ERADDR "dinosh: Address is not valid"

#define EXIT_REBOOT 1;
#define EXIT_HALT 2;

#define args(x) (cmd + strlen(x))
#define isword(c) (isalpha(c) || isdigit(c) || c == '_' || c == '-')
#define authorized_character(c) (isword(c) || c == ' ')

#define next_arg(str)                                                          \
	{                                                                          \
		while (isword(*str)) {                                                 \
			str++;                                                             \
		}                                                                      \
		while (*str == ' ') {                                                  \
			str++;                                                             \
		}                                                                      \
	}
#define apply_color(color)                                                     \
	{                                                                          \
		default_color = color;                                                 \
		color_screen();                                                        \
	}
#define add_theme(name, bg, fg)                                                \
	if (check_arg(str, name))                                                  \
		return combine(bg, fg);
#define add_color(name, color)                                                 \
	if (check_arg(str, name))                                                  \
		return color;

#define skip_prefix(str) !(str += 2)

#define HELP_MSG                                                               \
	"DINOS - HELP\n"                                                           \
	"echo <value>                 display <value> on the output.\n"            \
	"\n"                                                                       \
	"halt                         halt the computer.\n"                        \
	"\n"                                                                       \
	"lilalelolu                   lalelilalo\n"                                \
	"\n"                                                                       \
	"reboot                       restart the computer.\n"                     \
	"\n"                                                                       \
	"memory <number> [address]    display <number> lines from the given "      \
	"address,\n"                                                               \
	"                             address with 16 bytes per line. If address " \
	"is\n"                                                                     \
	"                             unspecified, display <number> lines from "   \
	"the stack.\n"                                                             \
	"                             address must start with 0x and be in "       \
	"hexadecimal."                                                             \
	"\n"                                                                       \
	"switch <number>              switch to the <number> workspace.\n"         \
	"\n"                                                                       \
	"theme <fg> <bg>              modify the colors of the output.\n"          \
	"      <theme>                use a custom theme.\n"\
