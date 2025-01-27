// FILE: clib.c
// 2025/01/27 Voltline

#include "clib.h"

int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

void memset(void* _dest, char _num, size_t _size) 
{
    const int _dword_size = sizeof(uint64_t);
    int _dword_count = _size / _dword_size;
    int _byte_count = _size / _dword_size;
    uint64_t _dword_data = 0;
    for (int i = 0; i < _dword_size; ++i) {
        _dword_data <<= _dword_size;
        _dword_data += _num;
    } 
    uint64_t* _dword_ptr = (uint64_t*)_dest;
    for (int i = 0; i < _dword_count; ++i) {
        _dword_ptr[i] = _dword_data;
    }
    char* _byte_ptr = (char*)(_dest + _dword_count * _dword_size);
    for (int i = 0; i < _byte_count; ++i) {
        _byte_ptr[i] = _num;
    }
}

void memcpy(void* _dest, const void* _src, size_t _size)
{
    const int _dword_size = sizeof(uint64_t);
    int _dword_count = _size / _dword_size;
    int _byte_count = _size / _dword_size;
    uint64_t _dword_data = 0;
    uint64_t* _dword_dest_ptr = (uint64_t*)_dest;
    const uint64_t* _dword_src_ptr = (const uint64_t*)_src;
    for (int i = 0; i < _dword_count; ++i) {
        _dword_dest_ptr[i] = _dword_src_ptr[i];
    }
    char* _byte_dest_ptr = (char*)(_dest + _dword_count * _dword_size);
    const char* _byte_src_ptr = (const char*)(_src + _dword_count * _dword_size);
    for (int i = 0; i < _byte_count; ++i) {
        _byte_dest_ptr[i] = _byte_src_ptr[i];
    }
}

int strlen(const char* _str)
{
    int cnt = 0;
    while (*_str++) {
        ++cnt;
    }
    return cnt;
}

void strcpy(char* _dest, const char* _src)
{
    while (*_src) {
        *_dest++ = *_src++;
    }
    *_dest = 0;
}
