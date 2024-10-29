#pragma once

#include "io.h"
#include "string.h"
#include "variadic.h"

#define FORMAT(format, ret)                                                    \
	{                                                                          \
		int len = strlen(format);                                              \
		if (!strncmp(format, str, len)) {                                      \
			*index += len;                                                     \
			return (ret);                                                      \
		}                                                                      \
	}

int putnbr(int n);
int putunbr(unsigned int n);
int puthexa(unsigned int n);

int putbit(unsigned int n);
int putbyte(unsigned int n);
int putptr(void *ptr);

int putchar(char c);
int putstr(char *str);
