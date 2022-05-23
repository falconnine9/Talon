# This is mostly just made for my computer right now,
# things like i386-elf-gcc or i386-elf-ld don't work by
# default on other systems, neither does the run command

# Boot files
BOOT_ASM = $(wildcard boot/*.asm boot/*/*.asm)

# Kernel files
KERNEL_ASM = $(wildcard */*.asm */*/*.asm)
KERNEL_C   = $(wildcard */*.c */*/*.c)
KERNEL_H   = $(wildcard */*.h */*/*.h)
KERNEL_OUT = $(filter-out ${BOOT_ASM:.asm=.o} kernel/entry.o, ${KERNEL_C:.c=.o} ${KERNEL_ASM:.asm=.o})

# General
CWD = $(shell pwd)

TalonOS.img: talon.bin
	@echo "Copying binary output to OS image"
	@dd if=$< of=$@ bs=512 count=$(shell echo $(shell stat --printf="%s" talon.bin)/512+1 | bc)

talon.bin: boot.bin kernel.bin
	@echo "Adding kernel and boot sector together"
	@cat $^ > $@

boot.bin: kernel.bin ${BOOT_ASM}
	@echo "Compiling bootsector with $(shell echo $(shell stat --printf="%s" kernel.bin)/512+1 | bc) sectors"
	@nasm -f bin -d KERNEL_SECTORS=$(shell echo $(shell stat --printf="%s" kernel.bin)/512+1 | bc) -o $@ boot/boot.asm

kernel.bin: kernel/entry.o ${KERNEL_OUT}
	@echo "Linking all kernel output files"
	@i386-elf-ld -o $@ -Ttext 0x2210 $^ --oformat binary

%.o: %.c ${HEADERS}
	@echo "Compiling C file: $<"
	@i386-elf-gcc -O2 -I "$(CWD)" -ffreestanding -c $< -o $@

%.o: %.asm
	@echo "Compiling assembly file: $<"
	@nasm -f elf -o $@ $<

clean:
	@echo "Cleaning output"
	@rm -rf kernel/entry.o ${KERNEL_OUT}
	@rm -rf boot.bin kernel.bin talon.bin

run:
	@echo "Running emulator"
	@"/mnt/c/Program Files/qemu/qemu-system-x86_64.exe" -fda TalonOS.img

debug:
	@echo "Starting debugger"
	@echo "Copy the following into GDB:"
	@echo "target remote | \"/mnt/c/Program Files/qemu/qemu-system-x86_64.exe\" -S -gdb stdio -m 16 -boot c -fda TalonOS.img"
	@gdb