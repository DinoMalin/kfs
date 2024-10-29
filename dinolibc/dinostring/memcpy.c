#include "dinostring.h"

void *memcpy(void *dst, const void *src, unsigned int size) {
	if (dst == src)
		return (dst);
	for (unsigned int i = 0; i < size; i++) {
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	}
	return (dst);
}
