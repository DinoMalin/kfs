#include "dinoint.h"
#include "dinostring.h"

void *memset(void *pointer, int value, unsigned int size) {
	unsigned int i = 0;
	while (i < size)
		*(unsigned char *)(pointer + i++) = (unsigned char)value;
	return (pointer);
}
