#pragma once

#include "types.h"
#include "virtual_mem.h"

// TABLE_SIZE / sizeof(mem_entry)
#define MAX_ALLOCS 349525
#define NULL ((void *)0)

#define PAGE_REFERENCE(addr) (addr & 0xfffff000)
#define no_space_left(size, last) ((last->addr + last->size + size) >= (void *)END_HEAP)

void *vmalloc(u32 size);
