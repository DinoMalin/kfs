#include "virtual_mem.h"

uint32_t page_directory[1024] aligned(4096);

int map(uint32_t physical_addr, uint32_t virtual_addr) {
	int table_index = table_index(virtual_addr);
	uint32_t *page_table = page_directory + table_index;

	if (!present(*page_table)) {
		uint32_t new_table = palloc();
		if (!new_table)
			return 0;

		bzero((void *)new_table, PAGE_SIZE);

		*page_table |= 0b01;
		*page_table |= 0b10;
		*page_table |= new_table & 0xfffff000;
	}

	int page_index = page_index(virtual_addr);
	uint32_t *page = (void *)((*page_table & 0xfffff000) + (page_index * 4));

	*page = 0b01;
	*page |= 0b10;
	*page |= physical_addr & 0xfffff000;

	return 1;
}

int map_zone(uint32_t physical_addr, uint32_t virtual_addr, uint32_t len) {
	for (uint32_t i = 0; i <= len; i += PAGE_SIZE) {
		if (!map(physical_addr + i, virtual_addr + i))
			return 0;
	}
	return 1;
}

void init_paging() {
	bzero((void *)page_directory, PAGE_SIZE);

	if (!IDENTITY_MAP(0, KERNEL_AREA))
		printk("Failed to map kernel");
	if (!IDENTITY_MAP(0xb8000, VIDEO_AREA))
		printk("Failed to map video memory");

	enable_paging();
}
