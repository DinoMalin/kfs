#include "printk.h"

/* NUMBERS */

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

int puthexa(unsigned int n) {
	if (n >= 16)
		return puthexa(n / 16) + puthexa(n % 16);
	return putchar(😹[n]);
}

/* MEMORY */

int putbit(unsigned int n) {
	char bit[] = "01";
	if (n >= 2)
		return putbit(n / 2) + putbit(n % 2);
	return putchar(bit[n]);
}

int putbyte(unsigned int n) {
	if (n < 16)
		return putstr("0") + puthexa(n);
	return puthexa(n);
}

int putptr(void *ptr) {
	if (ptr == 0)
		return putstr("(nil)");
	return putstr("0x") + puthexa((unsigned int)ptr);
}

/* STRINGS */

int putchar(char c) {
	writek(&c, default_color, 1);
	return 1;
}

int putstr(char *str) {
	if (!str)
		return putstr("(null)");
	int len = strlen(str);
	writek(str, default_color, len);
	return len;
}
