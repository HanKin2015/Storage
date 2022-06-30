#include <stdio.h>

//可以输出变量名
#define get_marco_name(x) #x
#define MAXN 1005
#define get_name(x) #x

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
	// 输出1005 MAXN
    printf("%d %s\n", MAXN, get_marco_name(MAXN));
	// 输出FRIDAY: FRIDAY, 5
	printf("FRIDAY: %s, %d\n", get_marco_name(FRIDAY), FRIDAY);
	
    int tmp = MAXN;
    switch(tmp) {
        case MAXN:
			// 输出1005 tmp
            printf("%d %s\n", tmp, get_marco_name(tmp));
            break;
        default:
            printf("default\n");
    }

    //error: stray ‘#’ in program(没有弄明白，直接使用#+变量名无法正常运行)
    //printf("FRIDAY: %s\n", (#FRIDAY));
	
	char temp[] = get_marco_name(FRIDAY);
	printf("FRIDAY: %s\n", temp);
	printf("get_name: %s\n", get_name(FRIDAY));
	
    //char str[] = (#FRIDAY);
	//printf("FRIDAY: %s\n", str);

    while(scanf("%d", &tmp) != EOF) {
        printf("key: %d, value: %s\n", tmp, MsgTypeNames[tmp]);
    }
    return 0;
}
/*
1005 MAXN
FRIDAY: FRIDAY, 5
1005 tmp
FRIDAY: FRIDAY
get_name: FRIDAY
4
key: 4, value: THURESDAY
7
key: 7, value: SUNDAY
8
key: 8, value: (null)
9
key: 9, value: (null)
*/