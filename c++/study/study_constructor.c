#include <stdio.h>

static void __attribute__ ((constructor)) my_load(void);
static void __attribute__ ((destructor)) my_unload(void);

static void my_load(void)
{
    printf("my_load\n");
}

static void my_unload(void)
{
    printf("my_unload\n");
}

int main()
{
    printf("main\n");
    return 0;
}