[bits 32]
[extern syscall_handler]
[global syscall_isr]

syscall_isr:
    call   syscall_handler
    iretd