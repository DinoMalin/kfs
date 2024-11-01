#pragma once
#include "types.h"

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096
#define TABLE_SIZE 4194304

extern void enable_paging();
extern void fill_first_table();
extern u32 page_directory[1024];
extern void *kernel_start;
extern void *kernel_end;

void section(".multiboot.text") init_boot_paging();
