# FILE: boot.S
# 2025/01/27 Voltline
.section .text.init
.global _start

_start:
    # 设置堆栈指针(0x80000000)
    la sp, _stack_end
    # 清零BSS
    call clear_bss
    # 跳转到main
    call main
    # 主函数结束后死循环
    j .

clear_bss:
    la a0, _bss_start
    la a1, _bss_end
    bgeu a0, a1, clear_bss_done
clear_bss_loop:
    sd zero, (a0)
    addi a0, a0, 8
    bltu a0, a1, clear_bss_loop
clear_bss_done:
    ret