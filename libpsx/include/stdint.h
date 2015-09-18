
#ifndef LIBPSX_STDINT_H
#define LIBPSX_STDINT_H

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

typedef int32_t intptr_t;
typedef uint32_t uintptr_t;

#undef  __INT8_MAX__
#define __INT8_MAX__    127
#define INT8_MIN    (-INT8_MAX-1)
#define INT8_MAX    __INT8_MAX__
#define UINT8_MAX   (__INT8_MAX__ * 2U + 1)

#undef  __INT16_MAX__
#define __INT16_MAX__   32767
#define INT16_MIN   (-INT16_MAX-1)
#define INT16_MAX   __INT16_MAX__
#define UINT16_MAX  (__INT16_MAX__ * 2U + 1)

#undef  __INT32_MAX__
#define __INT32_MAX__   2147483647
#define INT32_MIN   (-INT32_MAX-1)
#define INT32_MAX   __INT32_MAX__
#define UINT32_MAX  (__INT32_MAX__ * 2U + 1)

#undef  __INT64_MAX__
#define __INT64_MAX__   9223372036854775807LL
#define INT64_MIN   (-INT64_MAX-1)
#define INT64_MAX   __INT64_MAX__
#define UINT64_MAX  (__INT64_MAX__ * 2ULL + 1)

#undef  __INTPTR_MAX__
#define __INTPTR_MAX__  __INT32_MAX__
#define INTPTR_MIN  (-INTPTR_MAX-1)
#define INTPTR_MAX  __INTPTR_MAX__

#undef  __UINTPTR_MAX__
#define __UINTPTR_MAX__ (__INT32_MAX__ * 2U + 1)
#define UINTPTR_MAX __UINTPTR_MAX__

#define SIZE_MAX    (__INT32_MAX__ * 2U + 1)

#define PTRDIFF_MIN (-PTRDIFF_MAX-1)
#define PTRDIFF_MAX __INT32_MAX__

#endif

