#pragma once

#include "io.h"
#include "multiboot.h"
#include "types.h"

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096
#define TABLE_SIZE 4194304

#define zone_to_allocate(offset, page, len)                                    \
	((offset * 32 + page - len) * PAGE_SIZE)
#define page_is_free(page) (!(bitmap[page / 32] & (1 << (page % 32))))
#define page(offset, page) (offset * 32 + page)
#define available(entry) (entry.type == 1)

u32 palloc();
void pmem_alloc_zone(u32 addr, u32 len);
void init_pmem();
