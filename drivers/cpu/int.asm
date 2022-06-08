[bits 32]
[extern pit_irq_handler]
[global pit_irq]

pit_irq:
    pushad

    call pit_irq_handler

    popad
    iret
