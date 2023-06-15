/**
* 文 件 名: invert_true.cpp
* 文件描述: 取反布尔变量对比
* 作    者: HanKin
* 创建日期: 2023.06.14
* 修改日期：2023.06.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    bool i = true;
    cout << i << endl;
    i = ~i;
    cout << i << endl;
    i = ~i;
    cout << i << endl;
    
    int j = 1;
    cout << j << endl;
    j = ~j;
    cout << j << endl;
    j = ~j;
    cout << j << endl;
    
    bool k = true;
    cout << k << endl;
    k = ~(int)k;
    cout << (bool)k << endl;
    k = ~(int)k;
    cout << (bool)k << endl;
    
    bool m = false;
    cout << m << endl;
    m = ~m;
    cout << m << endl;
    m = ~m;
    cout << m << endl;
    
    bool n = false;
    cout << n << endl;
    n = !n;
    cout << n << endl;
    n = !n;
    cout << n << endl;
    
    int l = 0;
    cout << l << endl;
    l = !l;
    cout << l << endl;
    l = !l;
    cout << l << endl;
    return 0;
}
/*
我想是：
false=0000 0000，取反后为1111 1111，非零为true
true = 0000 0001，取反后为1111 1110，同样也是非零

如果您是在讨论计算机中的二进制数值，那么取反操作是将每个二进制位上的0变为1，1变为0。因此，对于一个二进制数值x，取反后得到的结果为~x。例如，如果x为0000 1111，则~x为1111 0000。因此，取反后的结果不一定是0，而是将所有位上的值取反。

可能是因为你的编译器对bool类型的实现方式不同。在C++标准中，bool类型只有两个取值：true和false，分别对应1和0。但是一些编译器可能会将bool类型实现为一个字节，其中非零值都被视为true，而零值被视为false。这种实现方式可能会导致按位取反运算符~的结果不同于预期。
1
1
1

1
-2
1

1
1
1

0
1
1

0
1
0

0
1
0
*/