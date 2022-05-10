[bits 16]
PROTECTED_ENTRY:
    cli
    lgdt [GDT_REG]

    mov eax, cr0
    or  eax, 0x1
    mov cr0, eax

    jmp 0x8:PROTECTED_INIT