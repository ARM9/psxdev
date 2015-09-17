
int foo[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
char *bar = "HELLO WORLD!!!!!";
static char *aaa = "Your face has healed nicely";
static long long int slli = 5ULL;
static short ss;
static int many[100];
const int ci = 0xcacebeef;

extern void sectionTest(void);

int main(int argc, char *argv[])
{
    static char *laz = "don't raise your voice in public";
    static short lss;
    char *baz = "pigs\non\rthe    wing  ";
    const int lci = 0xbeefcace;

    sectionTest();
    /*double y = 3.14*2;*/
    /*float x = 1.0/((double) argc);*/
    /*float z = 5.5;*/
    return 0x42;
}
