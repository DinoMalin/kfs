#pragma once
#include "dinoint.h"
#include "physical_mem.h"

#define VIDEO_AREA 4000

#define resolve_table(address) (address / 0x400000)
#define resolve_page(address) (address % 0x400000)
#define present(table) (table & 1)
#define kernel_len ((uint32_t) & kernel_end - (uint32_t) & kernel_start)

/* Identity map : mapping a virtual address to the same physical
 * address. Useful for address like the video memory.
 **/
#define IDENTITY_MAP(addr, len) map_zone(addr, addr, len)

extern void enable_paging();

void init_paging();
