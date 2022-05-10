[bits 16]

GDT_START:

GDT_NULL:
    dq 0

GDT_SEG_KCODE:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 0b10011010
    db 0b11001111
    db 0

GDT_SEG_KDATA:
    dw 0xFFFF
    dw 0x0
    db 0
    db 0b10010010
    db 0b11001111
    db 0

GDT_END:

GDT_REG:
    dw GDT_END - GDT_START - 1
    dd GDT_START