#include "virtual_mem.h"

u32 *page_directory = (void *)PAGE_DIRECTORY_ADDR;

int map(u32 physical_addr, u32 virtual_addr) {
	int table_index = table_index(virtual_addr);
	u32 *page_table = page_directory + table_index;

	if (!present(*page_table)) {
		u32 new_table = palloc();
		if (!new_table)
			return 0;
		bzero((void *)new_table, PAGE_SIZE);
		*page_table = MAPPED(new_table);
	}

	int page_index = page_index(virtual_addr);
	u32 *page = (void *)((*page_table & 0xfffff000) + (page_index * 4));

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
