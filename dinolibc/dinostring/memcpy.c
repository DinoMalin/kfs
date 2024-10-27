#include "dinostring.h"

void	*ft_memcpy(void *dst, const void *src, size_t size) {
	if (dst == src)
		return (dst);
	for (size_t i = 0; i < size; i++) {
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	}
	return (dst);
}
