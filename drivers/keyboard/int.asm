[bits 32]
[extern kbd_irq_handler]
[global kbd_irq]

kbd_irq:
    pusha

    call kbd_irq_handler

    popa
    iret