#pragma once

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096

#define kernel_len(start, end)				((unsigned int)&end - (unsigned int)&start)
#define zone_to_allocate(offset, page, len)	((offset * 32 + page - len) * PAGE_SIZE)
#define page_is_free(page)					(!(bitmap[page / 32] & (1 << (page % 32))))
#define page(offset, page)					(offset * 32 + page)

void alloc_basics();
