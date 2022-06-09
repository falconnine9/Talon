[bits 16]

; The GDT is where memory segments are defined, this method of
; splitting memory into segments are giving each bit different
; permissions is now considered legacy. Because of this, each
; entry here (with the exception of the TSS) spans a full 4GB,
; overlapping each other. Paging is later used by the kernel
; to split memory into protected segments

GDT_START:

GDT_NULL:
    ; Every GDT must start with a NULL entry
    dq 0

GDT_SEG_KCODE:
    ; Kernel code segment
    ;  - Present:           True
    ;  - DPL:               0 (kernel)
    ;  - Descriptor:        1 (data/code)
    ;  - Executable:        True
    ;  - Direct/Conforming: False
    ;  - Read/Write:        True
    ;  - Accessed:          False
    ;  - Granularity:       True (4KiB blocks)
    ;  - Size:              1 (32 bit)
    ;  - Long:              False (32 bit)
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A
    db 0xCF
    db 0

GDT_SEG_KDATA:
    ; Kernel data segment
    ;  - Present:           True
    ;  - DPL:               0 (kernel)
    ;  - Descriptor:        1 (data/code)
    ;  - Executable:        False
    ;  - Direct/Conforming: False
    ;  - Read/Write:        True
    ;  - Accessed:          False
    ;  - Granularity:       True (4KiB blocks)
    ;  - Size:              1 (32 bit)
    ;  - Long:              False (32 bit)
    dw 0xFFFF
    dw 0
    db 0
    db 0x92
    db 0xCF
    db 0

GDT_SEG_TSS:
    ; Task state segment (System segment)
    dw 0x68
    dw 0
    db 0
    db 0x81
    db 0x40
    db 0

GDT_END:

GDT_REG:
    ; GDT register, to give to the lgdt instruction
    dw GDT_END - GDT_START - 1
    dd GDT_START