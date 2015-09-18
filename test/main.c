#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

int foo[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
char *bar = "HELLO WORLD!!!!!";
static char *aaa = "Your face has healed nicely";
static long long int slli = 5ULL;
static short ss;
static int many[100];
const int ci = 0xcacebeef;

int lolgcc[] = {[0 ... 9] = 1, [10 ... 99] = 2, [100] = 3};
char mucha[] = {[0 ... 10] = 'a', 0};

extern void sectionTest(void);

struct myStruct_s {
    int first;
    char second;
    char third;
    char *fourth;
    long long fifth;
    char sixth;
};

int main(int argc, char *argv[])
{
    static char *laz = "don't raise your voice in public";
    static short lss;
    char *baz = "pigs\non\rthe    wing  ";
    const int lci = 0xbeefcace;

    int a = sizeof(int8_t);
    int b = sizeof(uint32_t);
    int b2 = sizeof(size_t);
    int c = sizeof(int64_t);
    int c2 = sizeof(long) == sizeof(int);

    int d = INT_MAX;
    bool cool = sizeof(int32_t) != sizeof(int64_t);
    long long e = LLONG_MAX;
    struct myStruct_s mys = {.first=42, .sixth='a', .second='2', .fourth=baz};
    size_t f = offsetof(struct myStruct_s, second);
    size_t g = offsetof(struct myStruct_s, third);
    size_t h = offsetof(struct myStruct_s, fourth);

    printf("%s\n%s\n%s\n%s\n%s\n%d %x", bar, aaa, laz, baz, mucha, mys.first, mys.sixth);

    printf("\n%d %d %d", a, b, b2);
    printf("\n%x %X %U %X", c, baz[2], baz[2], baz[3]);

    while(1){

    }
    return 0x42;
}
