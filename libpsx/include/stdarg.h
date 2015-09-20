
#ifndef LIBPSX_STDARG_H
#define LIBPSX_STDARG_H

#define va_arg(v,type)      __builtin_va_arg(v,type)

#define va_start(v,parmN)   __builtin_va_start(v,parmN)
#define va_end(v)           __builtin_va_end(v)
#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   define va_copy(d,s)     __builtin_va_copy(d,s)
#endif
#define __va_copy(d,s)      __builtin_va_copy(d,s)

typedef __gnuc_va_list va_list;

#endif

