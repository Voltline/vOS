/* FILE: linker.ld */
/* 2025/01/27 Voltline */
OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000,
    LENGTH = 128M
}

PHDRS {
    text PT_LOAD FLAGS(5); /* R-X (Read + Execute) */
    data PT_LOAD FLAGS(6); /* RW- (Read + Write) */
}

SECTIONS {
    .text : {
        *(.text.init)
        *(.text .text.*)
    } > RAM : text

    .rodata : {
        *(.rodata .rodata.*)
    } > RAM : text

    .data : {
        *(.data .data.*)
    } > RAM : data

    .bss : {
        . = ALIGN(8);
        _bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        _bss_end = .;
    } > RAM : data

    .stack : {
        . = ALIGN(16);
        . += 4096; /* 4KB 堆栈 */
        _stack_end = .;
    } > RAM : data
}