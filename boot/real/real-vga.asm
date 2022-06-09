[bits 16]

RM_PRINT:
    ; Entry point for the real mode print, it pushes registers
    ; then continues onto the main code
    pusha
    
RM_PRINT_LOOP:
    ; A loop which goes through each character in the string,
    ; printing it out until it finds a NULL terminator

    ; Moves the next character into al (from bx), checks if
    ; it's NULL and exits if it is
    mov    al, [bx]
    cmp    al, 0x0
    je     RM_PRINT_NEWLINE

    ; int 10h to output the character
    mov    ah, 0x0E
    int    0x10

    ; Go to the next character and jump back to the top of
    ; the loop
    add    bx, 1
    jmp    RM_PRINT_LOOP

RM_PRINT_NEWLINE:
    ; Outputs a newline after the string has been printed
    mov    ah, 0x0E
    mov    al, 0x0A
    int    0x10
    mov    al, 0x0D
    int    0x10

RM_PRINT_DONE:
    ; Restores registers, then returns
    popa
    ret