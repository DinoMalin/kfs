#include "virtual_mem.h"

u32 *v_page_directory;

int map(u32 physical_addr, u32 virtual_addr) {
	u32 table_index = table_index(virtual_addr);
	u32 *page_table = v_page_directory + table_index;

	if (!PRESENT(*page_table)) {
		u32 new_table = palloc();
		if (!new_table)
			return 0;

		*page_table = MAPPED(new_table);
		CLEAR_TABLE(table_index);
	}

	u32 page_index = page_index(virtual_addr);
	u32 *page = (void *)INDEX_TO_PAGE(table_index, page_index);

	*page = MAPPED(physical_addr);
	return 1;
}

int map_zone(u32 physical_addr, u32 virtual_addr, u32 len) {
	for (u32 i = 0; i <= len; i += PAGE_SIZE) {
		if (!map(physical_addr + i, virtual_addr + i))
			return 0;
	}
	return 1;
}

void *map_new_page(u32 virtual_addr) {
	u32 p_new_page = palloc();
	if (!p_new_page)
		return 0;
	if (!map(p_new_page, virtual_addr))
		return 0;
	return (void *)virtual_addr;
}

int map_table(u32 index) {
	u32 addr = INDEX_TO_ADDR(index);
	for (u32 i = 0; i < 1024; i++) {
		if (!map_new_page(addr + (i * PAGE_SIZE))) {
			printk("couldnt map");
			return 0;
		}
	}
	return 1;
}

void init_heap() {
	map_new_page(HEAP);

	mem_entry *heap_descriptor = (void *)HEAP_DESCRIPTOR;
	heap_descriptor->addr = (void *)HEAP;
	heap_descriptor->size = 0;
	heap_descriptor->next = 0;
}

void init_pages() {
	v_page_directory = (void *)PAGE_DIRECTORY_PTR_ADDR;
	map_table(HEAP_DESCRIPTOR_INDEX);
	bzero((void *)HEAP_DESCRIPTOR, TABLE_SIZE);
	init_heap();
}
