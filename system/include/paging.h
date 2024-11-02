#pragma once
#include "types.h"

typedef struct mem_entry {
	void *addr;
	u32 size;
	struct mem_entry *next;
} mem_entry;

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096
#define TABLE_SIZE 0x400000
#define HEAP_DESCRIPTOR 0xc1c00000
#define HEAP 0xc2000000
#define END_HEAP 0xc9c00000

extern void *kernel_start;
extern void *kernel_end;

void section(".multiboot.text") init_boot_paging();
