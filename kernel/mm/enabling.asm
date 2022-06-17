[bits 32]
[extern mm_pd]
[global mm_enable]

mm_enable:
    mov    eax, mm_pd
    mov    cr3, eax

    mov    eax, cr4
    or     eax, (1 << 4)
    mov    cr4, eax

    mov    eax, cr0
    or     eax, (1 << 31)
    mov    cr0, eax

    ret