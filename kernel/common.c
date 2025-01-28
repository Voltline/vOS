// FILE: common.c
// 2025/01/28 Voltline

#include "common.h"
#include "syscall.h"
#include "format.h"

void putchar(char ch);
void puts(const char* s);

void* memcpy(void* dst, const void* src, size_t n)
{
    uint8_t* d = (uint8_t*)dst;
    const uint8_t* s = (const uint8_t*)src;
    while (n--) {
        *d++ = *s++;
    }
    return dst;
}

void* memset(void* buf, char c, size_t n)
{
    uint8_t* p = (uint8_t*)buf;
    while (n--) {
        *p++ = c;
    }
    return buf;
}

char* strcpy(char* dst, const char* src)
{
    char* d = dst;
    while (*src) {
        *d++ = *src++;
    }
    *d = 0;
    return dst;
}

int strcmp(const char* s1, const char* s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2) {
            break;
        }
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void putchar(char ch)
{
	sbi_call(ch, 0, 0, 0, 0, 0, 0, 1); // Console Putchar
}

void puts(const char* s)
{
	while (*s) {
		putchar(*s++);
	}
}

void debug_puts(const char* s)
{
	puts(GREEN);
	puts(s);
	putchar('\n');
	puts(CLEAR);
}

// 实现来自https://operating-system-in-1000-lines.vercel.app/zh/05-hello-world
// @Return: 格式化变量输出数量
int printf(const char* fmt, ...)
{
	int count = 0;
	va_list vargs;
	va_start(vargs, fmt);

	while (*fmt) {
		if (*fmt == '%') {
			fmt++; // 跳过 % 
			switch (*fmt) { // 读取下一个字符
			case '\0':		// % 作为结尾
				putchar('%');
				goto end;
			case '%':		// 打印 %
				putchar('%');
				break;
			case 's': {		// 打印以 NULL 结尾的字符串
				const char* s = va_arg(vargs, const char*);
				count++;
				puts(s);
				break;
			}
			case 'd': {		// 打印十进制整型
				int value = va_arg(vargs, int);
				count++;
				if (value < 0) {
					putchar('-');
					value = -value;
				}

				int divisor = 1;
				while (value / divisor > 9) 
					divisor *= 10;
				
				while (divisor > 0) {
					putchar('0' + value / divisor);
					value %= divisor;
					divisor /= 10;
				}	
				break;
			}
			case 'x': {
				int value = va_arg(vargs, int);
				count++;
				for (int i = 7; i >= 0; i--) {
					int nibble = (value >> (i * 4)) & 0xf;
					putchar("0123456789abcdef"[nibble]);
				}			
			}		  
			}
		}
		else {
			putchar(*fmt);
		}
		fmt++;
	}
end:
	va_end(vargs);
	return count;
}
