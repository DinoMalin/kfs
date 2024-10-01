#include "dinio.h"
#include "dinostring.h"
#include "dinoarg.h"

int  no_newline = 0;

int putstr(char *str) {
    if (!str)
	return putstr("(null)");
    int len = strlen(str);
    writek(str, DEFAULT, len);
    return len;
}

int putchar(char c) { 
	writek(&c, DEFAULT, 1);
	return 1;
}

int puthexa(unsigned int n) {
    char    hexa[16] = "0123456789abcdef";
    if (n >= 16)
	return puthexa(n / 16) + puthexa(n % 16);
    return putchar(hexa[n]);
}

int putptr(void *ptr) {
    if (ptr == 0)
	return putstr("(nil)");
    return putstr("0x") + puthexa((unsigned int)ptr);
}

int putnbr(int n) {
    if (n <= -10)
	return putchar('-') + putnbr(-(n / 10)) + putnbr(-(n % 10));
    else if (n < 0)
	return putchar('-') + putnbr(-n);
    else if (n >= 10)
	return putnbr(n / 10) + putnbr(n % 10);
    else if (n < 10)
	return putchar(n + '0');
    return 0;
}

int putunbr(unsigned int n) {
    if (n >= 10)
	return putnbr(n / 10) + putnbr(n % 10);
    return putchar(n + '0');
}

int basic(char *str, int *index) {
    int i = 0;
    while (str[i] && str[i] != '%')
       i++;
    writek(str, DEFAULT, i);
    *index += i;
    return i;
}

int putbyte(unsigned int n) {
    if (n < 16)
	return putstr("0") + puthexa(n);
    return puthexa(n);
}

int format(char *str, int *index, va_list *variadic) {
    if (!strncmp("%d", str, 2)) {
        *index += 2;
        return putnbr(va_arg(*variadic, int));
    } else if (!strncmp("%u", str, 2)) {
        *index += 2;
        return putunbr(va_arg(*variadic, unsigned int));
    } else if (!strncmp("%x", str, 2)) {
        *index += 2;
        return puthexa(va_arg(*variadic, unsigned int));
    } else if (!strncmp("%byte", str, 5)) {
        *index += 5;
        return putbyte(va_arg(*variadic, unsigned char));
    } else if (!strncmp("%p", str, 2)) {
        *index += 2;
        return putptr(va_arg(*variadic, void *));
    } else if (!strncmp("%s", str, 2)) {
        *index += 2;
        return putstr(va_arg(*variadic, char *));
    } else if (!strncmp("%c", str, 2)) {
	*index += 2;
	return putchar(va_arg(*variadic, char));
    } else if (!strncmp("%%", str, 2)) {
        *index += 2;
        return putstr("%");
    } else if (!strncmp("%nonl", str, 5)) {
        *index += 5;
	no_newline = 1;
	return 0;
    }
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
	writek("\n", DEFAULT, 1);

    no_newline = 0;
    while (str[i])
    {
        count += basic(str + i, &i);
        count += format(str + i, &i,  &variadic);
    }

    va_end(variadic);
    return count;
}
