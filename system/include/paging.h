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
#define KERNEL_HEAP_DESCRIPTOR 0xc1c00000

#define KERNEL_HEAP 0xc2000000
#define END_KERNEL_HEAP 0xca000000

#define HEAP_HEAP 0xa7400000
#define END_USER_HEAP 0xaf400000

#define SIZE_HEAP 0x8000000

extern void *kernel_start;
extern void *kernel_end;

void section(".multiboot.text") init_boot_paging();
