[bits 32]
PROTECTED_INIT:
    mov ebp, STACK_OFFSET
    mov esp, ebp

    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

BEGIN_KERNEL:
    jmp KERNEL_OFFSET
    jmp $