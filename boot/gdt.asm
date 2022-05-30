[bits 16]

GDT_START:

GDT_NULL:
    dq 0

GDT_SEG_KCODE:
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xCF
    db 0

GDT_SEG_KDATA:
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xCF
    db 0

GDT_SEG_TSS:
    dw 0x68
    dw 0
    db 0
    db 0x81
    db 0x40
    db 0

GDT_END:

GDT_REG:
    dw GDT_END - GDT_START - 1
    dd GDT_START