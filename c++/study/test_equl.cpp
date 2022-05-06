#include <stdio.h>

int main()
{
    int m = 2;
    if (m = 1) {
        printf("yes %d\n", m);
    } else {
        printf("no %d\n", m);
    }
    
    if (m = 0) {
        printf("yes %d\n", m);
    } else {
        printf("no %d\n", m);
    }
    
    // 编译不通过error: lvalue required as left operand of assignment
    if (1 = m) {
        printf("yes %d\n", m);
    } else {
        printf("no %d\n", m);
    }
    return 0;
}
