#pragma once

struct multiboot_info {
	uint32_t flags;
	uint32_t mmap_len;
	uint32_t mmap_addr;
};

struct mmap_entry {
	uint32_t size;
	uint64_t addr;
	uint64_t len;
	uint32_t type;
};

#define keep_mmap_info(info)                                                   \
	{                                                                          \
		info->mmap_len = (*(uint32_t *)(((char *)info) + 44));                 \
		info->mmap_addr = (*(uint32_t *)(((char *)info) + 48));                \
	}

#define MULTIBOOT_MAGIC 0x2BADB002
#define MULTIBOOT_INFO_MEM_MAP 0x40

extern struct multiboot_info *multiboot;
