/*
setprecision(n)是格式控制符，
precision（n）是流对象的成员函数
纠正网上某些观点所说的取消c++所设置的cout中setprecision输出的格式方法
这里并不能取消精度控制，取消的是相应的std::ios_base::flags
C++11中可以这样写：
std::cout << std::defaultfloat;

C++11以前是这样写的：
std::cout.unsetf(std::ios_base::floatfield);

所进行的浮点输出精度（即生成多少数位），注意不是小数位数
*/

#include <iostream>
#include<iomanip>
using namespace std;
 
int main( )
{
    double s = 20.7843909;
    cout << s << endl;
    cout << setprecision(3) << s << endl;
    cout << fixed << setprecision(10) << s << endl;
    cout << s << endl;
    return 0;
}

/*
20.7844
20.8
20.7843909000
20.7843909000
*/
