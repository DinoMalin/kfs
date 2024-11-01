#include "printk.h"

int no_newline = 0;

int basic(char *str, int *index) {
	int i = 0;
	while (str[i] && str[i] != '%')
		i++;
	writek(str, default_color, i);
	*index += i;
	return i;
}

int format(char *str, int *index, va_list *variadic) {
	FORMAT("%d", putnbr(va_arg(*variadic, int)));
	FORMAT("%c", putchar(va_arg(*variadic, char)));
	FORMAT("%%", putstr("%"));
	FORMAT("%p", putptr(va_arg(*variadic, void *)));
	FORMAT("%s", putstr(va_arg(*variadic, char *)));
	FORMAT("%u", putunbr(va_arg(*variadic, unsigned int)));
	FORMAT("%x", puthexa(va_arg(*variadic, unsigned int)));
	FORMAT("%byte", putbyte(va_arg(*variadic, unsigned char)));
	FORMAT("%bit", putbit(va_arg(*variadic, unsigned int)));
	FORMAT("%nonl", ((no_newline = 1), 0));

	// Should not be used with another arg,
	// my variadic doesn't handle 64 bits well
	FORMAT("%lu", putlu(va_arg(*variadic, unsigned long long)));

	return 0;
}

int printk(char *str, ...) {
	int i = 0;
	int count = 0;

	char *last_basic = str;
	int size_basic = 0;

	va_list variadic;
	va_start(variadic, str);

	if (video_memory != START_VMEM && !no_newline)
		writek("\n", default_color, 1);

	no_newline = 0;
	while (str[i]) {
		count += basic(str + i, &i);
		count += format(str + i, &i, &variadic);
	}
	va_end(variadic);
	return count;
}
