#pragma once

#include "io.h"
#include "multiboot.h"
#include "types.h"
#include "paging.h"

#define zone_to_allocate(offset, page, len)                                    \
	((offset * 32 + page - len) * PAGE_SIZE)
#define page_is_free(page) (!(bitmap[page / 32] & (1 << (page % 32))))
#define page(offset, page) (offset * 32 + page)
#define available(entry) (entry.type == 1)

u32 palloc();
void pmem_alloc_zone(u32 addr, u32 len);
void init_pmem();

