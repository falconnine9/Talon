[bits 16]

RM_ALERT:
    ; An alert utility to output information in a specific format.
    ; "Boot: [MESSAGE]"
    push   bx
    mov    bx, MSG_ALERT
    jmp    RM_ALERT_COMMON

RM_ALERT_ERR:
    ; Same alert utility as before, but it prints out in a different
    ; format than before. "Boot error: [MESSAGE]"
    push   bx
    mov    bx, MSG_ALERT_ERR

RM_ALERT_COMMON:
    ; Common print for both. The only difference between the 2 alerts
    ; is the intial message, so there's no sense in having the custom
    ; message be printed in both
    mov    dl, 0x0
    call   RM_PRINT

    pop    bx
    mov    dl, 0x1
    call   RM_PRINT

    ret

MSG_ALERT     db 'Boot: ', 0
MSG_ALERT_ERR db 'Boot error: ', 0