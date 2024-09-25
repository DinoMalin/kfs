#include "dinio.h"
#include "dinostring.h"
#include "dinoarg.h"

int	putnbr(int n) {
	if (n <= -10) {
		writek("-", DEFAULT, 1);
		return (1 + putnbr(-(n / 10)) + putnbr(-(n % 10)));
	}
	else if (n < 0) {
		writek("-", DEFAULT, 1);
		return (1 + putnbr(-n));
	}
	else if (n >= 10)
		return (putnbr(n / 10) + putnbr(n % 10));
	else if (n < 10) {
        char print = n + '0';
		writek(&print, DEFAULT, 1);
		return (1);
	}
	return (0);
}

int putstr(char *str) {
    if (!str)
	return putstr("(null)");
    int len = strlen(str);
    writek(str, DEFAULT, len);
    return len;
}

int basic(char *str, int *index) {
    int i = 0;
    while (str[i] && str[i] != '%')
       i++;
    writek(str, DEFAULT, i);
    *index += i;
    return i;
}

int format(char *str, int *index, va_list *variadic) {
    if (!strncmp("%d", str, 2)) {
        *index += 2;
        return putnbr(va_arg(*variadic, int));
    } else if (!strncmp("%s", str, 2)) {
        *index += 2;
        return putstr(va_arg(*variadic, char *));
    } else if (!strncmp("%c", str, 2)) {
	*index += 2;
	writek(&va_arg(*variadic, char), DEFAULT, 1);
	return 1;
    } else if (!strncmp("%%", str, 2)) {
        *index += 2;
        return putstr("%");
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

    if (last_written_addr != video_memory)
	writek("\n", DEFAULT, 1);

    while (str[i])
    {
        count += basic(str + i, &i);
        count += format(str + i, &i,  &variadic);
    }

    va_end(variadic);
    return count;
}
