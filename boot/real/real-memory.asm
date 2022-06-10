[bits 16]

ENABLE_A20:
    ; A function which calls int 15h, ax=2401h to enable the A20
    ; line (if it's not already)
    pusha

    mov    ax, 0x2401
    int    0x15

    call   MEMORY_A20_SUCCESS
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
    je     MEMORY_DETECT_ERROR

    call   MEMORY_DETECT_SUCCESS
    popa
    ret

MEMORY_A20_SUCCESS:
    ; Prints out the A20 line success message
    mov    bx, MSG_MEM_A20_SUCCESS
    call   RM_ALERT
    ret

MEMORY_DETECT_SUCCESS:
    ; Prints out the memory detection success message
    mov    bx, MSG_MEM_DETECT_SUCCESS
    call   RM_ALERT
    ret

MEMORY_DETECT_ERROR:
    ; Prints out the memory detection error message, then hangs
    mov    bx, MSG_MEM_DETECT_ERROR
    call   RM_ALERT_ERR
    jmp    $

MEM_SIZE               dw 0
MSG_MEM_A20_SUCCESS    db 'A20 line enabled', 0
MSG_MEM_DETECT_SUCCESS db 'High memory size detected', 0
MSG_MEM_DETECT_ERROR   db 'Failed to detect memory size', 0