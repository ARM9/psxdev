
#ifndef LIBPSX_STDLIB_H
#define LIBPSX_STDLIB_H

#include <stddef.h>

#define EXIT_FAILURE    (-1)
#define EXIT_SUCCESS    0

#define RAND_MAX    2147483647

//#define MB_CUR_MAX  1

typedef struct {
    int quot, rem;
} div_t;

typedef struct {
    long quot, rem;
} ldiv_t;

typedef int (*__compar_fn_t)(const void *, const void *);

int abs(int);
long labs(long);

//void abort(void);
//int atexit(void (*)(void));
//void exit(int);
//getenv();
//int system(const char *);

//double atof(const char *);
int atoi(const char *);
long atol(const char *);
//double strtod(const char *, char **);
long strtol(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);

void *bsearch(const void *, const void *, size_t, size_t,
                int(*)(const void*, const void *));
void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

void *calloc(size_t, size_t);
void free(void *);
void *malloc(size_t);
void *realloc(void *, size_t);

div_t div(int, int);
ldiv_t ldiv(long, long);

int rand(void);
long random(void);
void srand(unsigned);
void srandom(unsigned);

#endif

