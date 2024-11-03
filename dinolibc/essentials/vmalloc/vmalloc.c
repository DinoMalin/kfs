#include "vmalloc.h"

mem_entry *heap_descriptor = (mem_entry *)KERNEL_HEAP_DESCRIPTOR;

void *vmalloc(u32 size) {
	if (!size)
		return NULL;

	int entry = find_free_entry();
	if (!entry)
		return NULL;

	void *addr = find_hole(size);
	if (!addr) {
		mem_entry *last = lstlast(heap_descriptor);
		if (need_to_allocate(size)) {
			if (no_space_left(size, last))
				return NULL;

			u32 new_page = PAGE_REFERENCE((u32)last->addr + last->size + size);
			if (!map_new_page(new_page))
				return NULL;
		}

		addr = last->addr + last->size;
	}

	insert(entry, addr, size);
	return addr;
}

void vfree(void *addr) {
	mem_entry *curr = heap_descriptor;

	while (curr->next) {
		if (curr->next->addr == addr) {
			if (is_last(curr->next) && different_pages(curr, curr->next))
				unmap_page((u32)curr->next->addr);
			curr->next->addr = NULL;
			curr->next = curr->next->next;
			return;
		}
		curr = curr->next;
	}
}

int vsize(void *addr) {
	mem_entry *curr = heap_descriptor + 1;

	while (curr) {
		if (curr->addr == addr)
			return curr->size;
		curr = curr->next;
	}
	return 0;
}
