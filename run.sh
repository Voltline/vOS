#!/bin/bash
# FILE: run.sh
# 2025/01/28 Voltline

set -xue

# QEMU 路径
QEMU=qemu-system-riscv32

# clang 路径和编译器标志
CC=/opt/homebrew/opt/llvm/bin/clang # macOS
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32 -ffreestanding -nostdlib"

# 构建内核
$CC $CFLAGS -Wl,-Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
	kernel.c

# 启动QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
	-kernel kernel.elf
