#include "dinostring.h"

int	strncmp(char *str1, char *str2, int size) {
	int	i;

	i = 0;
	while (str1[i] == str2[i] && i < size && str1[i] && str2[i])
		i++;
	if (i == size)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
