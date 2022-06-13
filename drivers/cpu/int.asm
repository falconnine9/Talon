[bits 32]

[extern pit_irq_handler]
[global pit_irq]
pit_irq:
    pushad

    call   pit_irq_handler

    popad
    iretd

[extern rtc_irq_handler]
[global rtc_irq]
rtc_irq:
    pushad

    call rtc_irq_handler

    popad
    iretd
