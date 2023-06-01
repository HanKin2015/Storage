#include <stdio.h>

int main(void)
{
#ifdef TEST_OPTION
    printf("Hello, CMake.\n");
#endif

#ifdef HJ
    printf("HJ = %d\n", HJ);
#endif

#if JH
    printf("JH = %d\n", JH);
#else
    printf("JH = %d\n", JH);
#endif
    return 0;
}
