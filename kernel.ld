/* FILE: kernel.ld */
/* 2025/01/28 Voltline */
ENTRY(boot) /* 声明入口点为boot */

SECTIONS {
	. = 0x80200000;  /* 基地址为0x80200000 */

	.text : { /* 程序代码段 */
		KEEP(*(.text.boot));
		*(.text .text.*);
	}

	.rodata : ALIGN(4) { /* 只读的常量数据 */
		*(.rodata .rodata.*);
	}

	.data : ALIGN(4) { /* 可读写的数据段 */
		*(.data .data.*);
	}

	.bss : ALIGN(4) { /* 初始值为0的可读写数据 */
		__bss = .;
		*(.bss .bss.* .sbss .sbss.*);
		__bss_end = .;
	}

	. = ALIGN(4);
	. += 128 * 1024; /* 内核栈大小 128 KB */
	__stack_top = .;
}
