[bits 32]
[extern kbd_irq_handler]
[global kbd_irq]

kbd_irq:
    pushad

    call   kbd_irq_handler

    popad
    iretd