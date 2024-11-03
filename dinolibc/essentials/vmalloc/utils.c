#include "vmalloc.h"

mem_entry *lstlast(mem_entry *lst) {
	mem_entry *curr = lst;

	while (curr->next) {
		curr = curr->next;
	}
	return curr;
}

u32 get_hole(mem_entry *a, mem_entry *b) {
	void *end_addr = a->addr + a->size;
	if (end_addr >= b->addr)
		return 0;
	return b->addr - end_addr;
}

void *find_hole(u32 size) {
	mem_entry *curr = (void *)heap_descriptor;

	while (curr->next) {
		u32 hole = get_hole(curr, curr->next);
		if (hole >= size)
			return curr->addr + curr->size;
		curr = curr->next;
	}
	return 0;
}

u32 find_free_entry() {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (heap_descriptor[i].addr == 0)
			return i;
	}
	return 0;
}

u32 need_to_allocate(mem_entry *last, u32 size) {
	u32 end_addr = (u32)last->addr + last->size;
	return (PAGE_REFERENCE(end_addr) != PAGE_REFERENCE(end_addr + size));
}

void *allocate_pages(u32 start, u32 size) {
	u32 page = PAGE_REFERENCE(start);
	u32 end = start + size;

	while (page <= end) {
		if (!map_new_page(page))
			return NULL;
		page += PAGE_SIZE;
	}
	return (void *)start;
}

void insert(int entry, void *addr, u32 size) {
	mem_entry *curr = heap_descriptor;

	while (curr->next) {
		if (curr->next->addr > addr)
			break;
		curr = curr->next;
	}

	heap_descriptor[entry].addr = addr;
	heap_descriptor[entry].size = size;
	heap_descriptor[entry].next = curr->next;
	curr->next = heap_descriptor + entry;
}
