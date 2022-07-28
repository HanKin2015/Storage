#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef DEBUG
    printf("DEBUG is definded \n");
#else
    printf("DEBUG is not definded \n");
#endif
}
