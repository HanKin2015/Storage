#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;

/* char数组除外无法进行求数组大小 */
static void array_size()
{
    int nums[5] = {0};

    // error: cannot convert ‘int*’ to ‘const char*’ for argument ‘1’ to ‘size_t strlen(const char*)’
    //cout << strlen(nums) << endl;

    // 注意是无法进行判空的, 判空只能使用指针
    printf("%s[%d]: %lu / %lu = %lu\n", __FUNCTION__, __LINE__, sizeof(nums), sizeof(nums[0]), sizeof(nums) / sizeof(nums[0]));
    
    //int arr[0] = {0}; // 无法这样初始化
    int arr[0];
    // 难道是我想错了，居然运行结果正确，arr[0]能访问？？
    printf("%s[%d]: %lu / %lu = %lu\n", __FUNCTION__, __LINE__, sizeof(arr), sizeof(arr[0]), sizeof(arr) / sizeof(arr[0]));
    return;
}

/*
strlen - calculate the length of a string
#include <string.h>
size_t strlen(const char *s);

*/
static void study_strlen_sizeof()
{
    int arr[5] = {0};

    // error: cannot convert ‘int*’ to ‘const char*’ for argument ‘1’ to ‘size_t strlen(const char*)’
    //cout << strlen(arr) << endl;
    // 结论: strlen函数只能用于const char *类型
    
    int *p_arr[5];
    printf("%s[%d]: %lu %lu\n", __FUNCTION__, __LINE__, sizeof(p_arr), sizeof(*p_arr));
    
    char *str = new char[20];
    const char *s = "123";
    strncat(str, s, strlen(s) - 1);
    printf("%lu %lu %lu %lu %s\n", strlen(s), strlen(str), sizeof(s), sizeof(str), str);
    printf("%lu %lu %lu %lu\n", sizeof(char), sizeof(char *), sizeof(int), sizeof(int *));

    const char *log_file_prefix = "/log/today/log_";
    char tmp[256];
    strncpy(tmp, log_file_prefix, strlen(log_file_prefix));
    printf("tmp: %s, %lu, %lu.\n", tmp, sizeof(log_file_prefix), strlen(log_file_prefix));
    return;
}

/*
结合上面函数明显得出结论
*/
static void study_sizeof()
{
    int arr[] = {1, 2, 3};
    size_t a = sizeof arr;  // 语法一
    size_t b = sizeof(arr); // 语法二
    printf("a: %lu, b: %lu\n", a, b);   // int为4字节，所以答案12
    
    int *p_arr[5];
    printf("pointer: %lu %lu\n", sizeof(p_arr), sizeof(*p_arr));    // 40 8
    
    char str0[100];
    cout << sizeof(str0) << ' ' << strlen(str0) << endl;            // 100 1
    return;
}

/*
1.strlen函数只能用于const char *类型或char数组，用于求字符串长度
2.sizeof用于数据类型，结果一定是(2的指数*数组大小)，常用于数组的初始化，求数组或结构体的类型占用大小
*/
int main()
{
    array_size();
    study_strlen_sizeof();
    study_sizeof();
    return 0;
}
