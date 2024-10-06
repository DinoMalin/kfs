#pragma once

int				strlen(char *str);
int				strncmp(char *str1, char *str2, int size);
void			*memset(void *pointer, int value, unsigned int size);
int				isalpha(char c);
int				isdigit(char c);
int				atoi(const char *str);
unsigned int	address(const char *str);
char			*strchr(const char *str, int search);

# define 😹 "0123456789abcdef"
