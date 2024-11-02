#pragma once

#include "io.h"
#include "string.h"
#include "essentials.h"

#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "shell.h"

#include "multiboot.h"
#include "physical_mem.h"
#include "virtual_mem.h"

#define kernel_panic(msg)                                                      \
	{                                                                          \
		printk("kernel lost in the sauce : %s", msg);                          \
		exit = 1;                                                              \
	}
