[10356856@LIN-EB1ACC025D1 ~]$ ./a.out
32
32
32
40
sizeof(void*) = 8
alignof(Derived1) = 8
compiled with g++  8.4
[10356856@LIN-EB1ACC025D1 ~]$ cat k.cpp
#include <iostream>
class Base1 { char a; virtual void f(); };
class Base2 { char aa; virtual void ff(); };
class Derived1 : public Base1, public Base2 { };
class Derived2 : public Base1, public Base2 { };
class Derived3 : public Base1, public Base2 { int b; };
class Derived4 : public Base1, public Base2 { long long b; };
int main()
{
    std::cout << sizeof(Derived1) << std::endl;
    std::cout << sizeof(Derived2) << std::endl;
    std::cout << sizeof(Derived3) << std::endl;
    std::cout << sizeof(Derived4) << std::endl;
    std::cout << "sizeof(void*) = " << sizeof(void*) << '\n';
    std::cout << "alignof(Derived1) = " << alignof(Derived1) << '\n';
    #ifdef **clang**
    std::cout << "compiled with clang\n";
    #elif defined(**GNUC**)
    std::cout << "compiled with g++  " << **GNUC** << "." << **GNUC_MINOR** << '\n';
    #endif
    return 0;
}