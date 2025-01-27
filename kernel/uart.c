// FILE: uart.c
// 2025/01/27 Voltline
#include "uart.h"
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

// 辅助函数：将整数转为字符串（支持十六进制和十进制）
void itoa(unsigned long long val, char* buf, int base) 
{
    static const char digits[] = "0123456789abcdef";
    char temp[32];
    int i = 0;
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    while (val) {
        temp[i++] = digits[val % base];
        val /= base;
    }
    for (int j = 0; j < i; j++) {
        buf[j] = temp[i - j - 1];
    }
    buf[i] = '\0';
}

// 格式化输出函数
void uart_printf(const char* fmt, ...) 
{
    va_list args;
    va_start(args, fmt);
    char buf[64];

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd': { // 十进制整数
                    int val = va_arg(args, int);
                    if (val < 0) {
                        uart_putc('-');
                        val = -val;
                    }
                    itoa(val, buf, 10);
                    uart_puts(buf);
                    break;
                }
                case 'x': { // 十六进制整数
                    unsigned int val = va_arg(args, unsigned int);
                    uart_puts("0x");
                    itoa(val, buf, 16);
                    uart_puts(buf);
                    break;
                }
                case 's': { // 字符串
                    const char* s = va_arg(args, const char*);
                    uart_puts(s);
                    break;
                }
                case 'c': { // 单个字符
                    char c = (char)va_arg(args, int);
                    uart_putc(c);
                    break;
                }
                default:
                    uart_putc('%');
                    uart_putc(*fmt);
                    break;
            }
        } else {
            uart_putc(*fmt);
        }
        fmt++;
    }

    va_end(args);
}