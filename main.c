// FILE: main.c
// 2025/01/27 Voltline
#define QEMU_UART_ADDR 0x10000000
volatile unsigned int* const UART0 = (unsigned int*)QEMU_UART_ADDR;

void uart_putc(char c) 
{
    *UART0 = c;
}

void uart_puts(const char* s)
{
    while (*s) {
        uart_putc(*s++);
    }
}

int main()
{
    uart_puts("Hello from vOS Kernel!\n");
    uart_puts("vOS Kernel based on RISC-V, developed by Voltline\n");
    while (1);
}