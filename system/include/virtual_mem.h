#pragma once

#include "dinio.h"
#include "dinoint.h"
#include "dinostring.h"
#include "physical_mem.h"

#define VIDEO_AREA 4000
#define KERNEL_AREA 0x400000
#define aligned(x) __attribute__((aligned(x)))

#define table_index(addr) (addr / TABLE_SIZE)
#define page_index(addr) ((addr % TABLE_SIZE) / PAGE_SIZE)
#define present(table) (table & 1)
#define kernel_len ((uint32_t) & kernel_end - (uint32_t) & kernel_start)

/* Identity map : mapping a virtual address to the same physical
 * address. Useful for address like the video memory.
 **/
#define IDENTITY_MAP(addr, len) map_zone(addr, addr, len)

extern void enable_paging();
extern void *kernel_start;
extern void *kernel_end;

void init_paging();
