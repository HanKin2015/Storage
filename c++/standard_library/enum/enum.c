#include <stdio.h>

enum DAY
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
};

//第一个枚举成员的默认值为整型的 0，后续枚举成员的值在前一个成员上加 1。
//也就说 spring 的值为 0，summer 的值为 3，autumn 的值为 4，winter 的值为 5。
enum season {spring, summer=3, autumn, winter};

#if 0
1、先定义枚举类型，再定义枚举变量
enum DAY
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
};
enum DAY day;

2、定义枚举类型的同时定义枚举变量
enum DAY
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
} day;

3、省略枚举名称，直接定义枚举变量
enum
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
} day;

在C 语言中，枚举类型是被当做 int 或者 unsigned int 类型来处理的，所以按照 C 语言规范是没有办法遍历枚举类型的。
不过在一些特殊的情况下，枚举类型必须连续是可以实现有条件的遍历。
使用 for 来遍历枚举的元素。
#endif

int main()
{
    printf("spring: %d, summer: %d, autumn: %d, winter: %d\n",
        spring, summer, autumn, winter);

    enum DAY day;
    day = THU;
    printf("day: %d\n", day);

    int a = 1;
    enum DAY weekend;
    weekend = ( enum DAY ) a;  //类型转换
    //weekend = a; //错误
    printf("weekend: %d\n", weekend);

    return 0;
}
