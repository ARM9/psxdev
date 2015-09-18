
#ifndef LIBPSX_STDDEF_H
#define LIBPSX_STDDEF_H

#define NULL ((void *) 0)

//#define offsetof(st, member) ((size_t) (&((st *) 0)->member))
#define offsetof(st, member) __builtin_offsetof(st, member)

typedef int ptrdiff_t;

typedef int ssize_t;
typedef unsigned size_t;

typedef int wchar_t;

#endif

