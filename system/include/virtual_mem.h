#pragma once

#include "io.h"
#include "physical_mem.h"
#include "string.h"
#include "types.h"
#include "paging.h"

#define VIDEO_AREA 4000
#define KERNEL_AREA 0x400000
#define KERNEL_VIRTUAL_ADDR 0xC0000000

#define table_index(addr) (addr / TABLE_SIZE)
#define page_index(addr) ((addr % TABLE_SIZE) / PAGE_SIZE)
#define present(table) (table & 1)
#define kernel_len ((u32) & kernel_end - (u32) & kernel_start)

/* Identity map : mapping a virtual address to the same physical
 * address. Useful for address like the video memory.
 **/
#define IDENTITY_MAP(addr, len) map_zone(addr, addr, len)

void init_paging();
