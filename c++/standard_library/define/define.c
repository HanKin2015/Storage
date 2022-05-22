#include <stdio.h>

//可以输出变量名
#define get_marco_name(x) #x
#define MAXN 1005

enum {
    MONDAY=1,
    TUESDAY,
    WEDNESDAY,
    THURESDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

//c++不支持这种可能不连续的值
static const char *MsgTypeNames[] = {
    [MONDAY]    = "MONDAY",
    [TUESDAY]   = "TUESDAY",
    [WEDNESDAY] = "WEDNESDAY",
    [THURESDAY] = "THURESDAY",
    [FRIDAY]    = "FRIDAY",
    [SATURDAY]  = "SATURDAY",
    [SUNDAY]    = "SUNDAY",
};

int main()
{
    printf("%d %s\n", MAXN, get_marco_name(MAXN));
    int tmp = MAXN;
    switch(tmp) {
        case MAXN:
            printf("%d %s\n", tmp, get_marco_name(tmp));
            break;
        default:
            printf("default\n");
    }

    printf("FRIDAY: %d\n", FRIDAY);
    //error: stray ‘#’ in program(没有弄明白)
    //printf("FRIDAY: %s\n", (#FRIDAY));
    printf("FRIDAY: %s\n", get_marco_name(FRIDAY));

    while(scanf("%d", &tmp) != EOF) {
        printf("key: %d, value: %s\n", tmp, MsgTypeNames[tmp]);
    }
    return 0;
}
