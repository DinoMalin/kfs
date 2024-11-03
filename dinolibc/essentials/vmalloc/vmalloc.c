#include "vmalloc.h"

mem_entry *heap_descriptor = (mem_entry *)KERNEL_HEAP_DESCRIPTOR;
int last = 0;

void *vmalloc(u32 size) {
	if (!size || size > SIZE_HEAP)
		return NULL;

	int entry = find_free_entry();
	if (!entry)
		return NULL;

	mem_entry *target = find_hole(size);
	void *addr;
	if (!target) {
		target = heap_descriptor + last;
		if (last == 0)
			addr = heap_descriptor->addr;
		else
			addr = (void *)ALIGN((u32)target->addr + target->size);

		if (need_to_allocate(target, size)) {
			if (no_space_left(size, target))
				return NULL;

			if (!allocate_pages((u32)addr, size))
				return NULL;
		}
		last = entry;
	} else {
		addr = (void *)ALIGN((u32)target->addr + target->size);
	}

	insert(entry, target, addr, size);
	return addr;
}

void vfree(void *addr) {
	mem_entry *curr = heap_descriptor;

	while (curr->next) {
		if (curr->next->addr == addr) {
			if (is_last(curr->next))
				last = curr - heap_descriptor;
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

void valgrind() {
	mem_entry *curr = heap_descriptor + 1;
	u32 bytes = 0;
	int allocs = 0;
	while (curr) {
		display_node_info(curr);
		bytes += curr->size;
		allocs++;
		curr = curr->next;
	}

	printk("\nHEAP SUMMARY:");
	printk("    in use: %u bytes", bytes);
	printk("  total heap usage: %d allocs, %u bytes allocated", allocs, bytes);
}
