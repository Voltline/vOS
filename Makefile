# FILE: Makefile
# 2025/01/27 Voltline 

CC = riscv64-unknown-elf-gcc
CFLAGS = -nostdlib -ffreestanding -march=rv64gc -mabi=lp64 -mcmodel=medany -T linker.ld
QEMU = qemu-system-riscv64

all: kernel.elf

kernel.elf : boot.S main.c
	$(CC) $(CFLAGS) $^ -o $@

run: kernel.elf
	$(QEMU) -machine virt -nographic -bios none -kernel $<

clean:
	rm -f kernel.elf