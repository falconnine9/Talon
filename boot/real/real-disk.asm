[bits 16]

RM_DISK_LOADER:
    ; General function to load sectors from the disk (Some register
    ; arguments are passed by the caller, so they aren't found here)
    pusha

    ; ax=2 (read sectors), ch=0 (cylinder 0), dh=0 (head 0)
    mov    ah, 0x2
    mov    ch, 0x0
    mov    dh, 0x0
    mov    [SECTORS_LOADED], al

    ; Calls int 13h, if the carry bit was set (error) then the error
    ; message is sent
    int    0x13
    jc     RM_DISK_ERROR

    ; al is now stored with the amount of sectors actually loaded, so
    ; if that number doesn't line up with the originally requested
    ; amount of sectors then the error message is sent
    cmp    al, [SECTORS_LOADED]
    jne    RM_DISK_ERROR

    call   RM_DISK_SUCCESS
    popa
    ret

RM_DISK_SUCCESS:
    ; Prints out the disk success message
    mov    bx, MSG_DISK_SUCCESS
    call   RM_ALERT
    ret

RM_DISK_ERROR:
    ; Prints out the disk error message, then hangs
    mov    bx, MSG_DISK_ERROR
    call   RM_ALERT_ERR
    jmp    $

SECTORS_LOADED   db 0
MSG_DISK_SUCCESS db 'Loaded sectors from disk', 0
MSG_DISK_ERROR   db 'Failed to load sectors from disk', 0