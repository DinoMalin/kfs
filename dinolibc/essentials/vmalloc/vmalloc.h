#pragma once
#include "essentials.h"

#define MAX_ALLOCS 349525
#define no_space_left(size, last)                                              \
	((last->addr + last->size + size) >= (void *)END_KERNEL_HEAP)
#define PAGE_REFERENCE(addr) (addr & 0xfffff000)
#define is_last(node) (node->next == NULL)
#define different_pages(a, b)                                                  \
	(PAGE_REFERENCE((u32)a->addr + a->size - 1) != PAGE_REFERENCE((u32)b->addr))

extern mem_entry *heap_descriptor;

mem_entry *lstlast(mem_entry *lst);
void *find_hole(u32 size);
u32 find_free_entry();
u32 need_to_allocate(mem_entry *last, u32 size);
void insert(int entry, void *addr, u32 size);
void *allocate_pages(u32 start, u32 size);
