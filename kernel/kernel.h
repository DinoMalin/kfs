#pragma once

#include "dinio.h"
#include "dinostring.h"

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "shell.h"

#include "virtual_mem.h"
#include "physical_mem.h"

struct multiboot_info {
    uint32_t flags;
    uint32_t mmap_length;
    uint32_t mmap_addr;
};

#define kernel_panic(msg) { \
	printk("kernel lost in the sauce : %s", msg); \
	exit = 1; \
}

#define keep_mmap_info(info) { \
	info->mmap_length = (*(uint32_t *)(((char *)info) + 44)); \
	info->mmap_addr = (*(uint32_t *)(((char *)info) + 48)); \
}

#define MULTIBOOT_MAGIC 0x2BADB002
#define MULTIBOOT_INFO_MEM_MAP 0x40

