#include <dinoint.h>
#include <physical_mem.h>

// More on bitmap allocator : https://wiki.osdev.org/Page_Frame_Allocation
uint32_t bitmap[NB_PAGES] = {[0 ... NB_PAGES - 1] = 0xffffffff};

void allocate_page(int page) { bitmap[page / 32] |= 1 << (page % 32); }

void allocate_zone(unsigned int addr, unsigned int len) {
	unsigned int last_page = addr + len;

	while (addr + PAGE_SIZE <= last_page) {
		allocate_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

void free_page(int page) {
	bitmap[page / 32] &= ~(1 << (page % 32));
}

void free_zone(unsigned int addr, unsigned int len) {
	unsigned int last_page = addr + len;

	while (addr + PAGE_SIZE <= last_page) {
		free_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

extern void *kernel_start;
extern void *kernel_end;

void alloc_basics() {
	allocate_zone(0, 0x100000);
	allocate_zone((unsigned int)&kernel_start, kernel_len(kernel_start, kernel_end));
}

int get_free_page() {
	int	i = 0;
	int current_len = 0;

	while (i < NB_PAGES) {
		int	j = 0;
		while (j != 32) {
			if (page_is_free(page(i, j))) {
				allocate_page(page(i, j));
				return page(i, j);
			}
			j++;
		}
	}
	return -1;
}

void *palloc() {
	int res = get_free_page();
	if (res == -1)
		return 0;
	return (void *)(res * PAGE_SIZE);
}
