[bits 32]

PROTECTED_INIT:
    ; Initialization/entry point for protected mode

    ; Sets the remaining segment registers to the new GDT_KDATA
    ; entry
    mov    ax, 0x10
    mov    ds, ax
    mov    ss, ax
    mov    es, ax
    mov    fs, ax
    mov    gs, ax

    ; Sets up the 32 bit stack with ebp and esp
    mov    ebp, STACK_OFFSET
    mov    esp, ebp

BEGIN_KERNEL:
    ; The 32 bit C ABI reads function arguments off the stack (last
    ; argument is the first pushed onto the stack). This takes the
    ; 32 bit value MEM_SIZE which has been loaded recently while in
    ; real mode and gives it to the kernel
    mov    eax, [MEM_SIZE]
    mov    ecx, 1024
    mul    ecx
    push   eax

    ; Give control the kernel. The code never returns back here
    jmp    KERNEL_OFFSET