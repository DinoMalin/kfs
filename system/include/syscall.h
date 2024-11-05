#pragma once

#include "idt.h"
#include "io.h"

#define CODE(regs) *(u32 *)(regs->esp + 28)
#define SYSCALL(code, nb)                                                      \
	{                                                                          \
		if (code == nb) {                                                      \
			syscall_##nb();                                                    \
			return;                                                            \
		}                                                                      \
	}
