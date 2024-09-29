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
	cli
.halt:
	hlt
	jmp .halt

; GDT load function
global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret

; IDT load function
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

; ISR Common stub
extern fault_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; Exporting ISR
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; ISR
; 0: Divison By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

; 3: Breakpoint Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

; 4: Into Detected Overflow Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

; 7: No Coprocessor Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

; 8: Double Fault Exception
isr8:
    cli
    push byte 8
    jmp isr_common_stub

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception
isr10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception
isr11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception
isr12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception
isr13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception
isr14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Unknown Interrupt Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Coprocessor Fault Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; 19: Reserved Exceptions
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

; 20: Reserved Exceptions
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

; 21: Reserved Exceptions
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

; 22: Reserved Exceptions
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

; 23: Reserved Exceptions
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

; 24: Reserved Exceptions
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

; 25: Reserved Exceptions
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

; 26: Reserved Exceptions
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

; 27: Reserved Exceptions
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

; 28: Reserved Exceptions
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

; 29: Reserved Exceptions
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

; 30: Reserved Exceptions
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

; 31: Reserved Exceptions
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

