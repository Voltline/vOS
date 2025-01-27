// FILE: uart.h
// 2025/01/27 Voltline
#ifndef _vOS_UART_H
#define _vOS_UART_H
#include <stdarg.h>

void uart_putc(char c);
void uart_puts(const char* s);
void uart_printf(const char* fmt, ...);

#endif // _vOS_UART_H