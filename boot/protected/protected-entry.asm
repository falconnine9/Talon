[bits 16]

PROTECTED_ENTRY:
    ; Entry function for protected mode. This function will setup all
    ; the necessary requirements to enter protected mode

    ; Disables interrupts and loads the GDT
    cli
    lgdt   [GDT_REG]

    ; Sets the carry bit to 1
    mov    eax, cr0
    or     eax, 0x1
    mov    cr0, eax

    ; Far jump to the protected mode functions, this will also load the
    ; new GDT_KCODE entry into the cs register
    jmp    0x8:PROTECTED_INIT