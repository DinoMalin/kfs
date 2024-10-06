#include "dinostring.h"

char *strchr(const char *str, int search) {
	int	i = 0;
	while (str[i]) {
		if (str[i] == (char)search)
			return ((char *)(str + i));
		i++;
	}
	if (search == '\0')
		return ((char *)(str + i));
	return (0);
}
