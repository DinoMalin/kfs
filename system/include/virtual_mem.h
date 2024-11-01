#pragma once

#include "io.h"
#include "paging.h"
#include "physical_mem.h"
#include "string.h"
#include "types.h"

#define VIDEO_AREA 4000
#define PAGE_DIRECTORY_ADDR 0xfffff000

#define table_index(addr) (addr / TABLE_SIZE)
#define page_index(addr) ((addr % TABLE_SIZE) / PAGE_SIZE)
#define present(table) (table & 1)
#define kernel_len ((u32) & kernel_end - (u32) & kernel_start)

#define IDENTITY_MAP(addr, len) map_zone(addr, addr, len)
#define MAPPED(addr) ((physical_addr & 0xfffff000) | 0b11)

