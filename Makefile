# FILE: Makefile
# 2025/01/27 Voltline

CC = riscv64-unknown-elf-gcc
CFLAGS = -nostdlib -ffreestanding -march=rv64gc -mabi=lp64 -mcmodel=medany -T kernel/linker.ld
QEMU = qemu-system-riscv64

# 设置源文件所在目录
SRC_DIR = kernel
OBJ_DIR = build

# 创建目标文件目录（如果没有）
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 目标文件
OBJ_FILES = $(OBJ_DIR)/boot.o \
			$(OBJ_DIR)/main.o \
			$(OBJ_DIR)/uart.o \
			$(OBJ_DIR)/clib.o

all: kernel.elf

# 编译目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf : $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

run: kernel.elf
	$(QEMU) -machine virt -nographic -bios none -kernel $<

clean:
	rm -rf kernel.elf $(OBJ_DIR)