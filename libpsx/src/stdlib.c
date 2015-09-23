
#include <stdlib.h>

inline int abs(int n) {
    int result, dummy;
    __asm__ __volatile__(
        "sra %[tmp], %[in], 31\n\t"
        "xor %[in], %[in], %[tmp]\n\t"
        "sub %[out], %[in], %[tmp]\n\t"
        :[out] "=r" (result), [tmp] "=r" (dummy)
        :[in] "r" (n)
        :);
    return result;
}

inline long labs(long n) {
    return n < 0L ? -n : n;
}

int atoi(const char *str) {
    return 0;
}

long atol(const char *str) {
    return 0L;
}

long strtol(const char *str, char **end, int base) {
    return 0L;
}

unsigned long strtoul(const char *str, char **end, int base) {
    return 0UL;
}

void *bsearch(const void *key, const void *base, size_t nitems,
        size_t item_size, int (*compar)(const void *, const void *))
{
    return NULL;
}

void qsort(void *base, size_t nitems, size_t item_size,
        int (*compar)(const void *, const void *))
{

}

void *malloc(size_t size) {
    return NULL;
}

void *calloc(size_t num, size_t size) {
    return NULL;
}

void *realloc(void *block, size_t size) {
    return NULL;
}

void free(void *block) {
    
}

div_t div(int num, int den) {
    return (div_t){.quot=num/den, .rem=num%den};
}

ldiv_t ldiv(long num, long den) {
    return (ldiv_t){.quot=num/den, .rem=num%den};
}

int rand(void) {
    return 4;
}

long random(void) {
    return 4L;
}

void srand(unsigned seed) {

}

void srandom(unsigned seed) {

}

