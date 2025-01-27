// FILE: main.c
// 2025/01/27 Voltline
#include "uart.h"
#include "clib.h"

int main()
{
    uart_printf("Hello from vOS Kernel!\n");
    uart_printf("vOS Kernel based on RISC-V, developed by Voltline\n");
    char s1[120] = { 0 }, s2[120] = { 0 };
    memset(s1, 'a', 20);
    uart_printf("[DEBUG]: s1 = %s\n", s1);
    memcpy(s2, s1, 20);
    uart_printf("[DEBUG]: s2 = %s\n", s2);
    memset(s2, 'd', 30);
    strcpy(s1, s2);
    uart_printf("[DEBUG]: s1 = %s\n", s1);
    while (1);
}