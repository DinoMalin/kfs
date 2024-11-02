#pragma once

#include "io.h"
#include "paging.h"
#include "physical_mem.h"
#include "string.h"
#include "types.h"

#define VIDEO_AREA 4000

#define PAGE_DIRECTORY_PTR_ADDR 0xfffff000
#define PAGE_DIRECTORY_ADDR 0xffc00000

#define table_index(addr) (addr / TABLE_SIZE)
#define page_index(addr) ((addr % TABLE_SIZE) / PAGE_SIZE)
#define CLEAR_TABLE(index) bzero((void *)INDEX_TO_TABLE(index), PAGE_SIZE)

#define PRESENT(table) (table & 1)
#define MAPPED(addr) ((addr & 0xfffff000) | 0b11)

#define INDEX_TO_ADDR(index) (index * TABLE_SIZE)
#define INDEX_TO_TABLE(index) ((u32)PAGE_DIRECTORY_ADDR + (index * PAGE_SIZE))
#define INDEX_TO_PAGE(table_index, page_index) (INDEX_TO_TABLE(table_index) + (page_index * 4))

#define ALLOC_DIRECTORY_INDEX 775

void *map_new_page(u32 virtual_addr);
void init_pages();
