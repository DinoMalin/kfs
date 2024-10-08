bits 32
section .text

; Multiboot macros
MULTIBOOT_PAGE_ALIGN	equ(1 << 0)
MULTIBOOT_MEMORY_INFO	equ(1 << 1)
MULTIBOOT_AOUT_KLUDGE	equ(1 << 16)
MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM		equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

; Multiboot header
align 4
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_CHECKSUM

; Stack init
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

; Kernel entrypoint
section .text
global _start
extern kmain

_start:
	mov esp, stack_top
	call kmain
	cmp eax, 1
	je .exit
	cli
.halt:
	hlt
	jmp .halt
.exit:

