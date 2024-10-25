#include "virtual_mem.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));

void init_page_directory() {
	for (int i = 0; i < 1024; i++) {
		page_directory[i] = 0b10; // rw rights
	}
}

int map(uint32_t physical_addr, uint32_t virtual_addr) {
	int table = resolve_page_table(virtual_addr);

	if (!present(page_directory[table_index])) {
		void *page_table = palloc();
		if (!page_table)
			return 0;
		page_directory[table] = page_table | 0b11;
	}

	int page = resolve_page(virtual_addr);
	page_directory[table][page] = physical_addr | 0b11;
	return 1;
}

int map_zone(uint32_t physical_addr, uint32_t virtual_addr, int len) {
	for (int i = 0; i < len; i += PAGE_SIZE) {
		if (!map(physical_addr + i, virtual_addr + i))
			return 0;
	}
	return 1;
}

void init_paging() {
	init_page_directory();
	IDENTITY_MAP(0xb8000, VIDEO_AREA);
	enable_paging();
}

