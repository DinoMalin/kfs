#include "essentials.h"

mem_entry *alloc_dir = (mem_entry *)HEAP_DESCRIPTOR;

mem_entry *lstlast(mem_entry *lst) {
	mem_entry *curr = lst;

	while (curr->next) {
		curr = curr->next;
	}
	return curr;
}

void *find_hole(u32 size) {
	mem_entry *curr = (void *)alloc_dir;
	
	while (curr->next) {
		u32 hole = ((curr->addr + curr->size) - curr->next);
		if (hole >= size)
			return curr->addr + curr->size;
		curr = curr->next;
	}
	return 0;
}

u32 find_free_entry() {
	for (int i = 0; i < MAX_ALLOCS; i++) {
		if (alloc_dir[i].addr == 0)
			return i;
	}
	return 0;
}

u32 need_to_allocate(u32 size) {
	mem_entry *last = lstlast(alloc_dir);
	u32 end_addr = (u32)last->addr + last->size;
	return (PAGE_REFERENCE(end_addr) != PAGE_REFERENCE(end_addr + size));
}

void insert(int entry, void *addr, u32 size) {
	mem_entry *curr = alloc_dir;

	while (curr->next) {
		if (curr->next->addr > addr)
			break;
		curr = curr->next;
	}

	alloc_dir[entry].addr = addr;
	alloc_dir[entry].next = curr->next;
	curr->next = alloc_dir + entry;
}

void *kmalloc(u32 size) {
	int entry = find_free_entry();
	if (!entry)
		return NULL;

	void *addr = find_hole(size);
	if (!addr) {
		mem_entry *last = lstlast(alloc_dir);
		if (need_to_allocate(size)) {
			if (no_space_left(size, last))
				return NULL;

			u32 new_page = PAGE_REFERENCE((u32)last->addr + last->size + size);
			if (!map_new_page(new_page))
				return NULL;
		}
	
		addr = last->addr + last->size;
	}

	printk("here");
	insert(entry, addr, size);
	return addr;
}

