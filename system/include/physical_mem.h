#pragma once
#include "dinoint.h"

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096

#define zone_to_allocate(offset, page, len)                                    \
	((offset * 32 + page - len) * PAGE_SIZE)
#define page_is_free(page) (!(bitmap[page / 32] & (1 << (page % 32))))
#define page(offset, page) (offset * 32 + page)

uint32_t palloc();
void init_bitmap();
