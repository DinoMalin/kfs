#include "io.h"
#include "string.h"
#include "types.h"

void *memset(void *pointer, int value, u32 size) {
	u32 i = 0;
	while (i < size) {
		*(u8 *)(pointer + i++) = (u8)value;
	}
	return (pointer);
}
