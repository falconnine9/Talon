[bits 32]
PROTECTED_INIT:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, STACK_OFFSET
    mov esp, ebp

BEGIN_KERNEL:
    jmp KERNEL_OFFSET
    jmp $