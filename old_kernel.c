// FILE: kernel.c
// 2025/01/28 Voltline

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

extern char __bss[], __bss_end[], __stack_top[];

void* memset(void* buf, char c, size_t n)
{
	uint8_t* p = (uint8_t*)buf;
	while (n--) {
		*p++ = c;
	}
	return buf;
}

void kernel_main(void) 
{
	memset(__bss, 0, (size_t)__bss_end - (size_t)__bss);
	
	for (;;);
}

__attribute__((section(".text.boot")))	// 控制函数在连接器脚本放置的位置
__attribute__((naked))					// 告知编译器不再函数题后生成非必要代码
void boot(void)							// 内核执行的初始位置 
{
	__asm__ __volatile__(
		"mv sp, %[stack_top]\n"			// 设置栈指针
		"j kernel_main\n"				// 跳转到内核主函数
		:
		: [stack_top] "r" (__stack_top)	// 将栈顶地址作为 %[stack_top] 传递	
	);
}
