// FILE: kernel.c
// 2025/01/28 Voltline

#include "kernel.h"
#include "common.h"
#include "format.h"
#include "trap.h"

extern char __bss[], __bss_end[], __stack_top[];

void kernel_main(void)
{
    memset(__bss, 0, (size_t)__bss_end - (size_t)__bss);
    printf("%s\n\nWelcome to vOS!\n%s", GREEN, CLEAR);

    WRITE_CSR(stvec, (uint32_t)kernel_entry);
    //__asm__ __volatile__("unimp");

    printf("1 + 2 = %d, %x\n", 1 + 2, 0x1234abcd);

	for (;;) {
		__asm__ __volatile__("wfi");
	}
}

__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) 
{
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"			// 设置栈指针
        "j kernel_main\n"				// 跳转到内核主函数
        :
        : [stack_top] "r" (__stack_top) // 将栈顶地址作为 %[stack_top] 传递
    );
}
