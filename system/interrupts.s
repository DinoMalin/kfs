; GDT load function
%macro isr 1
global isr%1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro irq 1
global irq%1
irq%1:
    cli
    push byte 0
    push byte %1 + 32
    jmp irq_common_stub
%endmacro

%macro int_func 1
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

    mov eax, %1
    call eax

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8

    iret
%endmacro

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

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

extern fault_handler
isr_common_stub:
	int_func fault_handler

extern irq_handler
irq_common_stub:
	int_func irq_handler

extern syscall_handler
global software_isr
software_isr:
    cli

    push eax
    push byte -128 ; 0x80 but it generates a warning so here it is signed
	int_func syscall_handler	

global syscall
syscall:
	push ebx
	int 0x80
	pop ebx
	ret


; ISRs
isr 0 ; Division by 0
isr 1 ; Debug
isr 2 ; Non Maskable Interrupt
isr 3 ; Breakpoint
isr 4 ; Detected Overflow
isr 5 ; Out of Bounds
isr 6 ; Invalid opcode
isr 7 ; No coprocessor
isr 8 ; Double fault
isr 9 ; Coprocessor segment overrun
isr 10 ; Bad TSS
isr 11 ; Segment not present
isr 12 ; Stack fault
isr 13 ; General protection fault
isr 14 ; Page fault
isr 15 ; Unknown interrupt
isr 16 ; Coprocessor fault
isr 17 ; Alignment check
isr 18 ; Machine check
; 19 -> 31 : Reserved Exceptions
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

; Interrupt Requests
irq 0 ; System clock
irq 1 ; Keyboard

