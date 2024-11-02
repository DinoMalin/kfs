#include <physical_mem.h>
#include <types.h>

// More on bitmap allocator : https://wiki.osdev.org/Page_Frame_Allocation
u32 bitmap[NB_PAGES] = {[0 ... NB_PAGES - 1] = 0xffffffff};

void pmem_alloc_page(int page) { bitmap[page / 32] |= 1 << (page % 32); }
void pmem_free_page(int page) { bitmap[page / 32] &= ~(1 << (page % 32)); }

void pmem_alloc_zone(u32 addr, u32 len) {
	u32 last_page = addr + len;

	while (addr <= last_page) {
		if (addr == 0)
			pmem_alloc_page(0);
		else
			pmem_alloc_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

void pmem_free_zone(u32 addr, u32 len) {
	u32 last_page = addr + len;

	while (addr <= last_page) {
		if (addr == 0)
			pmem_free_page(0);
		else
			pmem_free_page(addr / PAGE_SIZE);
		addr += PAGE_SIZE;
	}
}

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

u32 palloc() {
	int res = get_free_page();
	return res * PAGE_SIZE;
}

void init_pmem() {
	mmap_entry *mmap = (mmap_entry *)multiboot->mmap_addr;
	int len = multiboot->mmap_len / sizeof(mmap_entry);
	for (u32 i = 0; i < len; i++) {
		if (available(mmap[i])) {
			pmem_free_zone(mmap[i].addr, mmap[i].len);
		}
	}
	pmem_alloc_zone(0, TABLE_SIZE);
}
