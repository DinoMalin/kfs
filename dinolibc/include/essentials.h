#pragma once

#include "types.h"
#include "virtual_mem.h"

typedef struct mem_entry {
	void *addr;
	u32 size;
	struct mem_entry *next;
} mem_entry;

// TABLE_SIZE / sizeof(mem_entry)
#define MAX_ALLOCS 349525
#define ALLOC_START 0xc2000000

#define NULL ((void *)0)

#define PAGE_REFERENCE(addr) (addr & 0xfffff000)

void *kmalloc(u32 size);
