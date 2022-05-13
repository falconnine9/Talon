[org 0x7c00]
[bits 16]

KERNEL_OFFSET equ 0x1000
STACK_OFFSET  equ 0x9000

    mov [BOOT_DRIVE], dl

    mov bp, STACK_OFFSET
    mov sp, bp

    mov dl, [BOOT_DRIVE]
    mov cl, 0x2
    mov bx, KERNEL_OFFSET
    mov al, KERNEL_SECTORS
    call RM_DISK_LOADER

    jmp PROTECTED_ENTRY

%include "boot/gdt.asm"

%include "boot/real/real-disk.asm"
%include "boot/real/real-vga.asm"

%include "boot/protected/protected-body.asm"
%include "boot/protected/protected-entry.asm"

BOOT_DRIVE        db 0

BOOTSECT:
    times 510-($-$$) db 0
    dw 0xAA55