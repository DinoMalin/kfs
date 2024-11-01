#pragma once
#include "types.h"

typedef struct multiboot_info {
	u32 flags;
	u32 mmap_len;
	u32 mmap_addr;
} multiboot_info;

typedef struct mmap_entry {
	u32 size;
	u64 addr;
	u64 len;
	u32 type;
} mmap_entry;

#define keep_mmap_info(info)                                                   \
	{                                                                          \
		info->mmap_len = (*(u32 *)(((char *)info) + 44));                      \
		info->mmap_addr = (*(u32 *)(((char *)info) + 48));                     \
	}

#define MULTIBOOT_MAGIC 0x2BADB002
#define MULTIBOOT_INFO_MEM_MAP 0x40

extern struct multiboot_info *multiboot;
