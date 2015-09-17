
#ifndef LIBPSX_LIMITS_H
#define LIBPSX_LIMITS_H

#define CHAR_BIT    8

#define SCHAR_MIN   (-128)
#define SCHAR_MAX   127

#define UCHAR_MAX   255

#ifdef __CHAR_UNSIGNED__
#   define CHAR_MIN    0
#   define CHAR_MAX    UCHAR_MAX
#else
#   define CHAR_MIN    SCHAR_MIN
#   define CHAR_MAX    SCHAR_MAX
#endif

#define SHRT_MIN    (-32768)
#define SHRT_MAX    32767
#define USHRT_MAX   65535

#define __INT_MAX__ 2147483647
#define INT_MIN     (-INT_MAX-1)
#define INT_MAX     __INT_MAX__
#define UINT_MAX    4294967295U

#define __LONG_MAX__ 2147483647L
#define LONG_MIN     (-LONG_MAX-1)
#define LONG_MAX     __LONG_MAX__
#define ULONG_MAX    4294967295UL

#define __LONG_LONG_MAX__   9223372036854775807LL
#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#   define LLONG_MIN   (-LLONG_MAX-1)
#   define LLONG_MAX   __LONG_LONG_MAX__
#   define ULLONG_MAX  18446744073709551615ULL
#endif

#if defined (__GNU_LIBRARY__) ? defined (__USE_GNU) : !defined (__STRICT_ANSI__)
#define LONG_LONG_MIN   (-LONG_LONG_MAX-1)
#define LONG_LONG_MAX   __LONG_LONG_MAX__
#define ULONG_LONG_MAX  18446744073709551615ULL
#endif

#endif

