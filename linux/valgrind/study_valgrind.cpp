#include <iostream>
#include <cstdio>
#include <cstdlib>

/*
问题1: 数组下标越界
问题2: 内存没有释放
*/
void test1()
{
    printf("%s\n", __FUNCTION__);
    int *x = (int *)malloc(10 * sizeof(int));
    x[10] = 0;
    return;
}

/*
正确
*/
void test2()
{
    printf("%s\n", __FUNCTION__);
    int *p = new int;
    *p = 123;
    printf("*p = %d\n", *p);
    
    delete p;
    p = NULL;
    return;
}

/*
内存没有释放
*/
void test3()
{
    printf("%s\n", __FUNCTION__);
    int *p = new int;
    *p = 123;
    printf("*p = %d\n", *p);
    return;
}

/*
测试覆盖率
*/
void test4()
{
    printf("%s\n", __FUNCTION__);
    int flag = 2;
    if (flag == 1) {
        printf("flag = %d\n", flag);
    } else if (flag == 2) {
        printf("flag = %d\n", flag);
    } else if (flag == 3) {
        printf("flag = %d\n", flag);
    } else {
        printf("flag = %d\n", flag);
    }
    return;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}