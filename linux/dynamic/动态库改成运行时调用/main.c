//main.c 
#include <dlfcn.h>
#include <stdio.h>
int fun_so();

int fun()
{
    printf("%s[%d]:%s\n", __FILE__, __LINE__, __FUNCTION__);
    printf("in main\n");
    return 0;
}

int main()
{
    void *handle;
    int (* p)();
    handle = dlopen ("./lib_so1.so", RTLD_LAZY);
    if (!handle) {
        printf ("dlopen error\n");         
        return -1;
    }

    p = dlsym(handle, "fun_so");     

    (*p)();
    dlclose( handle );
    return 0;
}
