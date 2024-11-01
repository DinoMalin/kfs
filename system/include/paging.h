#pragma once
#include "types.h"

// 4 GiB / 4MiB / 32 bits
#define NB_PAGES 32768
#define PAGE_SIZE 4096
#define TABLE_SIZE 0x400000

extern void *kernel_start;
extern void *kernel_end;

void section(".multiboot.text") init_boot_paging();
