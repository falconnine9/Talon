[bits 16]
[org 0x7C00]

STACK_OFFSET  equ 0x2200 ; 8KiB area for the stack (growing downwards)
KERNEL_OFFSET equ 0x2210 ; Kernel placement right after the stack
KERNEL_SECTOR equ 0x0002 ; Where the remaining sectors of the kernel are

    ; Some things that need to be done before the boot sequence
    ; message can be printed
    mov    [BOOT_DRIVE], dl
    mov    bp, STACK_OFFSET
    mov    sp, bp

    ; Print the boot sequence message
    mov    bx, MSG_BOOT_BEGIN
    call   RM_PRINT

    ; Load in the remaining sectors of the kernel
    mov    dl, [BOOT_DRIVE]
    mov    cl, KERNEL_SECTOR
    mov    bx, KERNEL_OFFSET
    mov    al, KERNEL_SECTORS
    call   RM_DISK_LOADER

    ; Enable the A20 line and detect how much memory is available
    call   ENABLE_A20
    call   DETECT_MEMORY

    ; Jump to the protected entry method (The code never returns
    ; from here so a simple JMP can be used)
    jmp    PROTECTED_ENTRY

%include "boot/gdt.asm"

%include "boot/real/real-disk.asm"
%include "boot/real/real-memory.asm"
%include "boot/real/real-vga.asm"

%include "boot/protected/protected-body.asm"
%include "boot/protected/protected-entry.asm"

BOOT_DRIVE     db 0
MSG_BOOT_BEGIN db 'Starting boot sequence', 0

BOOTSECT:
    times 510-($-$$) db 0
    dw 0xAA55