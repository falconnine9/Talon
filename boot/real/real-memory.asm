[bits 16]

ENABLE_A20:
    ; A function which calls int 15h, ax=2401h to enable the A20
    ; line (if it's not already)
    pusha

    mov    ax, 0x2401
    int    0x15

    popa
    ret

DETECT_MEMORY:
    ; Detects available high memory (memory above 1MiB) which is
    ; then stored in MEM_SIZE. This amount is later passed to the
    ; kernel
    pusha

    mov    ah, 0x88
    int    0x15
    mov    [MEM_SIZE], ax

    ; If ax=0, it means there was an error with detecting memory
    cmp    ax, 0
    je     MEMORY_ERROR

    popa
    ret

MEMORY_ERROR:
    ; Prints out the memory error message, then hangs
    mov     bx, MSG_MEM_ERROR
    call    RM_PRINT
    jmp     $

MEM_SIZE      dw 0
MSG_MEM_ERROR db 'Boot error: Failed to detect memory size', 0