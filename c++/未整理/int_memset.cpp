#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int nums[5] = {0};
    cout << sizeof(nums) << endl;
    // error: cannot convert ‘int*’ to ‘const char*’ for argument ‘1’ to ‘size_t strlen(const char*)’ 
    //cout << strlen(nums) << endl;

    // 求数组预存大小
    cout << sizeof(nums) / sizeof(nums[0]) << endl; // 注意是无法进行判空的, 判空只能使用指针
    
    char str0[100];
    cout << sizeof(str0) << ' ' << strlen(str0) << endl;
    return 0;
}
