[bits 32]
[extern idt_isr_handler]

%macro ISR 1
isr%+%1:
    pushad

    push %1
    call idt_isr_handler
    pop eax

    popad
    leave

    %if %1 == 8
        jmp $
    %else
        iretd
    %endif
%endmacro

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31

[global isr_table]
isr_table:
    %assign i 0
    %rep 32
        dd isr%+i
        %assign i i+1
    %endrep