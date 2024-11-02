#pragma once

#include "types.h"
#include "virtual_mem.h"

// TABLE_SIZE / sizeof(mem_entry)
#define NULL ((void *)0)

void *vmalloc(u32 size);
void vfree(void *addr);
