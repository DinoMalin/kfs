; GDT load function
%macro isr 1
isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro irq 1
irq%1:
    cli
    push byte 0
    push byte %1 + 32
    jmp irq_common_stub
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

; IRQ Common stub
extern irq_handler
irq_common_stub:
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
    mov eax, irq_handler
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

; Exporting ISR
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; ISR
; 0: Divison By Zero Exception
isr 0
; 1: Debug Exception
isr 1
; 2: Non Maskable Interrupt Exception
isr 2
; 3: Breakpoint Exception
isr 3
; 4: Into Detected Overflow Exception
isr 4
; 5: Out of Bounds Exception
isr 5
; 6: Invalid Opcode Exception
isr 6
; 7: No Coprocessor Exception
isr 7
; 8: Double Fault Exception
isr 8
; 9: Coprocessor Segment Overrun Exception
isr 9
; 10: Bad TSS Exception
isr 10
; 11: Segment Not Present Exception
isr 11
; 12: Stack Fault Exception
isr 12
; 13: General Protection Fault Exception
isr 13
; 14: Page Fault Exception
isr 14
; 15: Unknown Interrupt Exception
isr 15
; 16: Coprocessor Fault Exception
isr 16
; 17: Alignment Check Exception
isr 17
; 18: Machine Check Exception
isr 18
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
; 32: IRQ0 : System clock
irq 0
; 33: IRQ1 : Keyboard
irq 1
; 34 -> 47 : Currently unused
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15
