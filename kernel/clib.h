// FILE: clib.h
// 2025/01/27 Voltline

#ifndef _vOS_CLIB_H
#define _vOS_CLIB_H
#include "types.h"

int isdigit(int c);
void memset(void* _dest, char _num, size_t _size);
void memcpy(void* _dest, const void* _src, size_t _size);

int strlen(const char* _str);
void strcpy(char* _dest, const char* _src);

#endif // _vOS_CLIB_H