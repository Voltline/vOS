// FILE: kernel.h
// 2025/01/28 Voltline

#pragma once

#define PANIC(fmt, ...)                                                         \
    do {                                                                        \
        printf("\e[31m");                                                            \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);   \
        printf("\e[0m");                                                          \
        while (1) {}                                                            \
    } while (0)        

#define READ_CSR(reg)                                       \
    ({                                                      \
        unsigned long __tmp;                                \
        __asm__ __volatile("csrr %0, " #reg : "=r"(__tmp)); \
        __tmp;                                              \
    })

#define WRITE_CSR(reg, value)                                   \
    do {                                                        \
        uint32_t __tmp = (value);                               \
        __asm__ __volatile__("csrw " #reg ", %0" :: "r"(__tmp));\
    } while (0)  