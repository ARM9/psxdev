
#ifndef LIBPSX_STRING_H
#define LIBPSX_STRING_H

#include <stddef.h>

void *memcpy(void *restrict dst, const void *restrict src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *s, int a, size_t n);
void *memset(void *dst, int a, size_t n);

size_t strlen(const char *s);

#endif

