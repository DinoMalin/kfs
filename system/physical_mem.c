#include <physical_mem.h>
#include <types.h>

// More on bitmap allocator : https://wiki.osdev.org/Page_Frame_Allocation
uint32_t bitmap[NB_PAGES] = {[0 ... NB_PAGES - 1] = 0};

void pmem_alloc_page(int page) { bitmap[page / 32] |= 1 << (page % 32); }
void pmem_free_page(int page) { bitmap[page / 32] &= ~(1 << (page % 32)); }

void pmem_alloc_zone(uint32_t addr, uint32_t len) {
	uint32_t last_page = addr + len;

	while (addr + PAGE_SIZE <= last_page) {
		pmem_alloc_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

void pmem_free_zone(u32 addr, u32 len) {
	u32 last_page = addr + len;

	while (addr + PAGE_SIZE <= last_page) {
		pmem_free_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

extern void *kernel_start;
extern void *kernel_end;

int get_free_page() {
	int i = 0;
	int current_len = 0;

	while (i < NB_PAGES) {
		int j = 0;
		while (j != 32) {
			if (page_is_free(page(i, j))) {
				pmem_alloc_page(page(i, j));
				return page(i, j);
			}
			j++;
		}
		i++;
	}
	return 0;
}

uint32_t palloc() {
	int res = get_free_page();
	return res * PAGE_SIZE;
}

void init_pmem() {
	struct mmap_entry *mmap = (struct mmap_entry *)multiboot->mmap_addr;
	int len = multiboot->mmap_len / sizeof(struct mmap_entry);
	for (uint32_t i = 0; i < len; i++) {
		pmem_alloc_zone(mmap[i].addr, mmap[i].len);
	}
	pmem_alloc_zone(0, (uint32_t)&kernel_end);
}
