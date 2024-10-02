#include "dinostring.h"

int	atoi(const char *str) {
	int	i = 0;
	int	minus = 1;
	int	result = 0;

	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ') {
		i++;
	}
	if (str[i] == '+' || str[i] == '-') {
		if (str[i++] == '-')
			minus = -1;
	}
	while (isdigit(str[i])) {
		result *= 10;
		result += str[i++] - '0';
	}
	return (result * minus);
}
