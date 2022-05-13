[bits 16]
RM_DISK_LOADER:
    pusha

    mov ah, 0x2
    mov ch, 0x0
    mov dh, 0x0
    mov [SECTORS_LOADED], al

    int 0x13
    jc RM_DISK_ERROR

    cmp al, [SECTORS_LOADED]
    jne RM_DISK_ERROR

    popa
    ret

RM_DISK_ERROR:
    mov bx, MSG_DISK_ERROR
    call RM_PRINT
    jmp $

MSG_DISK_ERROR db 'Error loading sectors from disk', 0
SECTORS_LOADED db 0