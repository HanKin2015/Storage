#include <stdio.h>
#include <string.h>
#define HJ_RK3566 "abc"

char *get_popen()
{
    static char buffer[BUFSIZ] = "abc";
    char *ret = NULL;
    ret = buffer;
    return ret;
}

int main()
{
    char *hw_type = get_popen();
    
    printf("%d %d\n", sizeof(hw_type), strlen(hw_type));        // 8 3
    printf("%d %d\n", sizeof(HJ_RK3566), strlen(HJ_RK3566));    // 10 3
    
    if (strncmp(hw_type, HJ_RK3566, strlen(hw_type)) == 0) {
        printf("this is a HJ_RK3566 client\n");
    }
    
    return 0;
}
