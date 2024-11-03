#pragma once

#include "types.h"
#include "virtual_mem.h"

// TABLE_SIZE / sizeof(mem_entry)
#define NULL ((void *)0)

void *vmalloc(u32 size);
void vfree(void *addr);
int vsize(void *addr);

typedef enum {
	NO_EXIT,
	EXIT,
} importance;
extern int end;

#define kernel_panic(msg, must_exit)                                           \
	{                                                                          \
		printk("kernel lost in the sauce: %s", msg);                           \
		if (must_exit)                                                         \
			end = 2;                                                           \
	}
