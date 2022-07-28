#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef CUSTOMHJ
    printf("CUSTOMHJ is definded \n");
#else
    printf("CUSTOMHJ is not definded \n");
#endif
}
