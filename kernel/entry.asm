[bits 32]
[extern k_main]
[global _start]

_start:
    call   k_main
    jmp    $