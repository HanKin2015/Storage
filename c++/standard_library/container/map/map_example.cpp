/**
* 文 件 名: map_example.cpp
* 文件描述: map的使用
* 备    注：unordered_map需要2011标准
* 作    者: HanKin
* 创建日期: 2023.07.13
* 修改日期：2023.07.13
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
#include <unordered_map>
#endif
#include <map>
using namespace std;

/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
elements in mymap:
a => 50
c => 150
d => 200
*/
static void is_exist_key_by_find()
{
    printf("\n%d: %s\n", __LINE__, __FUNCTION__);
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
    std::unordered_map<char, int> mymap;
    std::unordered_map<char, int>::iterator it;
#else
    std::map<char, int> mymap;
    std::map<char, int>::iterator it;
#endif

    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    it = mymap.find('b');
    if (it != mymap.end())  {
        mymap.erase(it);
    }

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';
    return;
}

static void is_exist_key_by_iterator()
{
    printf("\n%d: %s\n", __LINE__, __FUNCTION__);
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
    std::unordered_map<char, int> mymap;
    std::unordered_map<char, int>::iterator it;
#else
    std::map<char, int> mymap;
    std::map<char, int>::iterator it;
#endif
    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    bool is_exist = false;
    it = mymap.begin();
    while (it != mymap.end()) {
        if (it->first == 'b') {
            is_exist = true;
            break;
        }
        it++;
    }
    if (is_exist) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    
    return;
}

static void is_exist_key_by_count()
{
    printf("\n%d: %s\n", __LINE__, __FUNCTION__);
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
    std::unordered_map<char, int> mymap;
#else
    std::map<char, int> mymap;
#endif
    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    if (mymap.count('b'))  {
        std::cout << "键\"b\"存在" << std::endl;
    } else {
        std::cout << "键\"b\"不存在" << std::endl;
    }

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';
    return;
}

/*
在C++17标准中，at函数的行为与C++11标准相同，即在访问不存在的键时会抛出std::out_of_range异常。在C++17标准之前，at函数在访问不存在的键时也会抛出std::out_of_range异常。

因此，如果你使用的是C++17标准或更早的标准，并且使用at函数访问不存在的键，程序会抛出std::out_of_range异常。如果你想要避免程序崩溃，可以使用count函数或find函数来判断指定键是否存在。

如果使用myMap["pear"]访问不存在的键，程序不会崩溃，但是会产生一个新的键值对，键为"pear"，值为该类型的默认构造值。具体来说，对于int类型的值，值为0，对于bool类型的值，值为false，对于其他类型的值，值为该类型的默认构造值。

这是因为map容器的operator[]函数会在访问不存在的键时自动创建一个新的键值对，并返回该键对应的值的引用。如果你不希望在访问不存在的键时自动创建新的键值对，可以使用count函数或find函数来判断指定键是否存在。
*/
static void access_not_exist_key()
{
    printf("\n%d: %s\n", __LINE__, __FUNCTION__);
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
    std::unordered_map<std::string, int> mymap1;
#else
    std::map<std::string, int> mymap1;
#endif
    std::map<std::string, int> mymap2;
    printf("%d %d\n", mymap1["mymap1"], mymap2["mymap2"]);
    
    int value = mymap2["apple"];
    std::cout << "键\"apple\"存在，对应的值为：" << value << std::endl;
    printf("apple count %lu apple1 count %lu\n", mymap2.count("apple"), mymap2.count("apple1"));
    
    value = mymap2.at("apple");
    std::cout << "键\"apple\"存在，对应的值为：" << value << std::endl;
    value = mymap2.at("apple1");
    std::cout << "键\"apple1\"存在，对应的值为：" << value << std::endl;
    
    printf("apple count %lu apple1 count %lu\n", mymap2.count("apple"), mymap2.count("apple1"));
    return;
}

int main(int argc, char *argv[])
{
    is_exist_key_by_find();
    is_exist_key_by_count();
    is_exist_key_by_iterator();
    access_not_exist_key();
    return 0;
}
