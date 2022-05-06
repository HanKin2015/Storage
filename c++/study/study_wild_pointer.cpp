#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

static void test1()
{
    int n = 12345;
    
    int *p = new int;
    *p = n;
    
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    
    delete p;
    p = NULL;   // 判NULL的重要性，避免使用空指针
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    
    p = new int;
    *p = n;
    delete p;   // 这个就是野指针，没有输出期望值
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    return;
}

static void test2()
{
    int arr[] = {1, 2, 3, 4, 5};
    
    int *p = new int;
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    
    p = arr + 2;
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    
    p = arr + 22;   // 这个也是野指针
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    return;
}

static int *test3_()
{
    int *p_arr[5];
    for (int i = 0; i < 5; i++) {
        p_arr[i]  = new int;
        *p_arr[i] = i;
    }
    
    assert(p_arr[22] == NULL);
    p_arr[22] = p_arr[2];
    return p_arr[22];
}
static int *test3__()
{
    int *p_arr[5];
    for (int i = 0; i < 5; i++) {
        p_arr[i]  = new int;
        *p_arr[i] = i;
    }
    
    assert(p_arr[153] == NULL);
    p_arr[153] = p_arr[2];
    return p_arr[153];
}
static void test3()
{
    int *p_arr[5];
    for (int i = 0; i < 5; i++) {
        p_arr[i]  = new int;
        *p_arr[i] = i;
    }
    
    if (p_arr[2] != NULL) printf("%d: %p [%d]\n", __LINE__, p_arr[2], *p_arr[2]);
    if (p_arr[22] != NULL) printf("%d: %p [%d]\n", __LINE__, p_arr[22], *p_arr[22]);
    
    int *p = p_arr[22];
    if (p != NULL) printf("%d: %p [%d]\n", __LINE__, p, *p);
    
    int *p_ = test3_();
    if (p_ != NULL) printf("%d: %p [%d]\n", __LINE__, p_, *p_);
    
    int *p__ = test3__();
    if (p__ != NULL) printf("%d: %p [%d]\n", __LINE__, p__, *p__);
    return;
}

int main()
{
    test1(); cout << endl;
    test2(); cout << endl;
    test3();
    return 0;
}
