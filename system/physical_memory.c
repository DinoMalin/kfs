#include <dinoint.h>

unsigned int bitmap[NB_PAGES] = {[0 ... NB_PAGES - 1] = 0xffffffff};

void allocate_page(int page) { bitmap[page / 32] |= 1 << (page % 32); }

void allocate_zone(unsigned int addr, unsigned int len) {
	unsigned int last_page = addr + len;

	while (addr + PAGE_SIZE <= last_page) {
		allocate_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

int page_is_allocated(int page) {
	return (bitmap[page / 32] & (1 << (page % 32)));
}

extern void *kernel_start;
extern void *kernel_end;

void alloc_basics() {
	allocate_zone(0, 0x100000);
	allocate_zone(kernel_start, kernel_end - kernel_start);
}
