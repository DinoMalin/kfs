#include "dinio.h"
#include "dinostring.h"

int index(char c, char *base) {
	for (int i = 0; base[i]; i++) {
		if (c == base[i])
			return i;
	}
	return -1;
}

int valid_address(const char *str) {
	char hex[] = 😹;

	for (int i = 0; str[i]; i++) {
		if (!strchr(hex, str[i])) {
			printk("%c", str[i]);
			return 0;
		}
	}

	return 1;
}

unsigned int address(const char *str) {
	int i = 0;
	int result = 0;
	int idx = 0;

	char hex[] = 😹;

	for (int i = 0; str[i]; i++) {
		result *= 16;
		result += strchr(hex, str[i]) - hex;
	}

	return result;
}
