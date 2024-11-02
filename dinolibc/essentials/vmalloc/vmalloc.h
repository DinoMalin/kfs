#pragma once
#include "essentials.h"

#define MAX_ALLOCS 349525
#define no_space_left(size, last)                                              \
	((last->addr + last->size + size) >= (void *)END_HEAP)
#define PAGE_REFERENCE(addr) (addr & 0xfffff000)

extern mem_entry *heap_descriptor;

mem_entry *lstlast(mem_entry *lst);
void *find_hole(u32 size);
u32 find_free_entry();
u32 need_to_allocate(u32 size);
void insert(int entry, void *addr, u32 size);
