# Talon
Basic hobby OS I'm making in C and assembly

## Compiling external UI

## System calls
TalonOS system calls are made with interrupt `0x40`. Arguments are passed with registers.
For every system call, `ax` is where you place the code of the system call, the remaining
register arguments can be found in the table below as well as codes for each system call.

| Name        | Code | Arguments                                           |
|:-----------:|:----:|:---------------------------------------------------:|
| getkey      | 0x0  | **ebx=**Keypress struct pointer                     |
| putc        | 0x1  | **bl=**X pos, **bh=**Y pos, **cx**=Output C         |
| getvgacur   | 0x2  | **ebx=**X pos pointer, **ecx=**Y pos pointer        |
| setvgacur   | 0x3  | **bl=**X pos, **bh=**Y pos                          |
| malloc      | 0x4  | **ebx=**Return block pointer, **ecx**=Size in bytes |
| mfree       | 0x5  | **ebx=**Block pointer                               |
| getpit      | 0x6  | **ebx=**Tick pointer                                |
| getdatetime | 0x7  | **ebx=**Datetime struct pointer                     |
| setdatetime | 0x8  | **ebx=**Datetime struct pointer                     |
| alert       | 0x9  | **ebx=**Message pointer, **cl=**Level               |
| setalert    | 0xA  | **ebx=**Callback pointer                            |