[bits 16]
RM_PRINT:
    pusha
    
RM_PRINT_LOOP:
    mov al, [bx]
    cmp al, 0x0
    je  RM_PRINT_NEWLINE

    mov ah, 0x0E
    int 0x10

    add bx, 1
    jmp RM_PRINT_LOOP

RM_PRINT_NEWLINE:
    mov ah, 0x0E

    mov al, 0x0A
    int 0x10

    mov al, 0x0D
    int 0x10

RM_PRINT_DONE:
    popa
    ret