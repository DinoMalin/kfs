bits 32

section .multiboot.data

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
section .multiboot.text
PAGE_SIZE equ(4096)
extern page_directory
extern first_table

%macro map 2
	mov dword[%1], %2
	or dword[%1], 3	
%endmacro

_start:
	map page_directory + 768 * 4, first_table ; 0xC0000000/PAGE_SIZE/NB_ENTRIES = 768
	map page_directory, first_table

	xor edi, edi ; counter
	mov esi, first_table ; pointer toward table

.fill_table:
	map esi, edi

	add edi, PAGE_SIZE
	add esi, 4

	cmp edi, 0x400000
	jge .done
	jmp .fill_table

.done:
	mov esi, page_directory
	mov cr3, esi
	 
	mov esi, cr0
	or esi, 0x80000000
	mov cr0, esi
	call kernel

section .text
kernel:
global _start
extern ksetup
extern kmain

	mov esp, stack_top

	push ebx
	push eax

	call ksetup
	call kmain
	cmp eax, 1
	je .exit
	cli
.halt:
	hlt
	jmp .halt
.exit:

