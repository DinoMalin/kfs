#pragma once

#include "types.h"
#include "virtual_mem.h"

// TABLE_SIZE / sizeof(mem_entry)
#define NULL ((void *)0)

void *vmalloc(u32 size);
void vfree(void *addr);
int vsize(void *addr);
void valgrind();

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

#define fkernel_panic(must_exit, msg, ...)                                     \
	{                                                                          \
		printk("kernel lost in the sauce: %nonl");                             \
		printk(msg, __VA_ARGS__);                                              \
		if (must_exit)                                                         \
			end = 2;                                                           \
	}
